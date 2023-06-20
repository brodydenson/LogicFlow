#ifndef CALL_H
#define CALL_H

#include <iostream>
#include <list>
#include "Expr.h"
#include "Tok.h"

class Call : public Expr {
public:
	Call(const ExprPtr _callee, const Tok _paren, const std::list<ExprPtr> &_args)
	: callee(_callee), paren(_paren), args(_args) { }
	void print_expr(std::ostream &os) const;
	PrimObjPtr eval() const;
private:
	const ExprPtr callee;
	const Tok paren; // TODO: Throw where error occurs
	const std::list<ExprPtr> args;
};

#endif
