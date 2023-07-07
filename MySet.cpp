#include <list>
#include <vector>
#include <iostream>
#include "include/MySet.h"

using std::list;
using std::vector;

vector<PrimObjPtr> DirectDomain::to_vec() const {
  if (op_type == SetOpType::NONE)
    return domain;
  
  auto vec = domain;

  const auto operand_vec = operand->to_vec();
  if (op_type == SetOpType::UNION)
    vec.insert(vec.cend(), operand_vec.cbegin(), operand_vec.cend());
  return vec;
}

vector<PrimObjPtr> MySet::to_vec() const {
  vector<PrimObjPtr> vec;
  for (const auto &i : domain->to_vec())
    vec.push_back(func->call(list<PrimObjPtr>({ i })));

  if (op_type == SetOpType::NONE)
    return vec;

  const auto operand_vec = operand->to_vec();
  if (op_type == SetOpType::UNION)
    vec.insert(vec.cend(), operand_vec.cbegin(), operand_vec.cend());
  return vec;
}
