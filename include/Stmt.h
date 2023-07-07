#ifndef STMT_H
#define STMT_H

#include <memory>
#include <list>
#include <iostream>
#include "Env.h"
#include "Expr.h"
#include "PrimObj.h"
#include "Tok.h"


class Stmt {
friend std::ostream &operator<<(std::ostream &os, const Stmt &stmt)
	{ os << stmt.to_str(); return os; }
friend Env;
public:
	virtual ~Stmt() = default;

	virtual std::string to_str() const = 0;

	virtual void exec(const EnvPtr&) = 0;
};

typedef std::shared_ptr<Stmt> StmtPtr;

class ExprStmt : public Stmt {
public:
	ExprStmt(const ExprPtr &_expr) : expr(_expr) { }

  std::string to_str() const { return expr->to_str(); }

	void exec(const EnvPtr &env) { expr->eval(env); }
private:
	const ExprPtr expr;
};

class IfStmt : public Stmt {
public:
	IfStmt(const ExprPtr &_condition, const StmtPtr &_then_branch) 
		: condition(_condition), then_branch(_then_branch) { }
	IfStmt(const ExprPtr &_condition, const StmtPtr &_then_branch, const StmtPtr &_else_branch) 
		: condition(_condition), then_branch(_then_branch), 
		else_branch(_else_branch) { }

  std::string to_str() const;

	void exec(const EnvPtr&);
private:
	const ExprPtr condition;
	const StmtPtr then_branch;
	const StmtPtr else_branch;
};

class PrintStmt : public Stmt {
public:
	PrintStmt(const ExprPtr &_val) : val(_val) { }

  std::string to_str() const { return val->to_str(); }

	void exec(const EnvPtr &env) 
    { std::cout << *val->eval(env) << std::endl; }
private:
	const ExprPtr val;
};

class VarDeclStmt : public Stmt {
public:
	VarDeclStmt(const TokPtr &_name) : name(_name) { }
	VarDeclStmt(const TokPtr &_name, const ExprPtr &_initializer) 
		: name(_name), initializer(_initializer) { }

  std::string to_str() const 
		{ return name->to_str() + " = " + initializer->to_str(); }

	void exec(const EnvPtr &env) 
		{ env->define(name, initializer != nullptr 
				   ? initializer->eval(env) : std::make_shared<DoubleObj>(0)); }
private:
	const TokPtr name;
	const ExprPtr initializer;
	const EnvPtr env;
};

class WhileStmt : public Stmt {
public:
	WhileStmt(const ExprPtr &_condition, const StmtPtr &_body) 
		: condition(_condition), body(_body) { }

  std::string to_str() const 
		{ return "while " + condition->to_str() + ", then " + body->to_str(); }

	void exec(const EnvPtr &env) 
		{ while (condition->eval(env)->to_bool()) body->exec(env); }
private:
	const ExprPtr condition;
	const StmtPtr body;
};

class BlockStmt : public Stmt {
public:
	BlockStmt(const std::list<StmtPtr> &_stmts) : stmts(_stmts) { }

  std::string to_str() const;

	void exec(const EnvPtr&);
private:
	const std::list<StmtPtr> stmts;
};

class FuncObj;
class FuncStmt : public Stmt {
friend FuncObj;
public:
	FuncStmt(const TokPtr &_name, const std::list<TokPtr> &_params, const StmtPtr &_body)
		: name(_name), params(_params), body(_body) { }
  FuncStmt(const FuncStmt&) = default;

  std::string to_str() const;

	void exec(const EnvPtr&);
private:
	const TokPtr name;
	const std::list<TokPtr> params;
	const StmtPtr body;
};

class ReturnStmt : public Stmt {
public:
	ReturnStmt(const ExprPtr &_val) : val(_val) { }
	ReturnStmt() { }
  ReturnStmt(const ReturnStmt&) = default;

  std::string to_str() const { return "return " + val->to_str(); }

	void exec(const EnvPtr&);
private:
	const ExprPtr val;
};

#endif
