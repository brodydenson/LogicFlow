#ifndef EXPR_H
#define EXPR_H

#include <iostream>
#include <memory>
#include "PrimObj.h"
#include "Env.h"

class Expr {
friend std::ostream &operator<<(std::ostream &os, const Expr &expr)
	{ os << expr.to_str(); return os; }
public:
	virtual ~Expr() = default;
	virtual std::string to_str() const = 0;
	virtual PrimObjPtr eval(const EnvPtr&) const = 0;
};

typedef std::shared_ptr<Expr> ExprPtr;

class BinOp : public Expr {
public:
	BinOp(const ExprPtr &_lhs, const ExprPtr &_rhs, const TokPtr &_op)
    : lhs(_lhs), rhs(_rhs), op(_op) { }

  std::string to_str() const
		{ return '(' + lhs->to_str() + tok_t::tok_to_str[op->type] + rhs->to_str() + ')'; }
	PrimObjPtr eval(const EnvPtr&) const;
private:
	const ExprPtr lhs;
	const ExprPtr rhs;
	const TokPtr op;
};

class Unary: public Expr {
public:
	Unary(const ExprPtr &_rhs, const TokPtr &_op) : rhs(_rhs), op(_op) { }

  std::string to_str() const
		{ return tok_t::tok_to_str[op->type] + rhs->to_str(); }
	PrimObjPtr eval(const EnvPtr&) const;
private:
	const ExprPtr rhs;
	const TokPtr op;
};

class Logical: public Expr {
public:
	Logical(const ExprPtr &_lhs, const ExprPtr &_rhs, const TokPtr &_op)
    : lhs(_lhs), rhs(_rhs), op(_op) { }

  std::string to_str() const
		{ return '(' + lhs->to_str() + tok_t::tok_to_str[op->type] + rhs->to_str() + ')'; }
	PrimObjPtr eval(const EnvPtr&) const;
private:
	const ExprPtr lhs;
	const ExprPtr rhs;
	const TokPtr op;
};

class Lit : public Expr {
public:
	Lit(const PrimObjPtr &_obj) : obj(_obj) { } // No debug

  std::string to_str() const { return obj->to_str(); }
	PrimObjPtr eval(const EnvPtr &env) const { return obj; }
private:
	const PrimObjPtr obj;
};

class Grouping : public Expr {
public:
	Grouping(const ExprPtr &_expr) : expr(_expr) { }

  std::string to_str() const { return '(' + expr->to_str() + ')'; }
	PrimObjPtr eval(const EnvPtr &env) const { return expr->eval(env); }
private:
	const ExprPtr expr;
};

class Var : public Expr {
public:
	Var(const TokPtr &_name) : name(_name) { }

  std::string to_str() const { return name->to_str(); }
	PrimObjPtr eval(const EnvPtr &env) const { return env->get(name); }
	TokPtr get_name() const { return name; }
private:
	const TokPtr name;
};

class Asgn : public Expr {
public:
	Asgn(const TokPtr &_name, const ExprPtr &_val)
    : name(_name), val(_val) { }

  std::string to_str() const
		{ return '(' + std::static_pointer_cast<StrObj>(name->lit_obj)->data 
			+ " = " + val->to_str() + ')'; }
	PrimObjPtr eval(const EnvPtr &env) const 
		{ return env->assign(name, val->eval(env)); }
private:
	const TokPtr name;
	const ExprPtr val;
};

class Call : public Expr {
public:
	Call(const ExprPtr &_callee, const TokPtr &_paren)
    : callee(_callee), paren(_paren) { }
	Call(const ExprPtr &_callee, const TokPtr &_paren, const std::list<ExprPtr> &_args)
    : callee(_callee), paren(_paren), args(_args) { }

  std::string to_str() const;
	PrimObjPtr eval(const EnvPtr&) const;
private:
	const ExprPtr callee;
	const TokPtr paren;
	const std::list<ExprPtr> args;
};

class Arr : public Expr {
public:
  Arr(const std::vector<ExprPtr> &_data) : data(_data) { }

  std::string to_str() const;
  PrimObjPtr eval(const EnvPtr&) const;
private:
  const std::vector<ExprPtr> data;
};

class Set : public Expr {
public:
  Set(const ExprPtr &_ret, const TokPtr &_var_name, const ExprPtr &_domain)
    : ret(_ret), var_name(_var_name), domain(_domain) { }
  Set(const ExprPtr &_ret, const TokPtr &_var_name, 
      const ExprPtr &_domain, const ExprPtr &_conditions)
    : ret(_ret), var_name(_var_name), domain(_domain), conditions(_conditions) { }

  std::string to_str() const;
  PrimObjPtr eval(const EnvPtr&) const;
private:
  const ExprPtr ret;
  const TokPtr var_name;
  const ExprPtr domain;
  const ExprPtr conditions;
};

#endif
