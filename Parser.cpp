#include <map>
#include <memory>
#include <stdexcept>
#include <vector>
#include "include/Exception.h"
#include "include/Expr.h"
#include "include/Env.h"
#include "include/Parser.h"
#include "include/PrimObj.h"
#include "include/Interpreter.h"

using std::string;
using std::to_string;
using std::initializer_list;
using std::prev;
using std::make_shared;
using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::cout;
using std::runtime_error;
using std::list;
using std::vector;
using std::cerr;
using std::endl;
using tok_t::TokType;

Parser::Parser() { }

Parser::Parser(const string &s) {
  *this = s;
}

Parser &Parser::operator=(const string &s) {
	lex = s;
	cur_tok = lex.toks.cbegin();
  return *this;
}

list<StmtPtr> Parser::parse() {
	list<StmtPtr> stmts;
	while (!check(TokType::END)) {
    try {
      stmts.push_back(declaration());
    } catch (ProgError e) {
      cerr << "Syntax Error: " << e.err_msg() << endl;
      exit(0);
    }
	}
	return stmts;
}

void Parser::print_toks() const {
	cout << lex << '\n';
}

StmtPtr Parser::declaration() {
	if (match({TokType::FN})) return func_declaration();
	if (match({TokType::LET})) return var_declaration();
	return statement();
}

StmtPtr Parser::func_declaration() {
	const TokPtr name = consume(TokType::IDENTIFIER, "Expected function name");
	consume(TokType::LEFT_PAREN, "Expected '(' after function name");

	list<TokPtr> params;
	if (!check(TokType::RIGHT_PAREN))
		do { params.push_back(
				consume(TokType::IDENTIFIER, "Expect parameter name"));
		} while (match({TokType::COMMA}));
	consume(TokType::RIGHT_PAREN, "Expect ')' after parameters");

	consume(TokType::COLON_COLON, "Expect '::' before function body");
	const StmtPtr body = block();
  // Supports overloaded functions
  const auto arity = make_shared<StrObj>("_" + to_string(params.size()));
  const auto callee_arity = make_shared<Tok>(TokType::IDENTIFIER, name->lit_obj->push(arity), name->line);
	return make_shared<FuncStmt>(callee_arity, params, body);
}

StmtPtr Parser::var_declaration() {
	const TokPtr name = consume(TokType::IDENTIFIER, "Expected variable name");
	ExprPtr initializer = nullptr;

	if (match({TokType::EQUAL})) initializer = expression();

	consume(TokType::SEMICOLON, "Expect ';' after variable declaration");
  return make_shared<VarDeclStmt>(name, initializer);
}

StmtPtr Parser::statement() {
	if (match({TokType::FOR})) return for_statement();
	if (match({TokType::IF})) return if_statement();
	if (match({TokType::PRINT})) return print_statement();
	if (match({TokType::RETURN})) return return_statement();
	if (match({TokType::WHILE})) return while_statement();
	if (match({TokType::COLON_COLON})) return block();
	return expression_statement();
}

StmtPtr Parser::expression_statement() {
	const ExprPtr expr = expression();
	consume(TokType::SEMICOLON, "Expect ';' after expression");
	return make_shared<ExprStmt>(expr);
}

StmtPtr Parser::for_statement() {
  // Somehow this ran first try with 0 mistakes...
  // That's a first
  
  // Collecting inputs
	// consume(TokType::LEFT_PAREN, "Expect '(' after for");
  const TokPtr var = consume(TokType::IDENTIFIER, "Expect identifier to declare");
  const TokPtr in = consume(TokType::IN, "Expect 'in' before domain");
  ExprPtr container = expression();
  // Conversion error without cap (causes seg fault)
  container = make_shared<Call>(
    make_shared<Var>(Interpreter::to_arr_tok), in, list<ExprPtr>{container});
	// consume(TokType::RIGHT_PAREN, "Expect ')' after domain");

	// Initializer (1)
  const TokPtr index = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("IDX"));
  const TokPtr arr = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("ARR"));
  const StmtPtr index_init = make_shared<VarDeclStmt>(index, make_shared<Lit>(make_shared<IntObj>(1)));
  const StmtPtr arr_init = make_shared<VarDeclStmt>(arr, container);
  const ExprPtr index_var = make_shared<Var>(index);
  const ExprPtr arr_var = make_shared<Var>(arr);

	// Condition (2)
  const ExprPtr len = make_shared<Unary>(arr_var, make_shared<Tok>(TokType::PIPE));
  const ExprPtr condition = make_shared<BinOp>(index_var, len, 
                                               make_shared<Tok>(TokType::LESS_EQUAL));

	// Increment (3)
  const ExprPtr inc_res = make_shared<BinOp>(index_var, make_shared<Lit>(make_shared<IntObj>(1)),
                                             make_shared<Tok>(TokType::PLUS));
  const ExprPtr inc_asgn = make_shared<Asgn>(index, inc_res);
	
	// Body
	StmtPtr body = statement();

  body = make_shared<BlockStmt>(
    list<StmtPtr>({
      make_shared<VarDeclStmt>(var, make_shared<BinOp>(arr_var, index_var, 
                                                       make_shared<Tok>(TokType::UNDERSCORE))),
      body, 
      make_shared<ExprStmt>(inc_asgn)
    })
  );
	body = make_shared<WhileStmt>(condition, body);
  body = make_shared<BlockStmt>(
    list<StmtPtr>({arr_init, index_init, body})
  );

	return body;
}

StmtPtr Parser::if_statement() {
	// consume(TokType::LEFT_PAREN, "Expect '(' before if condition");
	const ExprPtr condition = expression();
	// consume(TokType::RIGHT_PAREN, "Expect ')' after if condition");
	const StmtPtr then_branch = statement();
	if (match({TokType::ELSE})) {
		const StmtPtr else_branch = statement();
		return make_shared<IfStmt>(condition, then_branch, else_branch);
	}
	return make_shared<IfStmt>(condition, then_branch);
}

StmtPtr Parser::print_statement() {
	const ExprPtr val = expression();
	consume(TokType::SEMICOLON, "Expect ';' after value");
	return make_shared<PrintStmt>(val);
}

StmtPtr Parser::return_statement() {
  const TokPtr keyword = *prev(cur_tok);
  if (match({TokType::SEMICOLON}))
    return make_shared<ReturnStmt>();

	const ExprPtr val = expression();
	consume(TokType::SEMICOLON, "Expect ';' after value");
	return make_shared<ReturnStmt>(val);
}

StmtPtr Parser::while_statement() {
	// consume(TokType::LEFT_PAREN, "Expect '(' before while condition");
	const ExprPtr condition = expression();
	// consume(TokType::RIGHT_PAREN, "Expect ')' after while condition");
	const StmtPtr body = statement();
	return make_shared<WhileStmt>(condition, body);
}

StmtPtr Parser::block() {
	list<StmtPtr> stmts;
	while (!check(TokType::SEMICOLON_SEMICOLON) && !is_at_end())
		stmts.push_back(declaration());

	consume(TokType::SEMICOLON_SEMICOLON, "Expected ';;' after block");
	return make_shared<BlockStmt>(stmts);
}

ExprPtr Parser::expression() {
	return assignment();
}

ExprPtr Parser::assignment() {
	ExprPtr expr = logic_or();

	if (match({TokType::EQUAL})) {
		shared_ptr<Var> var = dynamic_pointer_cast<Var>(expr);
		if (var == nullptr) throw ProgError("Invalid assignment target", *cur_tok);
		const ExprPtr val = logic_or();
		expr = make_shared<Asgn>(var->get_name(), val);
	}

	return expr;
}

ExprPtr Parser::logic_or() {
	ExprPtr expr = logic_and();

	while (match({TokType::OR})) {
		const TokPtr op = *prev(cur_tok);
		const ExprPtr rhs = logic_and();
		expr = make_shared<Logical>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::logic_and() {
	ExprPtr expr = equality();

	while (match({TokType::AND})) {
		const TokPtr op = *prev(cur_tok);
		const ExprPtr rhs = equality();
		expr = make_shared<Logical>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::equality() {
	ExprPtr expr = comparison();

	while (match({TokType::EQUAL_EQUAL, TokType::BANG_EQUAL})) {
		const TokPtr op = *prev(cur_tok);
		const ExprPtr rhs = comparison();
		expr = make_shared<BinOp>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::comparison() {
	ExprPtr expr = array_op();

	while (match({TokType::GREATER, TokType::GREATER_EQUAL,
				  TokType::LESS, TokType::LESS_EQUAL})) {
		const TokPtr op = *prev(cur_tok);
		const ExprPtr rhs = term();
		expr = make_shared<BinOp>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::array_op() {
	ExprPtr expr = term();

	while (match({TokType::MINUS_MINUS, TokType::PLUS_PLUS})) {
		const TokPtr op = *prev(cur_tok);
		const ExprPtr rhs = factor();
		expr = make_shared<BinOp>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::term() {
	ExprPtr expr = factor();

	while (match({TokType::MINUS, TokType::PLUS})) {
		const TokPtr op = *prev(cur_tok);
		const ExprPtr rhs = factor();
		expr = make_shared<BinOp>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::factor() {
	ExprPtr expr = unary();

	while (match({TokType::STAR, TokType::SLASH})) {
		const TokPtr op = *prev(cur_tok);
		const ExprPtr rhs = unary();
		expr = make_shared<BinOp>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::unary() {
	if (match({TokType::BANG, TokType::MINUS})) {
		const TokPtr op = *prev(cur_tok);
		const ExprPtr rhs = exponent();
		return make_shared<Unary>(rhs, op);
	}

	return exponent();
}

ExprPtr Parser::exponent() {
	ExprPtr expr = array();

	while (match({TokType::CARROT})) {
		const TokPtr op = *prev(cur_tok);
		const ExprPtr rhs = array();
		expr = make_shared<BinOp>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::array() {
	if (match({TokType::LEFT_BRACKET})) {
    vector<ExprPtr> expr_arr;
    if (match({TokType::RIGHT_BRACKET})) return make_shared<Arr>(expr_arr);
    do { expr_arr.push_back(expression()); } while (match({TokType::COMMA}));
    consume(TokType::RIGHT_BRACKET, "Expect ']' after array");
    return make_shared<Arr>(expr_arr);
	}

	return set();
}

ExprPtr Parser::set() {
  if (match({TokType::LEFT_BRACE})) {
    // Empty set
    if (match({TokType::RIGHT_BRACE}))
      return make_shared<Set>(nullptr, nullptr, make_shared<Arr>(vector<ExprPtr>{}), nullptr);

    const ExprPtr ret = expression();
    if (!match({TokType::PIPE})) {
      const auto brace = consume(TokType::RIGHT_BRACE, "Expect '}' after expression");
      const auto arr = make_shared<Arr>(vector<ExprPtr>{ret});
      return make_shared<Call>(
        make_shared<Var>(Interpreter::to_set_tok), brace, list<ExprPtr>{arr});
    }
    // consume(TokType::PIPE, "Expect '|' before variable declaration");
    // For ranges and non ranges
    const TokPtr var_name = consume(TokType::IDENTIFIER, 
                                    "Expect identifier before domain");
    consume(TokType::IN, "Expect 'in' before domain");
    const ExprPtr domain = expression();
    if (match({TokType::RIGHT_BRACE}))
      return make_shared<Set>(ret, var_name, domain);
    consume(TokType::COMMA, "Expect ',' or '}' after domain");

    const ExprPtr conditions = logic_or();
    consume(TokType::RIGHT_BRACE, "Expect '}' after domain");
    return make_shared<Set>(ret, var_name, domain, conditions);
  }

  return call();
}

ExprPtr Parser::call() {
	ExprPtr expr = index();

	while (match({TokType::LEFT_PAREN}))
		expr = finish_call(expr);

	return expr;
}

ExprPtr Parser::finish_call(const ExprPtr &callee) {
  const auto callee_var = dynamic_pointer_cast<Var>(callee);
  if (callee_var == nullptr) throw ProgError("Callee must be an identifier", *prev(cur_tok));
  const auto callee_name = callee_var->get_name();
	list<ExprPtr> args;

	if (match({TokType::RIGHT_PAREN}))  {
    // Supports overloaded functions
    const auto arity = make_shared<StrObj>("_0");
    const auto new_name = make_shared<Tok>(TokType::IDENTIFIER, callee_name->lit_obj->push(arity), 
                                           callee_name->line);
    const auto callee_arity = make_shared<Var>(new_name);
	  return make_shared<Call>(callee_arity, *prev(cur_tok));
  }

	do { args.push_back(expression()); } while (match({TokType::COMMA}));

	const TokPtr paren = consume(TokType::RIGHT_PAREN, "Expect ')' after arguments");

  // Supports overloaded functions
  const auto arity = make_shared<StrObj>("_" + to_string(args.size()));
  const auto new_name = make_shared<Tok>(TokType::IDENTIFIER, callee_name->lit_obj->push(arity), 
                                         callee_name->line);
  const auto callee_arity = make_shared<Var>(new_name);
	return make_shared<Call>(callee_arity, paren, args);
}

ExprPtr Parser::index() {
  const ExprPtr expr = primary();

  if (match({TokType::UNDERSCORE})) {
    const TokPtr op = *prev(cur_tok);
    const ExprPtr index = primary();
    return make_shared<BinOp>(expr, index, op);
  }

  return expr;
}

ExprPtr Parser::primary() {
	if (match({TokType::FALSE})) 
		return make_shared<Lit>(make_shared<BoolObj>(false));
	if (match({TokType::TRUE})) 
		return make_shared<Lit>(make_shared<BoolObj>(true));

	if (match({TokType::NUMBER, TokType::STRING})) {
		const auto prev_tok = *prev(cur_tok);
		return make_shared<Lit>(prev_tok->lit_obj);
	}

	if (match({TokType::IDENTIFIER})) 
		return make_shared<Var>(*prev(cur_tok));
	
	if (match({TokType::LEFT_PAREN})) {
		const ExprPtr expr = expression();
		consume(TokType::RIGHT_PAREN, "Missing ')'");
		return make_shared<Grouping>(expr);
	}

	if (match({TokType::PIPE})) {
		const ExprPtr expr = expression();
		consume(TokType::PIPE, "Missing ending '|'");
		return make_shared<Unary>(expr, make_shared<Tok>(TokType::PIPE));
	}

  throw ProgError("Invalid syntax for token '" + (*cur_tok)->to_str() + "'", *cur_tok);
}

bool Parser::match(const initializer_list<TokType> &tok_type_l) {
	for (auto &type : tok_type_l)
		if (check(type)) { adv(); return true; }
	return false;
}

// Like match, advances if it's the correct type, otherwise throw an error
TokPtr Parser::consume(const TokType tok_type, const string &msg) {
	if (check(tok_type)) return adv();
	throw ProgError(msg, *prev(cur_tok));
}

TokPtr Parser::adv() {
	if ((*cur_tok)->type != TokType::END) ++cur_tok;
	return *prev(cur_tok);
}
