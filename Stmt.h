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
	{ stmt.print_stmt(os); return os; }
friend Env;
public:
	virtual ~Stmt() = default;
	virtual void print_stmt(std::ostream&) const = 0;
	virtual void exec() = 0;
};

typedef std::shared_ptr<Stmt> StmtPtr;

class ExprStmt : public Stmt {
public:
	ExprStmt(ExprPtr _expr) : expr(_expr) { }
	void print_stmt(std::ostream &os) const { os << expr; }
	void exec() { expr->eval(); }
private:
	const ExprPtr expr;
};

class IfStmt : public Stmt {
public:
	IfStmt(ExprPtr _condition, StmtPtr _then_branch) 
		: condition(_condition), then_branch(_then_branch) { }
	IfStmt(ExprPtr _condition, StmtPtr _then_branch, StmtPtr _else_branch) 
		: condition(_condition), then_branch(_then_branch), 
		else_branch(_else_branch) { }
	void print_stmt(std::ostream &os) const 
		{ os << "if " << *condition << ", then " << *then_branch;
		if (else_branch) os << *else_branch; }
	void exec() 
		{ if (condition->eval()->to_bool()) then_branch->exec(); 
				else if (else_branch) else_branch->exec(); }
private:
	const ExprPtr condition;
	const StmtPtr then_branch;
	const StmtPtr else_branch;
};

class PrintStmt : public Stmt {
public:
	PrintStmt(ExprPtr _val) : val(_val) { }
	void print_stmt(std::ostream &os) const { os << *val; }
	// TODO: Use the current ostream
	void exec() { std::cout << *val->eval() << std::endl; }
private:
	const ExprPtr val;
};

class VarDeclStmt : public Stmt {
public:
	VarDeclStmt(Tok _name, EnvPtr _env) : name(_name), env(_env) { }
	VarDeclStmt(Tok _name, ExprPtr _initializer, EnvPtr _env) 
		: name(_name), initializer(_initializer), env(_env) { }
	void print_stmt(std::ostream &os) const 
		{ os << name << " = " << *initializer; }
	void exec() 
		{ env->define(name, initializer != nullptr 
				   ? initializer->eval() : std::make_shared<DoubleObj>(0)); }
private:
	const Tok name;
	const ExprPtr initializer;
	const EnvPtr env;
};

class WhileStmt : public Stmt {
public:
	WhileStmt(ExprPtr _condition, StmtPtr _body) 
		: condition(_condition), body(_body) { }
	void print_stmt(std::ostream &os) const 
		{ os << "while " << *condition << ", then " << *body; }
	void exec() 
		{ while (condition->eval()->to_bool()) body->exec(); }
private:
	const ExprPtr condition;
	const StmtPtr body;
};

class BlockStmt : public Stmt {
public:
	BlockStmt(const std::list<StmtPtr> &_stmts) : stmts(_stmts) { }
	void print_stmt(std::ostream &os) const
		{ for(auto it = stmts.cbegin(); it != stmts.cend(); ++it) 
			os << **it << '\n'; }
	void exec()
		{ for(auto it = stmts.cbegin(); it != stmts.cend(); ++it) 
			(*it)->exec(); }
private:
	const std::list<StmtPtr> stmts;
};

class FuncStmt : public Stmt {
public:
	FuncStmt(const Tok &_name, const std::list<Tok> &_params, StmtPtr _body)
		: name(_name), params(_params), body(_body) { }
	void print_stmt(std::ostream &os) const
		{ os << name << '(' << params.size() << ')' << body; }
	void exec();
private:
	const Tok name;
	const std::list<Tok> params;
	const StmtPtr body;
};

#endif
