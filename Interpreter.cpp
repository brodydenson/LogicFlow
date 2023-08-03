#include "include/Interpreter.h"
#include "include/Exception.h"
#include "include/Tok.h"
#include "include/MySet.h"

using std::cerr;
using std::endl;
using tok_t::TokType;
using std::make_shared;

const EnvPtr Interpreter::global_env = std::make_shared<Env>(nullptr);

const TokPtr Interpreter::z_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("Z"));
const TokPtr Interpreter::uz_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("uZ"));
const TokPtr Interpreter::nz_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("nZ"));

const TokPtr Interpreter::to_int_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("int"));
const TokPtr Interpreter::to_double_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("double"));
const TokPtr Interpreter::to_str_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("str"));
const TokPtr Interpreter::to_bool_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("bool"));
const TokPtr Interpreter::to_arr_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("arr"));
const TokPtr Interpreter::to_set_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("set"));

void Interpreter::build_env() {
  // Pre defined sets
  const auto z_set = make_shared<ZDomain>();
  const auto uz_set = make_shared<ZDomain>(1);
  const auto nz_set = make_shared<ZDomain>(LONG_MIN, -1);
  global_env->define(z_tok, make_shared<SetObj>(z_set));
  global_env->define(uz_tok, make_shared<SetObj>(uz_set));
  global_env->define(nz_tok, make_shared<SetObj>(nz_set));

  // Type conversion callables
  global_env->define(to_int_tok, make_shared<ToInt>());
  global_env->define(to_double_tok, make_shared<ToDouble>());
  global_env->define(to_str_tok, make_shared<ToStr>());
  global_env->define(to_bool_tok, make_shared<ToBool>());
  global_env->define(to_arr_tok, make_shared<ToArr>());
  global_env->define(to_set_tok, make_shared<ToSet>());
}

Parser Interpreter::parser;

void Interpreter::interpret() {
	for (auto &stmt : parser.parse()) {
    try {
      stmt->exec(global_env);
    } catch (const ProgError &e) {
      cerr << "Runtime Error: " << e.err_msg() << endl;
      exit(0);
    }
	}
}
