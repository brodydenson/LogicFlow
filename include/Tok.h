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
  LEFT_BRACKET, RIGHT_BRACKET,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
  PIPE, UNDERSCORE,

	// One or multiple character tokens.
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,
  COLON_COLON, SEMICOLON_SEMICOLON,
  PLUS_PLUS, MINUS_MINUS,
	// LitTokerals.
	IDENTIFIER, STRING, NUMBER,

	// Keywords.
	AND, ELSE, FALSE, FUN, FOR, IF, OR,
	PRINT, RETURN, TRUE, VAR, WHILE,
  IN,

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

	Tok(tok_t::TokType _type, unsigned _line=0) : type(_type), line(_line) { } 

	Tok(tok_t::TokType _type, const PrimObjPtr &_lit_obj, unsigned _line=0) 
		: type(_type), lit_obj(_lit_obj), line(_line) { } 
	
	Tok(const std::string &type_str, unsigned _line=0)
	  : type(tok_t::str_to_tok[type_str]), line(_line) { } 

	std::string to_str() const;

	const tok_t::TokType type;
  const unsigned line;
	const std::shared_ptr<PrimObj> lit_obj;
};
typedef std::shared_ptr<Tok> TokPtr;

#endif
