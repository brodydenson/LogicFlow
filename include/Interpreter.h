#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Parser.h"

class Interpreter {
public:
  static const EnvPtr global_env;
  static const TokPtr z_tok;
  static const TokPtr uz_tok;
  static const TokPtr nz_tok;
  static const TokPtr to_int_tok;
  static const TokPtr to_double_tok;
  static const TokPtr to_str_tok;
  static const TokPtr to_bool_tok;
  static const TokPtr to_arr_tok;
  static const TokPtr to_set_tok;

  static void set_parser(const Parser &_parser) { parser = _parser; } 
  static void build_env();
	static void interpret();
private:
	static Parser parser;
};

#endif
