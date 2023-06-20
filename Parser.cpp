#include <map>
#include <memory>
#include <stdexcept>
#include "Asgn.h"
#include "Call.h"
#include "Func.h"
#include "Expr.h"
#include "Env.h"
#include "Parser.h"
#include "BinOp.h"
#include "Logical.h"
#include "Unary.h"
#include "Lit.h"
#include "Grouping.h"
#include "Var.h"
#include "PrimObj.h"

using std::string;
using std::initializer_list;
using std::prev;
using std::make_shared;
using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::cout;
using std::runtime_error;
using std::list;
using tok_t::TokType;

Parser::Parser(const std::string &s) {
	lex = s;
	cur_tok = lex.toks.cbegin();
	cur_env = make_shared<Env>(nullptr);
}

list<StmtPtr> Parser::parse() {
	list<StmtPtr> stmts;
	while (!check(TokType::END)) {
		stmts.push_back(declaration());
	}
	return stmts;
}

void Parser::print_toks() const {
	cout << lex << '\n';
}

StmtPtr Parser::declaration() {
	if (match({TokType::FUN})) return func_declaration();
	if (match({TokType::VAR})) return var_declaration();
	return statement();
}

StmtPtr Parser::func_declaration() {
	Tok name = consume(TokType::IDENTIFIER, "Expected function name");
	consume(TokType::LEFT_PAREN, "Expected '(' after function name");

	list<Tok> params;
	if (!check(TokType::RIGHT_PAREN))
		do { params.push_back(
				consume(TokType::IDENTIFIER, "Expect parameter name"));
		} while (match({TokType::COMMA}));
	consume(TokType::RIGHT_PAREN, "Expect ')' after parameters");

	consume(TokType::LEFT_BRACE, "Expect '{' before function body");
	StmtPtr body = block();
	return make_shared<Func>(name, params, body);
}

StmtPtr Parser::var_declaration() {
	Tok name = consume(TokType::IDENTIFIER, "Expected variable name");
	ExprPtr initializer = nullptr;

	if (match({TokType::EQUAL})) initializer = expression();

	consume(TokType::SEMICOLON, "Expect ';' after variable declaration");
	return make_shared<VarDeclStmt>(name, initializer, cur_env);
}

StmtPtr Parser::statement() {
	if (match({TokType::FOR})) return for_statement();
	if (match({TokType::IF})) return if_statement();
	if (match({TokType::PRINT})) return print_statement();
	if (match({TokType::WHILE})) return while_statement();
	if (match({TokType::LEFT_BRACE})) return block();
	return expression_statement();
}

StmtPtr Parser::expression_statement() {
	ExprPtr expr = expression();
	consume(TokType::SEMICOLON, "Expect ';' after expression");
	return make_shared<ExprStmt>(expr);
}

StmtPtr Parser::for_statement() {
	consume(TokType::LEFT_PAREN, "Expect '(' after for");

	// Initializer (1)
	StmtPtr initializer;
	if (!match({TokType::SEMICOLON})) {
		initializer = match({TokType::VAR}) 
			? var_declaration() : expression_statement();
	}

	// Condition (2)
	ExprPtr condition;
	if (!check(TokType::SEMICOLON)) {
		condition = expression();
	}
	consume(TokType::SEMICOLON, "Expect ';' after loop condition");

	// Increment (3)
	ExprPtr increment;
	if (!check(TokType::RIGHT_PAREN)) {
		increment = expression();
	}
	consume(TokType::RIGHT_PAREN, "Expect ')' after for clauses");
	
	// Body
	StmtPtr body = statement();

	if (increment) {
		body = make_shared<BlockStmt>(
			list<StmtPtr>({body, make_shared<ExprStmt>(increment)})
		);
	}

	if (!condition) condition = make_shared<Lit>(make_shared<BoolObj>(true));
	body = make_shared<WhileStmt>(condition, body);

	if (initializer) {
		body = make_shared<BlockStmt>(
			list<StmtPtr>({initializer, body})
		);
	}

	return body;
}

StmtPtr Parser::if_statement() {
	consume(TokType::LEFT_PAREN, "Expect '(' before if condition");
	ExprPtr condition = expression();
	consume(TokType::RIGHT_PAREN, "Expect ')' after if condition");
	StmtPtr then_branch = statement();
	if (match({TokType::ELSE})) {
		StmtPtr else_branch = statement();
		return make_shared<IfStmt>(condition, then_branch, else_branch);
	}
	return make_shared<IfStmt>(condition, then_branch);
}

StmtPtr Parser::print_statement() {
	ExprPtr val = expression();
	consume(TokType::SEMICOLON, "Expect ';' after value");
	return make_shared<PrintStmt>(val);
}

StmtPtr Parser::while_statement() {
	consume(TokType::LEFT_PAREN, "Expect '(' before while condition");
	ExprPtr condition = expression();
	consume(TokType::RIGHT_PAREN, "Expect ')' after while condition");
	StmtPtr body = statement();
	return make_shared<WhileStmt>(condition, body);
}

StmtPtr Parser::block() {
	cur_env = make_shared<Env>(cur_env);
	list<StmtPtr> stmts;
	while (!check(TokType::RIGHT_BRACE) && !is_at_end())
		stmts.push_back(declaration());

	consume(TokType::RIGHT_BRACE, "Expected '}' after block");
	cur_env = cur_env->get_enclosing();
	return make_shared<BlockStmt>(stmts);
}

ExprPtr Parser::expression() {
	return assignment();
}

ExprPtr Parser::assignment() {
	ExprPtr expr = logic_or();

	if (match({TokType::EQUAL})) {
		shared_ptr<Var> var = dynamic_pointer_cast<Var>(expr);
		if (var == nullptr) throw runtime_error("Invalid assignment target");
		ExprPtr val = logic_or();
		expr = make_shared<Asgn>(var->get_name(), val, cur_env);
	}

	return expr;
}

ExprPtr Parser::logic_or() {
	ExprPtr expr = logic_and();

	while (match({TokType::OR})) {
		Tok op = *prev(cur_tok);
		ExprPtr rhs = logic_and();
		expr = make_shared<Logical>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::logic_and() {
	ExprPtr expr = equality();

	while (match({TokType::AND})) {
		Tok op = *prev(cur_tok);
		ExprPtr rhs = equality();
		expr = make_shared<Logical>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::equality() {
	ExprPtr expr = comparison();

	while (match({TokType::EQUAL_EQUAL, TokType::BANG_EQUAL})) {
		Tok op = *prev(cur_tok);
		ExprPtr rhs = comparison();
		expr = make_shared<BinOp>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::comparison() {
	ExprPtr expr = term();

	while (match({TokType::GREATER, TokType::GREATER_EQUAL,
				  TokType::LESS, TokType::LESS_EQUAL})) {
		Tok op = *prev(cur_tok);
		ExprPtr rhs = term();
		expr = make_shared<BinOp>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::term() {
	ExprPtr expr = factor();

	while (match({TokType::MINUS, TokType::PLUS})) {
		Tok op = *prev(cur_tok);
		ExprPtr rhs = factor();
		expr = make_shared<BinOp>(expr, rhs, op);
	}

	return expr;
}

ExprPtr Parser::factor() {
	ExprPtr expr = unary();

	while (match({TokType::STAR, TokType::SLASH})) {
		Tok op = *prev(cur_tok);
		ExprPtr rhs = unary();
		expr = make_shared<BinOp>(expr, rhs, op);
	}

	return expr;
}


ExprPtr Parser::unary() {
	if (match({TokType::BANG, TokType::MINUS})) {
		Tok op = *prev(cur_tok);
		ExprPtr rhs = unary();
		return make_shared<Unary>(rhs, op);
	}

	return call();
}

ExprPtr Parser::call() {
	ExprPtr expr = primary();

	while (match({TokType::LEFT_PAREN})) {
		expr = finish_call(expr);
	}

	return expr;
}

ExprPtr Parser::finish_call(ExprPtr callee) {
	list<ExprPtr> args;

	if (match({TokType::RIGHT_PAREN})) 
		{ return make_shared<Call>(callee, *prev(cur_tok)); }

	do { args.push_back(expression()); } while (match({TokType::COMMA}));

	Tok paren = consume(TokType::RIGHT_PAREN, "Expect ')' after arguments");

	return make_shared<Call>(callee, paren, args);
}

ExprPtr Parser::primary() {
	if (match({TokType::FALSE})) 
		return make_shared<Lit>(make_shared<BoolObj>(false));
	if (match({TokType::TRUE})) 
		return make_shared<Lit>(make_shared<BoolObj>(true));

	if (match({TokType::NUMBER, TokType::STRING})) {
		auto prev_tok = prev(cur_tok);
		return make_shared<Lit>(prev_tok->lit_obj);
	}

	if (match({TokType::IDENTIFIER})) 
		return make_shared<Var>(*prev(cur_tok), cur_env);
	
	if (match({TokType::LEFT_PAREN})) {
		ExprPtr expr = expression();
		consume(TokType::RIGHT_PAREN, "Missing ')'");
		return make_shared<Grouping>(expr);
	}

	throw std::logic_error("No match for token '" + cur_tok->to_string() + "' found in parser");
}

bool Parser::match(initializer_list<TokType> tok_type_l) {
	for (auto &type : tok_type_l)
		if (check(type)) { adv(); return true; }
	return false;
}

// Like match, advances if it's the correct type, otherwise throw an error
const Tok &Parser::consume(TokType tok_type, const string &msg) {
	if (check(tok_type)) return adv();
	throw runtime_error(msg);
}

const Tok &Parser::adv() {
	if (cur_tok->type != TokType::END) ++cur_tok;
	return *prev(cur_tok);
}
