#include "Headers/Expr.h"

using std::shared_ptr;
using std::list;
using std::string;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::runtime_error;
using tok_t::TokType;

PrimObjPtr BinOp::eval(const EnvPtr env) const {
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
		throw runtime_error("Invalid binary operator '" + op->to_str() + "'");
	} // switch op type
}

PrimObjPtr Unary::eval(const EnvPtr env) const { 
	switch (op->type) {
		case TokType::BANG:
		return !*(rhs->eval(env));
		case TokType::MINUS:
		return -*(rhs->eval(env));
		default:
		throw runtime_error("Invalid unary operator");
	}
}

PrimObjPtr Logical::eval(const EnvPtr env) const {
	switch (op->type) {
		case TokType::AND:
		return *lhs->eval(env) && *rhs->eval(env);
		case TokType::OR:
		return *lhs->eval(env) || *rhs->eval(env);
		default:
		throw runtime_error("Invalid logical operator '" + op->to_str() + "'");
	} // switch op type
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
	if (!func_obj) throw runtime_error("Invalid callable object");

	list<PrimObjPtr> args_objs;
  for (auto &arg : args)
		args_objs.push_back(arg->eval(env));
	
	return func_obj->call(args_objs);
}


