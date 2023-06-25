#include <algorithm>
#include <iostream>
#include <cctype>
#include "Headers/Lexer.h"
#include "Headers/Tok.h"

using std::string;
using std::vector;
using std::istringstream;
using std::cout;
using std::ostream;
using std::set;
using std::isalpha;
using std::isdigit;
using std::stod;
using std::runtime_error;
using std::logic_error;
using std::make_shared;
using std::isspace;

using tok_t::TokType;
using tok_t::str_to_tok;
using tok_t::some_type_same_len;

ostream &operator<<(ostream &os, const Lexer &lex) {
	os << "[";
	auto it = lex.toks.cbegin();
	while (it != lex.toks.cend())
		os << '(' << **it << " | " << (*it)->type << ')' << (++it != lex.toks.cend() ? ", " : "");
	os << "]";
	return os;
}

Lexer::Lexer() { }

Lexer::Lexer(const string &_content) { *this = _content; }

Lexer &Lexer::operator=(const string &_content) {
	content = _content;
	cur_it = content.cbegin();
	tokenize();
	return *this;
}


bool Lexer::match(const char ch) {
	if (cur_it != content.cend() && *cur_it == ch) 
		{ ++cur_it; return true; }
	return false;
}

TokPtr Lexer::next_tok() {
	// Forgets whitespaces
	while (isspace(static_cast<unsigned char>(*cur_it))) ++cur_it;
  // cout << *cur_it;
	const auto beg = cur_it;
	const auto op_end = check_op();
	const auto key_end = check_key();
	const auto id_lit_end = check_id_lit();
	const auto str_lit_end = check_str_lit();
	const auto num_lit_end = check_num_lit();

	// cout << *op_end << ' ' << *var_or_key_end << ' ' << *lit_end << '\n';

	TokType type;
	if (op_end != cur_it) 
		{ cur_it = op_end; return make_shared<Tok>(string(beg, op_end)); }
	else if (key_end != cur_it) 
		{ cur_it = key_end; return make_shared<Tok>(string(beg, key_end)); }
	else if (id_lit_end != cur_it) 
		{ cur_it = id_lit_end; return make_shared<Tok>(TokType::IDENTIFIER, 
								string(beg, id_lit_end)); }
	// String literal needs to trim off the excess
	else if (str_lit_end != cur_it) 
		{ cur_it = str_lit_end; return make_shared<Tok>(TokType::STRING, 
								 string(beg+1, str_lit_end-1)); }
	else if (num_lit_end != cur_it) 
		{ cur_it = num_lit_end; return make_shared<Tok>(TokType::NUMBER, 
								 stod(string(beg, num_lit_end))); }
  // cout << '\n' << toascii(*cur_it) << std::endl;
	throw logic_error("No matching case for current character"); 
	
}

void Lexer::tokenize() {
	toks.clear();
	while (cur_it != content.cend()) 
		toks.push_back(next_tok());
	toks.push_back(make_shared<Tok>(TokType::END));
}

Lexer::sci Lexer::check_op() const {
	auto tmp_it = cur_it;
	while (tmp_it != content.cend() && 
		!isalpha(*tmp_it) &&
		!isdigit(*tmp_it) &&
		some_type_same_len(string(cur_it, tmp_it + 1))) ++tmp_it;
	if (cur_it != tmp_it && str_to_tok.find(string(cur_it, tmp_it)) == str_to_tok.cend()) 
		throw runtime_error("Invalid operator token");
	return tmp_it;
}

Lexer::sci Lexer::check_key() const {
	if (!isalpha(*cur_it)) return cur_it;
	auto tmp_it = cur_it;

	// Doesn't encounter an operator or space
	do ++tmp_it; 
	while (tmp_it != content.cend() && 
		(isalpha(*tmp_it) || isdigit(*tmp_it)) && 
		*tmp_it != ' ');
	if (str_to_tok.find(string(cur_it, tmp_it)) == str_to_tok.cend()) return cur_it;
	return tmp_it;
}

Lexer::sci Lexer::check_id_lit() const {
	if (!isalpha(*cur_it)) return cur_it;
	auto tmp_it = cur_it;

	// Doesn't encounter an operator or space
	do ++tmp_it; 
	while (tmp_it != content.cend() && 
		(isalpha(*tmp_it) || isdigit(*tmp_it)) && 
		*tmp_it != ' ');
	if (str_to_tok.find(string(cur_it, tmp_it)) == str_to_tok.cend()) return tmp_it;
	return cur_it;
}

Lexer::sci Lexer::check_str_lit() const {
	if (*cur_it != '"') return cur_it;
	auto tmp_it = cur_it;

	do ++tmp_it; while (tmp_it != content.cend() && *tmp_it != '"');
	if (tmp_it == content.cend()) throw runtime_error("Missing \"");
	return ++tmp_it;
}

Lexer::sci Lexer::check_num_lit() const {
	bool allow_dec = true;
	// Goes on until there are two decimals, or there is a non-digit character
	auto tmp_it = cur_it;
	while (tmp_it != content.cend()
		&& (isdigit(*tmp_it) || *tmp_it == '.')) {

		if (*tmp_it == '.' && !allow_dec)
			throw runtime_error("Too many decimals");
		else if (*tmp_it == '.')
			allow_dec = false;
		tmp_it++;
	}
	return tmp_it;
}
