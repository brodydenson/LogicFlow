#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <memory>
#include "Expr.h"
#include "Lexer.h"
#include "Stmt.h"

class Parser {
public:
  Parser();
	Parser(const std::string&);
	Parser(const Parser&) = default;
	Parser &operator=(const std::string&);

	std::list<StmtPtr> parse();

	void print_toks() const;
private:
	std::list<TokPtr>::const_iterator cur_tok;
	Lexer lex;

	inline TokPtr adv();

	bool check(const tok_t::TokType tok_type) const 
		{ return (*cur_tok)->type == tok_type; }
	bool is_at_end() const { return check(tok_t::TokType::END); }

	TokPtr consume(const tok_t::TokType, const std::string&);
	bool match(const std::initializer_list<tok_t::TokType>&);

	ExprPtr finish_call(const ExprPtr&);

	StmtPtr declaration();
	StmtPtr statement();
	StmtPtr func_declaration();
	StmtPtr var_declaration();
	StmtPtr expression_statement();
	StmtPtr for_statement();
	StmtPtr if_statement();
	StmtPtr print_statement();
	StmtPtr return_statement();
	StmtPtr while_statement();
	StmtPtr block();

	ExprPtr expression();
	ExprPtr assignment();
	ExprPtr logic_or();
	ExprPtr logic_and();
	ExprPtr equality();
	ExprPtr comparison();
  ExprPtr array_op();
	ExprPtr term();
	ExprPtr factor();
	ExprPtr exponent();
	ExprPtr unary();
	ExprPtr array();
	ExprPtr set();
	ExprPtr call();
  ExprPtr index();
	ExprPtr primary();
};

#endif
