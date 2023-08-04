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
const TokPtr Interpreter::pz_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("pZ"));
const TokPtr Interpreter::nz_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("nZ"));

const TokPtr Interpreter::to_int_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("int_1"));
const TokPtr Interpreter::to_double_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("double_1"));
const TokPtr Interpreter::to_str_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("str_1"));
const TokPtr Interpreter::to_bool_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("bool_1"));
const TokPtr Interpreter::to_arr_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("arr_1"));
const TokPtr Interpreter::to_arr2_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("arr_2"));
const TokPtr Interpreter::to_arr3_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("arr_3"));
const TokPtr Interpreter::to_set_tok = make_shared<Tok>(TokType::IDENTIFIER, make_shared<StrObj>("set_1"));

void Interpreter::build_env() {
  // Pre defined sets
  const auto z_set = make_shared<ZDomain>();
  const auto pz_set = make_shared<PosZDomain>();
  const auto nz_set = make_shared<NegZDomain>();
  global_env->define(z_tok, make_shared<SetObj>(z_set));
  global_env->define(pz_tok, make_shared<SetObj>(pz_set));
  global_env->define(nz_tok, make_shared<SetObj>(nz_set));

  // Type conversion callables
  global_env->define(to_int_tok, make_shared<ToInt>());
  global_env->define(to_double_tok, make_shared<ToDouble>());
  global_env->define(to_str_tok, make_shared<ToStr>());
  global_env->define(to_bool_tok, make_shared<ToBool>());
  global_env->define(to_arr_tok, make_shared<ToArr>());
  global_env->define(to_arr2_tok, make_shared<ToArr2>());
  global_env->define(to_arr3_tok, make_shared<ToArr3>());
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
