#include <list>
#include <vector>
#include <iostream>
#include "include/MySet.h"

using std::list;
using std::vector;
using std::min;
using std::max;
using std::make_shared;
using std::set;

SetContainer ZDomain::to_finite(const size_t max_size) const {
  SetContainer s;
  for (long i = start; s.size() < max_size && i < end; ++i) 
    s.insert(make_shared<IntObj>(i));
  return s;
}

SetContainer ArrDomain::to_finite(const size_t max_size) const {
  return SetContainer(domain.cbegin(), min(domain.cbegin() + max_size, domain.cend()));
}

SetContainer MySet::to_finite(const size_t max_size) const {
  SetContainer s;
  size_t computed = 0;
  const auto finite_domain = domain->to_finite(max_size);
  for (auto d_it = finite_domain.cbegin(); d_it != finite_domain.cend() && computed < max_size; ++d_it) {
    if (!cond_func || cond_func->call(list<PrimObjPtr>{*d_it})->to_bool()) {
      s.insert(func->call(list<PrimObjPtr>{*d_it}));
    }
    ++computed;
  }
  return s;
}

SetContainer SetOp::finite_union(const size_t max_size) const {
  SetContainer s;
  size_t computed = 0;
  const auto finite_lhs = lhs->to_finite(max_size);
  const auto finite_rhs = rhs->to_finite(max_size);
  auto lhs_it = finite_lhs.cbegin();
  auto rhs_it = finite_rhs.cbegin();
  while ((lhs_it != finite_lhs.cend() || rhs_it != finite_rhs.cend()) && computed < max_size) {
    if (lhs_it != finite_lhs.cend()) {
      s.insert(*lhs_it++);
      ++computed;
    }
    if (rhs_it != finite_rhs.cend()) {
      s.insert(*rhs_it++);
      ++computed;
    }
  }
  return s;
}

SetContainer SetOp::finite_intersection(const size_t max_size) const {
  SetContainer s;
  size_t computed = 0;
  const auto finite_lhs = lhs->to_finite(max_size);
  const auto finite_rhs = rhs->to_finite(max_size);

  for (auto lhs_it = finite_lhs.cbegin(); lhs_it != finite_lhs.cend() && computed < max_size; ++lhs_it) {
    if (finite_rhs.find(*lhs_it) != finite_rhs.cend()) 
      s.insert(*lhs_it);
    ++computed;
  }

  return s;
}

SetContainer SetOp::finite_difference(const size_t max_size) const {
  SetContainer s;
  size_t computed = 0;
  const auto finite_lhs = lhs->to_finite(max_size);
  const auto finite_rhs = rhs->to_finite(max_size);

  for (auto lhs_it = finite_lhs.cbegin(); lhs_it != finite_lhs.cend() && computed < max_size; ++lhs_it) {
    if (finite_rhs.find(*lhs_it) == finite_rhs.cend()) 
      s.insert(*lhs_it);
    ++computed;
  }

  return s;
}

SetContainer SetOp::to_finite(const size_t max_size) const {
  if (op_type == SetOpType::UNION)
    return finite_union(max_size);
  if (op_type == SetOpType::INTERSECTION)
    return finite_intersection(max_size);
  if (op_type == SetOpType::DIFFERENCE)
    return finite_difference(max_size);
  throw std::logic_error("No matching set operation");
}


