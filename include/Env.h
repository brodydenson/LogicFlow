#ifndef ENV_H
#define ENV_H

#include <map>
#include <string>
#include <memory>
#include "PrimObj.h"
#include "Tok.h"

class Env;
typedef std::shared_ptr<Env> EnvPtr;

class Env {
public:
	Env(EnvPtr _enclosing) : enclosing(_enclosing) { }
	PrimObjPtr define(const TokPtr&, const PrimObjPtr&); 
	PrimObjPtr assign(const TokPtr&, const PrimObjPtr&); 
	PrimObjPtr get(const TokPtr&) const;
	EnvPtr get_enclosing() const { return enclosing; }
	bool contains(const TokPtr&) const;
private:
	const EnvPtr enclosing;
	std::map<std::string, PrimObjPtr> vals;
};

#endif
