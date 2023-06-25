#include "Headers/Stmt.h"
#include "Headers/Exception.h"

using std::to_string;
using std::string;

string IfStmt::to_str() const {
  string s = "if " + condition->to_str() + ", then " + then_branch->to_str();
  if (else_branch) s += else_branch->to_str();
  return s;
}
void IfStmt::exec(const EnvPtr &env) {
  if (condition->eval(env)->to_bool())
    then_branch->exec(env); 
  else if (else_branch)
    else_branch->exec(env);
}

string BlockStmt::to_str() const {
  string s;
  for (auto it = stmts.cbegin(); it != stmts.cend(); ++it) 
    s += (*it)->to_str() + '\n';
  return s;
}

void BlockStmt::exec(const EnvPtr &enclosing_env) {
  const EnvPtr env = std::make_shared<Env>(enclosing_env);
  for (auto it = stmts.cbegin(); it != stmts.cend(); ++it)
    (*it)->exec(env);
}

string FuncStmt::to_str() const {
  return name->to_str() + '(' + to_string(params.size()) + ')' + body->to_str();
}
void FuncStmt::exec(const EnvPtr &env) {
  const auto func = std::make_shared<FuncObj>(std::make_shared<FuncStmt>(*this)); 
  env->define(name, func);
}

void ReturnStmt::exec(const EnvPtr &env) {
  throw ReturnExcept(val->eval(env));
}
