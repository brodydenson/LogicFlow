#ifndef GROUPING_H
#define GROUPING_H

#include <iostream>
#include "Expr.h"

class Grouping : public Expr {
public:
	Grouping(const ExprPtr _expr) : expr(_expr) { }
	void print_expr(std::ostream &os) const { os << '(' << *expr << ')'; }
	PrimObjPtr eval() const { return expr->eval(); }
private:
	const ExprPtr expr;
};

#endif
