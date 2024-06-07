#include <iostream>
#include <memory>
#include "Env.h"
#include "Exception.h"

using std::runtime_error;
using std::dynamic_pointer_cast;
using std::string;
using tok_t::TokType;

PrimObjPtr Env::define(const TokPtr &name, const PrimObjPtr &val) {
	if (name->type != TokType::IDENTIFIER)
		throw ProgError("Token type must be of type identifier", name);
	string name_str = dynamic_pointer_cast<StrObj>(name->lit_obj)->data;
  vals[name_str] = val;
	return val;
}

PrimObjPtr Env::assign(const TokPtr &name, const PrimObjPtr &val) {
	if (name->type != TokType::IDENTIFIER)
		throw ProgError("Token type must be of type identifier", name);
	string name_str = dynamic_pointer_cast<StrObj>(name->lit_obj)->data;

	auto found = vals.find(name_str);
	if (found == vals.cend()) {
		if (enclosing == nullptr)
			throw ProgError("Undefined variable " + name_str, name);
		return enclosing->assign(name, val);
	}

	found->second = val;
	return val;
}

PrimObjPtr Env::get(const TokPtr &name) const {
	if (name->type != TokType::IDENTIFIER)
		throw ProgError("Token type must be of type identifier", name);
	string name_str = dynamic_pointer_cast<StrObj>(name->lit_obj)->data;

	auto found = vals.find(name_str);
	if (found == vals.cend()) {
		if (enclosing == nullptr)
			throw ProgError("Undefined variable " + name_str, name);
		return enclosing->get(name);
	}

  return found->second;
}

bool Env::contains(const TokPtr &name) const {
	if (name->type != TokType::IDENTIFIER)
		throw ProgError("Token type must be of type identifier", name);
	string name_str = dynamic_pointer_cast<StrObj>(name->lit_obj)->data;
	return vals.find(name_str) != vals.cend();
}
