#ifndef EXPR_H
#define EXPR_H

#include <iostream>
#include <memory>
#include "PrimObj.h"

class Expr {
friend std::ostream &operator<<(std::ostream &os, const Expr &expr)
	{ expr.print_expr(os); return os; }
public:
	virtual ~Expr() = default;
	virtual void print_expr(std::ostream&) const = 0;
	virtual PrimObjPtr eval() const = 0;
};

typedef std::shared_ptr<Expr> ExprPtr;

#endif
