#include <memory>
#include <iostream>
#include <list>
#include <string>
#include "include/Exception.h"
#include "include/PrimObj.h"
#include "include/Stmt.h"
#include "include/Interpreter.h"
#include "include/MySet.h"

using std::make_shared;
using std::runtime_error;
using std::list;
using std::vector;
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

string ArrObj::to_str() const {
  string s = "[";
  for (auto it = data.cbegin(); it != data.cend(); ++it)
    s += it + 1 != data.cend() ? ((*it)->to_str() + ", ") : ((*it)->to_str() + "]");
  return s;
}
DomainPtr ArrObj::to_set() const { return make_shared<DirectDomain>(data); }

PrimObjPtr ArrObj::operator-() const { 
  auto new_arr = data;
  for (auto &i : new_arr)
    i = -*i;
	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::operator!() const { 
  auto new_arr = data;
  for (auto &i : new_arr)
    i = !*i;
	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::operator+(const PrimObj &rhs) const { 
  // I dont even know how to comment on this garbage solution
  auto new_arr = data;
  const auto rhs_arr = dynamic_cast<const ArrObj*>(&rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = new_arr.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != new_arr.end() && rhs_it != rhs_arr->data.cend()) {
      *lhs_it = **lhs_it + **rhs_it;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (auto &i : new_arr)
      i = *i + rhs;
  }
    
	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::operator-(const PrimObj &rhs) const { 
  auto new_arr = data;
  const auto rhs_arr = dynamic_cast<const ArrObj*>(&rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = new_arr.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != new_arr.end() && rhs_it != rhs_arr->data.cend()) {
      *lhs_it = **lhs_it - **rhs_it;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (auto &i : new_arr)
      i = *i - rhs;
  }

	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::operator*(const PrimObj &rhs) const { 
  auto new_arr = data;
  const auto rhs_arr = dynamic_cast<const ArrObj*>(&rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = new_arr.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != new_arr.end() && rhs_it != rhs_arr->data.cend()) {
      *lhs_it = **lhs_it * **rhs_it;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (auto &i : new_arr)
      i = *i * rhs;
  }

	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::operator/(const PrimObj &rhs) const { 
  auto new_arr = data;
  const auto rhs_arr = dynamic_cast<const ArrObj*>(&rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = new_arr.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != new_arr.end() && rhs_it != rhs_arr->data.cend()) {
      *lhs_it = **lhs_it / **rhs_it;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (auto &i : new_arr)
      i = *i / rhs;
  }

	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::operator>(const PrimObj &rhs) const { 
  const auto rhs_arr = dynamic_cast<const ArrObj*>(&rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = **lhs_it > **rhs_it;
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = *i > rhs;
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::operator>=(const PrimObj &rhs) const { 
  const auto rhs_arr = dynamic_cast<const ArrObj*>(&rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = **lhs_it >= **rhs_it;
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = *i >= rhs;
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::operator<(const PrimObj &rhs) const { 
  const auto rhs_arr = dynamic_cast<const ArrObj*>(&rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = **lhs_it < **rhs_it;
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = *i < rhs;
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::operator<=(const PrimObj &rhs) const { 
  const auto rhs_arr = dynamic_cast<const ArrObj*>(&rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = **lhs_it <= **rhs_it;
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = *i <= rhs;
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::operator==(const PrimObj &rhs) const { 
  const auto rhs_arr = dynamic_cast<const ArrObj*>(&rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = **lhs_it == **rhs_it;
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = *i == rhs;
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::operator!=(const PrimObj &rhs) const {
  const auto rhs_arr = dynamic_cast<const ArrObj*>(&rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = **lhs_it != **rhs_it;
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = *i != rhs;
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::operator&&(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(to_bool());
}
PrimObjPtr ArrObj::operator||(const PrimObj &rhs) const { 
	return make_shared<BoolObj>(to_bool());
}

string FuncObj::to_str() const { 
  const string name = dynamic_pointer_cast<StrObj>(decl->name->lit_obj)->data;
  return "<fn " + name + '>';
}
unsigned FuncObj::arity() const { return decl->params.size(); }

PrimObjPtr FuncObj::call(const list<PrimObjPtr> &args) const {
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

string SetObj::to_str() const {
  constexpr unsigned limit = 5;
  string s = "{";
  const auto vec = data->to_vec();

  for (size_t i = 0; i < vec.size(); ++i) {
    s += vec[i]->to_str();

    if (i+1 < limit && i != vec.size() - 1)
      s += ", ";
    else if (i+1 >= limit) {
      s += ", ...";
      break;
    }
  }
  return s + "}";
}

bool SetObj::to_bool() const { return data->size() > 0; }
vector<PrimObjPtr> SetObj::to_arr() const { return data->to_vec(); }
DomainPtr SetObj::to_set() const { return data; }

PrimObjPtr SetObj::operator+(const PrimObj &rhs) const { 
  const auto new_set = make_shared<MySet>(data->domain, data->func, UNION, rhs.to_set());
  return make_shared<SetObj>(new_set);
}
