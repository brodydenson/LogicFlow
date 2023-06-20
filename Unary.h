#ifndef UNARY_H
#define UNARY_H

#include "Expr.h"
#include "Tok.h"
#include "PrimObj.h"

class Unary: public Expr {
public:
	Unary(const ExprPtr _rhs, Tok _op) : rhs(_rhs), op(_op) { }
	void print_expr(std::ostream &os) const
		{ os << tok_t::tok_to_str[op.type] << *rhs; }
	PrimObjPtr eval() const;
private:
	const ExprPtr rhs;
	Tok op;
};

#endif
