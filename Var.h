#ifndef VAR_H
#define VAR_H

#include <iostream>
#include "Expr.h"
#include "PrimObj.h"
#include "Tok.h"

class Var : public Expr {
public:
	Var(const Tok &_name, EnvPtr _env) : name(_name), env(_env) { }
	void print_expr(std::ostream &os) const { os << name; }
	PrimObjPtr eval() const { return env->get(name); }
	Tok get_name() const { return name; }
private:
	const Tok name;
	const EnvPtr env;
};

#endif
