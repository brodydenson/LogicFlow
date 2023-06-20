#include <memory>
#include "BinOp.h"

using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::runtime_error;
using tok_t::TokType;

PrimObjPtr BinOp::eval() const {
	switch (op.type) {
		case TokType::PLUS:
		return *lhs->eval() + *rhs->eval();
		case TokType::MINUS:
		return *lhs->eval() - *rhs->eval();
		case TokType::STAR:
		return *lhs->eval() * *rhs->eval();
		case TokType::SLASH:
		return *lhs->eval() / *rhs->eval();
		case TokType::GREATER:
		return *lhs->eval() > *rhs->eval();
		case TokType::GREATER_EQUAL:
		return *lhs->eval() >= *rhs->eval();
		case TokType::LESS:
		return *lhs->eval() < *rhs->eval();
		case TokType::LESS_EQUAL:
		return *lhs->eval() <= *rhs->eval();
		case TokType::EQUAL_EQUAL:
		return *lhs->eval() == *rhs->eval();
		case TokType::BANG_EQUAL:
		return *lhs->eval() != *rhs->eval();
		default:
		throw runtime_error("Invalid binary operator '" + op.to_string() + "'");
	} // switch op type
}
