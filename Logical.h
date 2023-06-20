#ifndef LOGICAL_H
#define LOGICAL_H

#include "Expr.h"
#include "Tok.h"
#include "PrimObj.h"

class Logical: public Expr {
public:
	Logical(ExprPtr _lhs, ExprPtr _rhs, const Tok &_op)
	: lhs(_lhs), rhs(_rhs), op(_op) { }
	void print_expr(std::ostream &os) const
		{ os << '(' << *lhs << tok_t::tok_to_str[op.type] << *rhs << ')'; }
	PrimObjPtr eval() const;
private:
	const ExprPtr lhs;
	const ExprPtr rhs;
	const Tok op;
};

#endif
