#include "include/Expr.h"
#include "include/Exception.h"
#include "include/MySet.h"
#include "include/Stmt.h"

using std::shared_ptr;
using std::list;
using std::vector;
using std::string;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::runtime_error;
using tok_t::TokType;

PrimObjPtr BinOp::eval(const EnvPtr &env) const {
  try {
	switch (op->type) {
		case TokType::PLUS:
		return *lhs->eval(env) + *rhs->eval(env);
		case TokType::MINUS:
		return *lhs->eval(env) - *rhs->eval(env);
		case TokType::STAR:
		return *lhs->eval(env) * *rhs->eval(env);
		case TokType::SLASH:
		return *lhs->eval(env) / *rhs->eval(env);
		case TokType::GREATER:
		return *lhs->eval(env) > *rhs->eval(env);
		case TokType::GREATER_EQUAL:
		return *lhs->eval(env) >= *rhs->eval(env);
		case TokType::LESS:
		return *lhs->eval(env) < *rhs->eval(env);
		case TokType::LESS_EQUAL:
		return *lhs->eval(env) <= *rhs->eval(env);
		case TokType::EQUAL_EQUAL:
		return *lhs->eval(env) == *rhs->eval(env);
		case TokType::BANG_EQUAL:
		return *lhs->eval(env) != *rhs->eval(env);
		default:
		throw ProgError("Invalid binary operator '" + op->to_str() + "'", op);
	} // switch op type
  } catch (runtime_error e) {
    throw ProgError(e.what(), op);
  }
}

PrimObjPtr Unary::eval(const EnvPtr &env) const { 
  try {
	switch (op->type) {
		case TokType::BANG:
		return !*(rhs->eval(env));
		case TokType::MINUS:
		return -*(rhs->eval(env));
		default:
		throw ProgError("Invalid unary operator", op);
	}
  } catch (runtime_error e) {
    throw ProgError(e.what(), op);
  }
}

PrimObjPtr Logical::eval(const EnvPtr &env) const {
  try {
	switch (op->type) {
		case TokType::AND:
		return *lhs->eval(env) && *rhs->eval(env);
		case TokType::OR:
		return *lhs->eval(env) || *rhs->eval(env);
		default:
		throw ProgError("Invalid logical operator '" + op->to_str() + "'", op);
	} // switch op type
  } catch (runtime_error e) {
    throw ProgError(e.what(), op);
  }
}



string Call::to_str() const {
  string s = callee->to_str() + '(';
	// Probably a much cleaner way of doing this... too bad
	for (auto it = args.cbegin(); it != args.cend(); ++it)
		{ s += (*it)->to_str(); if (++std::move(it) != args.cend()) s += ", "; }
	s += ')';
  return s;
}
PrimObjPtr Call::eval(const EnvPtr &env) const {
	auto func_obj = dynamic_pointer_cast<FuncObj>(callee->eval(env));
	if (!func_obj) throw ProgError("Invalid callable object", paren);

	list<PrimObjPtr> args_objs;
  for (auto &arg : args)
		args_objs.push_back(arg->eval(env));
	
	return func_obj->call(args_objs);
}

string Arr::to_str() const {
  // Copy of ArrObj to_str method
  string s = "[";
  for (auto it = data.cbegin(); it != data.cend(); ++it)
    s += it + 1 != data.cend() ? ((*it)->to_str() + ", ") : ((*it)->to_str() + "]");
  return s;
}
PrimObjPtr Arr::eval(const EnvPtr &env) const {
  vector<PrimObjPtr> prim_obj_arr;
  for (const auto &i : data)
    prim_obj_arr.push_back(i->eval(env));
  return make_shared<ArrObj>(prim_obj_arr);
}


string Set::to_str() const {
  return "{ " + ret->to_str() + " | " + var_name->to_str() + " in " + domain->to_str() + " }";
}
PrimObjPtr Set::eval(const EnvPtr &env) const {
  const auto ret_stmt = make_shared<ReturnStmt>(ret);
  const auto func_stmt = make_shared<FuncStmt>(nullptr, list<TokPtr>({ var_name }), ret_stmt);
  const auto func = make_shared<FuncObj>(func_stmt);

  const DomainPtr my_domain = domain->eval(env)->to_set();
  const auto my_set = make_shared<MySet>(my_domain, func);

  return make_shared<SetObj>(my_set);
}
