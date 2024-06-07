#include <map>
#include <string>
#include "Tok.h"

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
  {"%", PERCENT},
	{"^", CARROT},
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
	{"-=", MINUS_EQUAL},
	{"+=", PLUS_EQUAL},
	{"/=", SLASH_EQUAL},
	{"*=", STAR_EQUAL},
	{"^=", CARROT_EQUAL},
  {"++=", PLUS_PLUS_EQUAL},
  {"--=", MINUS_MINUS_EQUAL},

	// Keywords.
	{"and", AND},
	{"else", ELSE},
	{"false", FALSE},
	{"fn", FN},
	{"for", FOR},
	{"if", IF},
	{"or", OR},
	{"print", PRINT},
	{"return", RETURN},
	{"true", TRUE},
	{"let", LET},
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
  {PERCENT, "%"},
	{CARROT, "^"},
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
	{MINUS_EQUAL, "-="},
	{PLUS_EQUAL, "+="},
	{SLASH_EQUAL, "/="},
	{STAR_EQUAL, "*="},
	{CARROT_EQUAL, "^="},
  {PLUS_PLUS_EQUAL, "++="},
  {MINUS_MINUS_EQUAL, "--="},

	// Keywords.
	{AND, "and"},
	{ELSE, "else"},
	{FALSE, "false"},
	{FN, "fn"},
	{FOR, "for"},
	{IF, "if"},
	{OR, "or"},
	{PRINT, "print"},
	{RETURN, "return"},
	{TRUE, "true"},
	{LET, "let"},
	{WHILE, "while"},
	{IN, "in"},
};
} // namespace tok_t
