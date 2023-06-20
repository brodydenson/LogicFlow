#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include "Stmt.h"
#include "Expr.h"
#include "Tok.h"

class Func : public Expr {
public:
	Func(const Tok &_name, const std::list<Tok> &_params, StmtPtr _body)
		: name(_name), params(_params), body(_body) { }
	void print_expr(std::ostream &os) const
		{ os << name << '(' << params.size() << ')' << body; }
	PrimObjPtr eval() const;
private:
	const Tok name;
	const std::list<Tok> params;
	const StmtPtr body;
};

#endif
