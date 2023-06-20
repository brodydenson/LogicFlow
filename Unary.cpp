#include <memory>
#include "Unary.h"

using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::make_shared;
using std::logic_error;
using tok_t::TokType;

PrimObjPtr Unary::eval() const { 
	switch (op.type) {
		case TokType::BANG:
		return !*(rhs->eval());
		case TokType::MINUS:
		return -*(rhs->eval());
		default:
		throw logic_error("Invalid unary operator");
	}
}
