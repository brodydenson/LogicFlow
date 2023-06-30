#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Parser.h"

class Interpreter {
public:
  static EnvPtr global_env;
  static void set_parser(const Parser &_parser) { parser = _parser; } 
	static void interpret();
private:
	static Parser parser;
};

#endif
