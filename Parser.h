#ifndef PARSER_H
#define PARSER_H

#include <list>
#include <memory>
#include "Expr.h"
#include "Lexer.h"
#include "Stmt.h"

class Parser {
public:
	Parser(const std::string&); 

	std::list<StmtPtr> parse();

	void print_toks() const;
private:
	std::list<Tok>::const_iterator cur_tok;
	EnvPtr cur_env;
	// std::list<Tok>::const_iterator eof;
	Lexer lex;

	const inline Tok &adv();

	bool check(tok_t::TokType tok_type) const 
		{ return cur_tok->type == tok_type; }
	bool is_at_end() const { return check(tok_t::TokType::END); }

	const Tok &consume(tok_t::TokType, const std::string&);
	bool match(std::initializer_list<tok_t::TokType>);

	ExprPtr finish_call(ExprPtr callee);

	StmtPtr declaration();
	StmtPtr statement();
	StmtPtr func_declaration();
	StmtPtr var_declaration();
	StmtPtr expression_statement();
	StmtPtr for_statement();
	StmtPtr if_statement();
	StmtPtr print_statement();
	StmtPtr while_statement();
	StmtPtr block();

	ExprPtr expression();
	ExprPtr assignment();
	ExprPtr logic_or();
	ExprPtr logic_and();
	ExprPtr equality();
	ExprPtr comparison();
	ExprPtr term();
	ExprPtr factor();
	ExprPtr unary();
	ExprPtr call();
	ExprPtr primary();
};

#endif
