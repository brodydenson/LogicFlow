#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Parser.h"

class Interpreter {
public:
	Interpreter(const Parser &_parser) : parser(_parser) { }

	void interpret();
private:
	Parser parser;
};

#endif
