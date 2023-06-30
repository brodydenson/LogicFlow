#include "include/Expr.h"
#include "include/Exception.h"

using std::shared_ptr;
using std::list;
using std::string;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::runtime_error;
using tok_t::TokType;

PrimObjPtr BinOp::eval(const EnvPtr env) const {
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

PrimObjPtr Unary::eval(const EnvPtr env) const { 
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

PrimObjPtr Logical::eval(const EnvPtr env) const {
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
PrimObjPtr Call::eval(EnvPtr env) const {
	auto func_obj = dynamic_pointer_cast<FuncObj>(callee->eval(env));
	if (!func_obj) throw ProgError("Invalid callable object", paren);

	list<PrimObjPtr> args_objs;
  for (auto &arg : args)
		args_objs.push_back(arg->eval(env));
	
	return func_obj->call(args_objs);
}


