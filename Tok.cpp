#include <map>
#include <string>
#include "include/Tok.h"

using std::map;
using std::string;
using std::ostream;
using tok_t::tok_to_str;
using tok_t::TokType;

string Tok::to_str() const {
	string output;
	if (type == TokType::IDENTIFIER ||
		 type == TokType::STRING ||
		 type == TokType::NUMBER)
		output += lit_obj->to_str();
	else
		output += tok_to_str[type];
	return output;
}

namespace tok_t {
bool some_type_same_len(const string &s) {
	for (auto &str_tok_map : str_to_tok)
		if (str_tok_map.first.size() >= s.size() && 
			str_tok_map.first.substr(0, s.size()) == s) return true;
	return false;
}

map<string, TokType> str_to_tok = {
	// Single-character tokens.
	{"(", LEFT_PAREN},
	{")", RIGHT_PAREN},
	{"{", LEFT_BRACE},
	{"}", RIGHT_BRACE},
	{"[", LEFT_BRACKET},
	{"]", RIGHT_BRACKET},
	{",", COMMA},
	{".", DOT},
	{"-", MINUS},
	{"+", PLUS},
	{";", SEMICOLON},
	{"/", SLASH},
	{"*", STAR},
	{"|", PIPE},
	{"_", UNDERSCORE},

	// One or multiple character tokens.
	{"!", BANG},
	{"!=", BANG_EQUAL},
	{"=", EQUAL},
	{"==", EQUAL_EQUAL},
	{">", GREATER},
	{">=", GREATER_EQUAL},
	{"<", LESS},
	{"<=", LESS_EQUAL},
  {"::", COLON_COLON},
  {";;", SEMICOLON_SEMICOLON},
  {"++", PLUS_PLUS},
  {"--", MINUS_MINUS},

	// Keywords.
	{"and", AND},
	{"else", ELSE},
	{"false", FALSE},
	{"fun", FUN},
	{"for", FOR},
	{"if", IF},
	{"or", OR},
	{"print", PRINT},
	{"return", RETURN},
	{"true", TRUE},
	{"var", VAR},
	{"while", WHILE},
	{"in", IN},
};

map<TokType, string> tok_to_str = {
	// Single-character tokens.
	{LEFT_PAREN, "("},
	{RIGHT_PAREN, ")"},
	{LEFT_BRACE, "{"},
	{RIGHT_BRACE, "}"},
	{LEFT_BRACKET, "["},
	{RIGHT_BRACKET, "]"},
 	{COMMA, ","},
	{DOT, "."},
	{MINUS, "-"},
	{PLUS, "+"},
	{SEMICOLON, ";"},
	{SLASH, "/"},
	{STAR, "*"},
	{PIPE, "|"},
	{UNDERSCORE, "_"},

	// One or multiple character tokens.
	{BANG, "!"},
	{BANG_EQUAL, "!="},
	{EQUAL, "="},
	{EQUAL_EQUAL, "=="},
	{GREATER, ">"},
	{GREATER_EQUAL, ">="},
	{LESS, "<"},
	{LESS_EQUAL, "<="},
  {COLON_COLON, "::"},
  {SEMICOLON_SEMICOLON, ";;"},
  {PLUS_PLUS, "++"},
  {MINUS_MINUS, "--"},

	// Keywords.
	{AND, "and"},
	{ELSE, "else"},
	{FALSE, "false"},
	{FUN, "fun"},
	{FOR, "for"},
	{IF, "if"},
	{OR, "or"},
	{PRINT, "print"},
	{RETURN, "return"},
	{TRUE, "true"},
	{VAR, "var"},
	{WHILE, "while"},
	{IN, "in"},
};
} // namespace tok_t
