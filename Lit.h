#ifndef LIT_H
#define LIT_H

#include <iostream>
#include "Expr.h"
#include "PrimObj.h"

class Lit : public Expr {
public:
	Lit(const PrimObjPtr _obj) : obj(_obj) { }
	void print_expr(std::ostream &os) const { os << *obj; }
	PrimObjPtr eval() const { return obj; }
private:
	const PrimObjPtr obj;
};

#endif
