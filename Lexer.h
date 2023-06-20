#ifndef LEXER_H
#define LEXER_H

#include <list>
#include <set>
#include <string>
#include <map>
#include <vector>
#include "Tok.h"

class Parser;

class Lexer {

typedef std::string::const_iterator sci;
public:
	friend Parser;
	friend std::ostream &operator<<(std::ostream&, const Lexer&);

	// Defualt constructor
	Lexer();
	Lexer(const std::string&);
	Lexer(const Lexer&) = default;
	Lexer &operator=(const std::string&);

private:
	sci cur_it;
	std::list<Tok> toks;
	std::string content;

	inline bool match(char);
	Tok next_tok();
	void tokenize();

	// static inline bool is_op(const char&);
	// static inline bool is_key(const std::string&);

	std::set<char> valid_chars(const std::set<std::string>&) const;
	sci check_op() const;
	sci check_key() const;
	sci check_id_lit() const;
	sci check_str_lit() const;
	sci check_num_lit() const;
};

#endif

// check_op (Old)
	// const auto beg = it;
	// bool next = true;
	// while (next) {
	// 	next = false;
	// 	string tok_seg(beg, it);
	// 	for (auto &op : ops) {
	// 		// cout << "cur_tok: " << cur_tok << '\n';
	// 		// cout << "op: " << op 
	// 		// 	<< "\t opsubstr: " << substr_op << '\n';
	// 		if (op.length() <= it - beg) { continue; }
	// 		string op_seg = op.substr(0, it - beg);
	// 		if (op_seg == tok_seg) {
	// 			next = true;
	// 			++it;
	// 			break;
	// 		}
	// 	}
	// }
	// auto found_tok = find(ops.cbegin(), ops.cend(), string(beg, it));
	// if (found_tok == ops.cend()) {
	// 	// TODO: Handle error
	// 	throw std::runtime_error("Unkown operator: '" + string(beg, it) + "'");
	// }
	// return it;
	// return Tok{ string(beg, it), Op };
	// switch (*(curr_it++)) {
	// case '(':
	// 	return Tok(TokType::LEFT_PAREN);
	// case ')':
	// 	return Tok(TokType::RIGHT_PAREN);
	// case '+':
	// 	return Tok(TokType::PLUS);
	// case '-':
	// 	return Tok(TokType::MINUS);
	// case '*':
	// 	return Tok(TokType::STAR);
	// case '/':
	// 	return Tok(TokType::SLASH);
	// case '!':
	// 	return match('=') ? Tok(TokType::BANG_EQUAL) : Tok(TokType::BANG);
	// case '=':
	// 	return match('=') ? Tok(TokType::EQUAL_EQUAL) : Tok(TokType::EQUAL);
	// case '>':
	// 	return match('=') ? Tok(TokType::GREATER_EQUAL) : Tok(TokType::GREATER);
	// case '<':
	// 	return match('=') ? Tok(TokType::LESS_EQUAL) : Tok(TokType::LESS);
	// default:
	// 	--curr_it;
	// } // switch curr_it
