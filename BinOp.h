#ifndef BIN_OP_H
#define BIN_OP_H

#include <iostream>
#include "Expr.h"
#include "Tok.h"

class BinOp : public Expr {
public:
	BinOp(const ExprPtr _lhs, const ExprPtr _rhs, Tok _op)
	: lhs(_lhs), rhs(_rhs), op(_op) { }
	void print_expr(std::ostream &os) const
		{ os << '(' << *lhs << tok_t::tok_to_str[op.type] << *rhs << ')'; }
	PrimObjPtr eval() const;
private:
	const ExprPtr lhs;
	const ExprPtr rhs;
	const Tok op;
};

// template <typename T>
// T BinOp<T>::eval() const {
// 	switch (type) {
// 		case Add: return lhs.eval() + rhs.eval();
// 		case Sub: return lhs.eval() - rhs.eval();
// 		case Mul: return lhs.eval() * rhs.eval();
// 		case Div: 
// 			if (rhs.eval() == 0) { throw std::runtime_error("Division by 0"); }
// 			return lhs.eval() / rhs.eval();
// 	} // switch type
// 	throw std::runtime_error("No matching operation");
// }
//
#endif
