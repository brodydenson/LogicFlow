#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include "include/Lexer.h"
#include "include/Tok.h"
#include "include/Exception.h"

using std::string;
using std::vector;
using std::istringstream;
using std::cout;
using std::ostream;
using std::set;
using std::isalpha;
using std::isdigit;
using std::stod;
using std::cerr;
using std::endl;
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

Lexer::Lexer() : cur_line(1) { }

Lexer::Lexer(const string &_content) : cur_line(1) { *this = _content; }

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
	while (cur_it != content.cend() && isspace(static_cast<unsigned char>(*cur_it))) {
    if (*cur_it == '\n') 
      ++cur_line;
    ++cur_it;
  }
  if (cur_it == content.cend()) return nullptr;

	const auto beg = cur_it;
	const auto op_end = check_op();
	const auto key_end = check_key();
	const auto id_lit_end = check_id_lit();
	const auto str_lit_end = check_str_lit();
	const auto num_lit_end = check_num_lit();

	// cout << *op_end << ' ' << *var_or_key_end << ' ' << *lit_end << '\n';

	TokType type;
	if (op_end != cur_it) 
		{ cur_it = op_end; return make_shared<Tok>(string(beg, op_end), cur_line); }
	else if (key_end != cur_it) 
		{ cur_it = key_end; return make_shared<Tok>(string(beg, key_end), cur_line); }
	else if (id_lit_end != cur_it) 
		{ cur_it = id_lit_end; return make_shared<Tok>(TokType::IDENTIFIER, 
								make_shared<StrObj>(string(beg, id_lit_end)), cur_line); }
	// String literal needs to trim off the excess
	else if (str_lit_end != cur_it) 
		{ cur_it = str_lit_end; return make_shared<Tok>(TokType::STRING, 
								 make_shared<StrObj>(string(beg+1, str_lit_end-1)), cur_line); }
	else if (num_lit_end != cur_it) {
    cur_it = num_lit_end; 
    const double num = stod(string(beg, num_lit_end));
    PrimObjPtr lit_obj;
    if (num == static_cast<int>(num))
      lit_obj = make_shared<IntObj>(num);
    else
      lit_obj = make_shared<DoubleObj>(num);
    return make_shared<Tok>(TokType::NUMBER, lit_obj, cur_line);
  }

  throw ProgError("Token unrecognizable", make_shared<Tok>(TokType::END, cur_line));
	// throw logic_error("No matching case for current character"); 
}

void Lexer::tokenize() {
	toks.clear();
  TokPtr tok;
  try {
    while ((tok = next_tok())) 
      toks.push_back(tok);
  } catch (ProgError e) {
    cerr << "Syntax Error: " << e.err_msg() << endl;
    exit(0);
  }
	toks.push_back(make_shared<Tok>(TokType::END));
}

Lexer::sci Lexer::check_op() const {
	auto tmp_it = cur_it;
	while (tmp_it != content.cend() && 
		!isalpha(*tmp_it) &&
		!isdigit(*tmp_it) &&
		some_type_same_len(string(cur_it, tmp_it + 1))) ++tmp_it;
	if (cur_it != tmp_it && str_to_tok.find(string(cur_it, tmp_it)) == str_to_tok.cend()) 
		throw ProgError("Invalid operator token", make_shared<Tok>(TokType::END, cur_line));
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
	if (tmp_it == content.cend())
		throw ProgError("Missing \"", make_shared<Tok>(TokType::END, cur_line));
	return ++tmp_it;
}

Lexer::sci Lexer::check_num_lit() const {
	bool allow_dec = true;
	// Goes on until there are two decimals, or there is a non-digit character
	auto tmp_it = cur_it;
	while (tmp_it != content.cend()
		&& (isdigit(*tmp_it) || *tmp_it == '.')) {

		if (*tmp_it == '.' && !allow_dec)
      return cur_it;
      // throw ProgError("Too many decimals", make_shared<Tok>(TokType::END, cur_line));
		else if (*tmp_it == '.')
			allow_dec = false;
		tmp_it++;
	}
	return tmp_it;
}
