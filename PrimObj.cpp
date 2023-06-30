#include <memory>
#include <iostream>
#include <list>
#include <string>
#include "include/Exception.h"
#include "include/PrimObj.h"
#include "include/Stmt.h"
#include "include/Interpreter.h"

using std::make_shared;
using std::runtime_error;
using std::list;
using std::dynamic_pointer_cast;
using std::string;

PrimObjPtr PrimObj::operator-() const { 
	throw runtime_error("Type does not support unary '-' operator");
}
PrimObjPtr PrimObj::operator!() const { 
	throw runtime_error("Type does not support unary '!' operator");
}
PrimObjPtr PrimObj::operator+(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support '+' operator");
}
PrimObjPtr PrimObj::operator-(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support '-' operator");
}
PrimObjPtr PrimObj::operator*(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support '*' operator");
}
PrimObjPtr PrimObj::operator/(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support '/' operator");
}
PrimObjPtr PrimObj::operator>(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support '>' operator");
}
PrimObjPtr PrimObj::operator>=(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support '>=' operator");
}
PrimObjPtr PrimObj::operator<(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support '<' operator");
}
PrimObjPtr PrimObj::operator<=(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support '<=' operator");
}
PrimObjPtr PrimObj::operator==(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support '==' operator");
}
PrimObjPtr PrimObj::operator!=(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support '!=' operator");
}
PrimObjPtr PrimObj::operator&&(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support 'and' operator");
}
PrimObjPtr PrimObj::operator||(const PrimObj &rhs) const { 
	throw runtime_error("Type does not support 'or' operator");
}

PrimObjPtr DoubleObj::operator-() const { 
	return make_shared<DoubleObj>(-data);
}
PrimObjPtr DoubleObj::operator!() const { 
	return make_shared<DoubleObj>(!data);
}
PrimObjPtr DoubleObj::operator+(const PrimObj &rhs) const { 
	return make_shared<DoubleObj>(data + rhs.to_double());
}
PrimObjPtr DoubleObj::operator-(const PrimObj &rhs) const { 
	return make_shared<DoubleObj>(data - rhs.to_double());
}
PrimObjPtr DoubleObj::operator*(const PrimObj &rhs) const { 
	return make_shared<DoubleObj>(data * rhs.to_double());
}
PrimObjPtr DoubleObj::operator/(const PrimObj &rhs) const { 
  if (rhs.to_double() == 0)
    throw runtime_error("Division by zero");
	return make_shared<DoubleObj>(data / rhs.to_double());
}
PrimObjPtr DoubleObj::operator>(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data > rhs.to_double());
}
PrimObjPtr DoubleObj::operator>=(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data >= rhs.to_double());
}
PrimObjPtr DoubleObj::operator<(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data < rhs.to_double());
}
PrimObjPtr DoubleObj::operator<=(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data <= rhs.to_double());
}
PrimObjPtr DoubleObj::operator==(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data == rhs.to_double());
}
PrimObjPtr DoubleObj::operator!=(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data != rhs.to_double());
}
PrimObjPtr DoubleObj::operator&&(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(to_bool() && rhs.to_bool());
}
PrimObjPtr DoubleObj::operator||(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(to_bool() || rhs.to_bool());
}

PrimObjPtr StrObj::operator+(const PrimObj &rhs) const { 
	return make_shared<StrObj>(data + rhs.to_str());
}
PrimObjPtr StrObj::operator>(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data > rhs.to_str());
}
PrimObjPtr StrObj::operator>=(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data >= rhs.to_str());
}
PrimObjPtr StrObj::operator<(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data < rhs.to_str());
}
PrimObjPtr StrObj::operator<=(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data <= rhs.to_str());
}
PrimObjPtr StrObj::operator==(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data == rhs.to_str());
}
PrimObjPtr StrObj::operator!=(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data != rhs.to_str());
}
PrimObjPtr StrObj::operator&&(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(to_bool() && rhs.to_bool());
}
PrimObjPtr StrObj::operator||(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(to_bool() || rhs.to_bool());
}

PrimObjPtr BoolObj::operator!() const { 
	return make_shared<BoolObj>(!data);
}
PrimObjPtr BoolObj::operator+(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data + rhs.to_bool());
}
PrimObjPtr BoolObj::operator*(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data * rhs.to_bool());
}
PrimObjPtr BoolObj::operator>(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data > rhs.to_bool());
}
PrimObjPtr BoolObj::operator>=(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data >= rhs.to_bool());
}
PrimObjPtr BoolObj::operator<(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data < rhs.to_bool());
}
PrimObjPtr BoolObj::operator<=(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data <= rhs.to_bool());
}
PrimObjPtr BoolObj::operator==(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data == rhs.to_bool());
}
PrimObjPtr BoolObj::operator!=(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data != rhs.to_bool());
}
PrimObjPtr BoolObj::operator&&(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data && rhs.to_bool());
}
PrimObjPtr BoolObj::operator||(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(data || rhs.to_bool());
}

string FuncObj::to_str() const { 
  const string name = dynamic_pointer_cast<StrObj>(decl->name->lit_obj)->data;
  return "<fn " + name + '>';
}
unsigned FuncObj::arity() const { return decl->params.size(); }

PrimObjPtr FuncObj::call(const list<PrimObjPtr> &args) {
  // Every call gets its own environment 
  // This is necessary for recursion to work
  const EnvPtr env = make_shared<Env>(Interpreter::global_env);

  auto param_it = decl->params.cbegin();
  auto arg_it = args.cbegin();
  while (param_it != decl->params.cend() && arg_it != args.cend())
    env->define(*(param_it++), *(arg_it++));

  try { decl->body->exec(env); }
  catch (ReturnExcept return_val) { return return_val.get_val(); }
  return make_shared<DoubleObj>(0);
}
