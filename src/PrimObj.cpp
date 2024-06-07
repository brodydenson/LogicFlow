#include <memory>
#include <iostream>
#include <list>
#include <string>
#include <cmath>
#include <algorithm>
#include "Exception.h"
#include "PrimObj.h"
#include "Stmt.h"
#include "Interpreter.h"
#include "MySet.h"

using std::to_string;
using std::make_shared;
using std::runtime_error;
using std::list;
using std::vector;
using std::dynamic_pointer_cast;
using std::string;

string PrimObj::to_str() const {
	throw runtime_error("Type does not support conversion to string");
}
int PrimObj::to_int() const {
	throw runtime_error("Type does not support conversion to int");
}
double PrimObj::to_double() const {
	throw runtime_error("Type does not support conversion to double");
}
bool PrimObj::to_bool() const {
	throw runtime_error("Type does not support conversion to bool");
}
vector<PrimObjPtr> PrimObj::to_arr(const size_t, const size_t) const {
	throw runtime_error("Type does not support conversion to array");
}
DomainPtr PrimObj::to_set() const {
	throw runtime_error("Type does not support conversion to set");
}
PrimObjPtr PrimObj::bar() const { 
	throw runtime_error("Type does not support grouping '|' operator");
}
PrimObjPtr PrimObj::push(const PrimObjPtr&) const {
	throw runtime_error("Type does not support '++' operator");
}
PrimObjPtr PrimObj::pop(const PrimObjPtr&) const {
	throw runtime_error("Type does not support '--' operator");
}
PrimObjPtr PrimObj::negative() const { 
	throw runtime_error("Type does not support unary '-' operator");
}
PrimObjPtr PrimObj::negate() const { 
	throw runtime_error("Type does not support unary '!' operator");
}
PrimObjPtr PrimObj::add(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '+' operator");
}
PrimObjPtr PrimObj::sub(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '-' operator");
}
PrimObjPtr PrimObj::mul(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '*' operator");
}
PrimObjPtr PrimObj::div(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '/' operator");
}
PrimObjPtr PrimObj::mod(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '%' operator");
}
PrimObjPtr PrimObj::pow(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '^' operator");
}
PrimObjPtr PrimObj::gt(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '>' operator");
}
PrimObjPtr PrimObj::gte(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '>=' operator");
}
PrimObjPtr PrimObj::lt(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '<' operator");
}
PrimObjPtr PrimObj::lte(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '<=' operator");
}
PrimObjPtr PrimObj::eq(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '==' operator");
}
PrimObjPtr PrimObj::neq(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '!=' operator");
}
PrimObjPtr PrimObj::conj(const PrimObjPtr &rhs) const { 
  return make_shared<BoolObj>(to_bool() && rhs->to_bool());
}
PrimObjPtr PrimObj::disj(const PrimObjPtr &rhs) const { 
  return make_shared<BoolObj>(to_bool() || rhs->to_bool());
}
PrimObjPtr PrimObj::at(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support '_' operator");
}
PrimObjPtr PrimObj::in(const PrimObjPtr &rhs) const { 
	throw runtime_error("Type does not support 'in' operator");
}

PrimObjPtr IntObj::bar() const {
	return make_shared<IntObj>(abs(data));
}
PrimObjPtr IntObj::negative() const { 
	return make_shared<IntObj>(-data);
}
PrimObjPtr IntObj::add(const PrimObjPtr &rhs) const { 
  const double res = data + rhs->to_double();
  if (res == static_cast<int>(res))
    return make_shared<IntObj>(res);
  else
    return make_shared<DoubleObj>(res);
}
PrimObjPtr IntObj::sub(const PrimObjPtr &rhs) const { 
  const double res = data - rhs->to_double();
  if (res == static_cast<int>(res))
    return make_shared<IntObj>(res);
  else
    return make_shared<DoubleObj>(res);
}
PrimObjPtr IntObj::mul(const PrimObjPtr &rhs) const { 
  const double res = data * rhs->to_double();
  if (res == static_cast<int>(res))
    return make_shared<IntObj>(res);
  else
    return make_shared<DoubleObj>(res);
}
PrimObjPtr IntObj::div(const PrimObjPtr &rhs) const { 
  if (rhs->to_double() == 0)
    throw runtime_error("Division by zero");
  const double res = data / rhs->to_double();
  if (res == static_cast<int>(res))
    return make_shared<IntObj>(res);
  else
    return make_shared<DoubleObj>(res);
}
PrimObjPtr IntObj::mod(const PrimObjPtr &rhs) const { 
  if (rhs->to_double() == 0)
    throw runtime_error("Division by zero");
  return make_shared<IntObj>(data % rhs->to_int());
}
PrimObjPtr IntObj::pow(const PrimObjPtr &rhs) const { 
  const double res = std::pow(data, rhs->to_double());
  if (res == static_cast<int>(res))
    return make_shared<IntObj>(res);
  else
    return make_shared<DoubleObj>(res);
}
PrimObjPtr IntObj::gt(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data > rhs->to_double());
}
PrimObjPtr IntObj::gte(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data >= rhs->to_double());
}
PrimObjPtr IntObj::lt(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data < rhs->to_double());
}
PrimObjPtr IntObj::lte(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data <= rhs->to_double());
}
PrimObjPtr IntObj::eq(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data == rhs->to_double());
}
PrimObjPtr IntObj::neq(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data != rhs->to_double());
}

PrimObjPtr DoubleObj::bar() const {
	return make_shared<DoubleObj>(abs(data));
}
PrimObjPtr DoubleObj::negative() const { 
	return make_shared<DoubleObj>(-data);
}
PrimObjPtr DoubleObj::add(const PrimObjPtr &rhs) const { 
	return make_shared<DoubleObj>(data + rhs->to_double());
}
PrimObjPtr DoubleObj::sub(const PrimObjPtr &rhs) const { 
	return make_shared<DoubleObj>(data - rhs->to_double());
}
PrimObjPtr DoubleObj::mul(const PrimObjPtr &rhs) const { 
	return make_shared<DoubleObj>(data * rhs->to_double());
}
PrimObjPtr DoubleObj::div(const PrimObjPtr &rhs) const { 
  if (rhs->to_double() == 0)
    throw runtime_error("Division by zero");
	return make_shared<DoubleObj>(data / rhs->to_double());
}
PrimObjPtr DoubleObj::pow(const PrimObjPtr &rhs) const { 
	return make_shared<DoubleObj>(std::pow(data, rhs->to_double()));
}
PrimObjPtr DoubleObj::gt(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data > rhs->to_double());
}
PrimObjPtr DoubleObj::gte(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data >= rhs->to_double());
}
PrimObjPtr DoubleObj::lt(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data < rhs->to_double());
}
PrimObjPtr DoubleObj::lte(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data <= rhs->to_double());
}
PrimObjPtr DoubleObj::eq(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data == rhs->to_double());
}
PrimObjPtr DoubleObj::neq(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data != rhs->to_double());
}

PrimObjPtr StrObj::bar() const {
	return make_shared<IntObj>(data.size());
}
PrimObjPtr StrObj::push(const PrimObjPtr &rhs) const { 
	return make_shared<StrObj>(data + rhs->to_str());
}
PrimObjPtr StrObj::pop(const PrimObjPtr &rhs) const { 
  const size_t index = rhs->to_int();
  if (index < 1 || index > bar()->to_int())
    throw runtime_error("Cannot remove an element out of range");

  string new_str = data;
  new_str.erase(new_str.cbegin() + index - 1);

  return make_shared<StrObj>(new_str);
}
PrimObjPtr StrObj::gt(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data > rhs->to_str());
}
PrimObjPtr StrObj::gte(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data >= rhs->to_str());
}
PrimObjPtr StrObj::lt(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data < rhs->to_str());
}
PrimObjPtr StrObj::lte(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data <= rhs->to_str());
}
PrimObjPtr StrObj::eq(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data == rhs->to_str());
}
PrimObjPtr StrObj::neq(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data != rhs->to_str());
}
PrimObjPtr StrObj::at(const PrimObjPtr &rhs) const { 
  const size_t i = rhs->to_int();
  try {
    return make_shared<StrObj>(string(1, data.at(i-1)));
  } catch (const std::out_of_range &e) {
    throw runtime_error("Index out of range");
  }
}
PrimObjPtr StrObj::in(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data.find(rhs->to_str()) != string::npos);
}

PrimObjPtr BoolObj::negate() const { 
	return make_shared<BoolObj>(!data);
}
PrimObjPtr BoolObj::add(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data + rhs->to_bool());
}
PrimObjPtr BoolObj::mul(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data * rhs->to_bool());
}
PrimObjPtr BoolObj::gt(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data > rhs->to_bool());
}
PrimObjPtr BoolObj::gte(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data >= rhs->to_bool());
}
PrimObjPtr BoolObj::lt(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data < rhs->to_bool());
}
PrimObjPtr BoolObj::lte(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data <= rhs->to_bool());
}
PrimObjPtr BoolObj::eq(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data == rhs->to_bool());
}
PrimObjPtr BoolObj::neq(const PrimObjPtr &rhs) const { 
	return make_shared<BoolObj>(data != rhs->to_bool());
}

PrimObjPtr ArrObj::push(const PrimObjPtr &rhs) const {
  vector<PrimObjPtr> new_arr = data;
  const auto rhs_arr_p = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr_p) {
    const auto rhs_arr = rhs_arr_p->data;
    new_arr.insert(new_arr.cend(), rhs_arr.cbegin(), rhs_arr.cend());
  } else new_arr.push_back(rhs);

  return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::pop(const PrimObjPtr &rhs) const {
  const size_t index = rhs->to_int();
  if (index < 1 || index > bar()->to_int())
    throw runtime_error("Cannot remove an element out of range");

  vector<PrimObjPtr> new_arr = data;
  new_arr.erase(new_arr.cbegin() + index - 1);

  return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::bar() const { 
	return make_shared<IntObj>(data.size());
}

string ArrObj::to_str() const {
  string s = "[";
  for (auto it = data.cbegin(); it != data.cend(); ++it)
    s += it + 1 != data.cend() ? ((*it)->to_str() + ", ") : (*it)->to_str();
  return s + "]";
}
DomainPtr ArrObj::to_set() const { return make_shared<ArrDomain>(data); }

PrimObjPtr ArrObj::negative() const { 
  auto new_arr = data;
  for (auto &i : new_arr)
    i = i->negative();
	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::negate() const { 
  auto new_arr = data;
  for (auto &i : new_arr)
    i = i->negate();
	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::add(const PrimObjPtr &rhs) const { 
  // I dont even know how to comment on this garbage solution
  auto new_arr = data;
  const auto rhs_arr = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = new_arr.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != new_arr.end() && rhs_it != rhs_arr->data.cend()) {
      *lhs_it = (*lhs_it)->add(*rhs_it);
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (auto &i : new_arr)
      i = i->add(rhs);
  }
    
	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::sub(const PrimObjPtr &rhs) const { 
  auto new_arr = data;
  const auto rhs_arr = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = new_arr.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != new_arr.end() && rhs_it != rhs_arr->data.cend()) {
      *lhs_it = (*lhs_it)->sub(*rhs_it);
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (auto &i : new_arr)
      i = i->sub(rhs);
  }

	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::mul(const PrimObjPtr &rhs) const { 
  auto new_arr = data;
  const auto rhs_arr = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = new_arr.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != new_arr.end() && rhs_it != rhs_arr->data.cend()) {
      *lhs_it = (*lhs_it)->mul(*rhs_it);
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (auto &i : new_arr)
      i = i->mul(rhs);
  }

	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::div(const PrimObjPtr &rhs) const { 
  auto new_arr = data;
  const auto rhs_arr = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = new_arr.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != new_arr.end() && rhs_it != rhs_arr->data.cend()) {
      *lhs_it = (*lhs_it)->add(*rhs_it);
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (auto &i : new_arr)
      i = i->div(rhs);
  }

	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::mod(const PrimObjPtr &rhs) const { 
  auto new_arr = data;
  const auto rhs_arr = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = new_arr.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != new_arr.end() && rhs_it != rhs_arr->data.cend()) {
      *lhs_it = (*lhs_it)->add(*rhs_it);
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (auto &i : new_arr)
      i = i->mod(rhs);
  }

	return make_shared<ArrObj>(new_arr);
}
PrimObjPtr ArrObj::gt(const PrimObjPtr &rhs) const { 
  const auto rhs_arr = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = (*lhs_it)->gt(*rhs_it);
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = i->gt(rhs);
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::gte(const PrimObjPtr &rhs) const { 
  const auto rhs_arr = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = (*lhs_it)->gte(*rhs_it);
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = i->gte(rhs);
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::lt(const PrimObjPtr &rhs) const { 
  const auto rhs_arr = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = (*lhs_it)->lt(*rhs_it);
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = i->lt(rhs);
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::lte(const PrimObjPtr &rhs) const { 
  const auto rhs_arr = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = (*lhs_it)->lte(*rhs_it);
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = i->lte(rhs);
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::eq(const PrimObjPtr &rhs) const { 
  const auto rhs_arr = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = (*lhs_it)->eq(*rhs_it);
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = i->eq(rhs);
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::neq(const PrimObjPtr &rhs) const {
  const auto rhs_arr = dynamic_pointer_cast<ArrObj>(rhs);
  if (rhs_arr != nullptr) {
    auto lhs_it = data.begin();
    auto rhs_it = rhs_arr->data.cbegin();
    while (lhs_it != data.end() && rhs_it != rhs_arr->data.cend()) {
      const auto cmp = (*lhs_it)->neq(*rhs_it);
      if (!cmp->to_bool()) return cmp;
      ++lhs_it; ++rhs_it;
    }
  } else {
    for (const auto &i : data) {
      const auto cmp = i->neq(rhs);
      if (!cmp->to_bool()) return cmp;
    }
  }

	return make_shared<BoolObj>(true);
}
PrimObjPtr ArrObj::at(const PrimObjPtr &rhs) const {
  const size_t i = rhs->to_int();
  try {
    return data.at(i-1);
  } catch (const std::out_of_range &e) {
    throw runtime_error("Index out of range");
  }
}
PrimObjPtr ArrObj::in(const PrimObjPtr &rhs) const {
  const auto it = std::find_if(data.cbegin(), data.cend(), 
                               [rhs](const PrimObjPtr &obj) { return obj->eq(rhs); });
  return make_shared<BoolObj>(it != data.cend());
}

PrimObjPtr ToInt::call(const list<PrimObjPtr> &args) const {
  return make_shared<IntObj>((*args.cbegin())->to_int());
}
PrimObjPtr ToDouble::call(const list<PrimObjPtr> &args) const {
  return make_shared<DoubleObj>((*args.cbegin())->to_double());
}
PrimObjPtr ToStr::call(const list<PrimObjPtr> &args) const {
  return make_shared<StrObj>((*args.cbegin())->to_str());
}
PrimObjPtr ToBool::call(const list<PrimObjPtr> &args) const {
  return make_shared<BoolObj>((*args.cbegin())->to_bool());
}
PrimObjPtr ToArr::call(const list<PrimObjPtr> &args) const {
  return make_shared<ArrObj>((*args.cbegin())->to_arr(DEF_COMP));
}
PrimObjPtr ToArr2::call(const list<PrimObjPtr> &args) const {
  auto it = args.cbegin();
  const auto obj = *it++;
  const size_t max_size = (*it++)->to_int();
  return make_shared<ArrObj>(obj->to_arr(max_size));
}
PrimObjPtr ToArr3::call(const list<PrimObjPtr> &args) const {
  auto it = args.cbegin();
  const auto obj = *it++;
  const size_t max_size = (*it++)->to_int();
  const size_t max_comp = (*it++)->to_int();
  return make_shared<ArrObj>(obj->to_arr(max_size, max_comp));
}
PrimObjPtr ToSet::call(const list<PrimObjPtr> &args) const {
  return make_shared<SetObj>((*args.cbegin())->to_set());
}

string FuncObj::to_str() const { 
  const string name = dynamic_pointer_cast<StrObj>(decl->name->lit_obj)->data;
  return "<fn " + name + '>';
}
unsigned FuncObj::arity() const { return decl->params.size(); }

PrimObjPtr FuncObj::call(const list<PrimObjPtr> &args) const {
  // Every call gets its own environment 
  // This is necessary for recursion to work as well with local functions
  const EnvPtr env = make_shared<Env>(closure);

  auto param_it = decl->params.cbegin();
  auto arg_it = args.cbegin();
  while (param_it != decl->params.cend() && arg_it != args.cend())
    env->define(*(param_it++), *(arg_it++));

  try { decl->body->exec(env); }
  catch (ReturnExcept return_val) { return return_val.get_val(); }
  return make_shared<IntObj>(0);
}

string SetObj::to_str() const {
  constexpr size_t text_limit = 10;
  const auto finite_set = data->to_finite(text_limit + 1);
  string s = "{ ";

  size_t added = 0;
  for (auto it = finite_set.cbegin(); it != finite_set.cend(); ++it, ++added) {
    s += (*it)->to_str();

    if (added+1 < text_limit && it != prev(finite_set.cend()))
      s += ", ";
    else if (finite_set.size() > text_limit) {
      s += ", ...";
      break;
    }
  }
  return s + " }";
}

bool SetObj::to_bool() const { return data->to_finite(1).size() != 0; }
vector<PrimObjPtr> SetObj::to_arr(const size_t max_size, const size_t max_comp) const {
  const auto s = data->to_finite(max_size, max_comp);
  return vector<PrimObjPtr>(s.cbegin(), s.cend());
}
DomainPtr SetObj::to_set() const { return data; }

PrimObjPtr SetObj::bar() const {
	return make_shared<IntObj>(data->to_finite().size());
}

PrimObjPtr SetObj::add(const PrimObjPtr &rhs) const { 
  const auto set_op = make_shared<SetUnion>(data, rhs->to_set());
  return make_shared<SetObj>(set_op);
}
PrimObjPtr SetObj::mul(const PrimObjPtr &rhs) const { 
  const auto set_op = make_shared<SetInter>(data, rhs->to_set());
  return make_shared<SetObj>(set_op);
}
PrimObjPtr SetObj::sub(const PrimObjPtr &rhs) const { 
  const auto set_op = make_shared<SetDiff>(data, rhs->to_set());
  return make_shared<SetObj>(set_op);
}
PrimObjPtr SetObj::in(const PrimObjPtr &rhs) const { 
  const auto s = data->to_finite(DEF_SIZE, DEF_COMP);
  return make_shared<BoolObj>(s.find(rhs) != s.cend());
}
// PrimObjPtr SetObj::pow(const PrimObjPtr &rhs) const { 
//   const unsigned exp = rhs->to_int();
//   if (exp < 0) throw runtime_error("Set must be raised to a positive power");
//   const auto set_op = make_shared<SetPow>(data, exp);
//   return make_shared<SetObj>(set_op);
// }
