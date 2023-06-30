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
	unsigned cur_line;
	std::list<TokPtr> toks;
	std::string content;

	inline bool match(const char);
	TokPtr next_tok();
	void tokenize();

	sci check_op() const;
	sci check_key() const;
	sci check_id_lit() const;
	sci check_str_lit() const;
	sci check_num_lit() const;
};

#endif
