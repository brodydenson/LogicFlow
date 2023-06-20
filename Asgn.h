#ifndef ASGN_H
#define ASGN_H

#include <iostream>
#include "Expr.h"
#include "Tok.h"
#include "Env.h"

class Asgn : public Expr {
public:
	Asgn(const Tok &_name, ExprPtr _val, EnvPtr _env)
	: name(_name), val(_val), env(_env) { }
	void print_expr(std::ostream &os) const
		{ os << '(' << std::static_pointer_cast<StrObj>(name.lit_obj)->data 
			<< " = " << *val << ')'; }
	PrimObjPtr eval() const 
		{ return env->assign(name, val->eval()); }
private:
	const Tok name;
	const ExprPtr val;
	const EnvPtr env;
};

#endif
