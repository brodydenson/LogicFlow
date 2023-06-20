#include <iostream>
#include "Logical.h"

using std::runtime_error;
using tok_t::TokType;

PrimObjPtr Logical::eval() const {
	switch (op.type) {
		case TokType::AND:
		return *lhs->eval() && *rhs->eval();
		case TokType::OR:
		return *lhs->eval() || *rhs->eval();
		default:
		throw runtime_error("Invalid logical operator '" + op.to_string() + "'");
	} // switch op type
}
