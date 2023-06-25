#ifndef TOK_H
#define TOK_H

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include "PrimObj.h"

namespace tok_t {
enum TokType {
	// Single-character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// LitTokerals.
	IDENTIFIER, STRING, NUMBER,

	// Keywords.
	AND, ELSE, FALSE, FUN, FOR, IF, OR,
	PRINT, RETURN, TRUE, VAR, WHILE,

	END // EOF
};
extern bool some_type_same_len(const std::string&);
extern std::map<std::string, TokType> str_to_tok;
extern std::map<TokType, std::string> tok_to_str;
} // namespace TokType

class Tok {
public:
	friend std::ostream &operator<<(std::ostream &os, const Tok &tok)
		{ os << tok.to_str(); return os; }

	Tok(const Tok&) = default;

	Tok(tok_t::TokType _type) : type(_type) { } 

	Tok(tok_t::TokType _type, double _lit_obj) 
		: type(_type), lit_obj(std::make_shared<DoubleObj>(_lit_obj)) { } 
	Tok(tok_t::TokType _type, const std::string &_lit_obj) 
		: type(_type), lit_obj(std::make_shared<StrObj>(_lit_obj)) { } 
	
	Tok(const std::string &type_str)
		: type(tok_t::str_to_tok[type_str]) { } 

	std::string to_str() const;

	const tok_t::TokType type;
	const std::shared_ptr<PrimObj> lit_obj;
};
typedef std::shared_ptr<Tok> TokPtr;

#endif
