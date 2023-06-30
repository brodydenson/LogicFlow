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
	PrimObjPtr define(TokPtr, PrimObjPtr); 
	PrimObjPtr assign(TokPtr, PrimObjPtr); 
	PrimObjPtr get(TokPtr) const;
	EnvPtr get_enclosing() const { return enclosing; }
	bool contains(TokPtr) const;
private:
	const EnvPtr enclosing;
	std::map<std::string, PrimObjPtr> vals;
};

#endif
