#ifndef MY_SET_H
#define MY_SET_H

#include <memory>
#include <vector>
#include <set>
#include "PrimObj.h"

constexpr size_t DEF_COMP = 65536;

struct PrimObj;
typedef std::shared_ptr<PrimObj> PrimObjPtr;

struct CompSetPtr {
  bool operator()(const PrimObjPtr &lhs, const PrimObjPtr &rhs) const {
    // Order matters
    try { return lhs->to_double() < rhs->to_double(); } catch (std::runtime_error) {}
    try { return lhs->to_str() < rhs->to_str(); } catch (std::runtime_error) {}
    try { return lhs->to_bool() < rhs->to_bool(); } catch (std::runtime_error) {}
    return false;
  }
};

typedef std::set<PrimObjPtr, CompSetPtr> SetContainer;

enum SetOpType {
  UNION, INTERSECTION, DIFFERENCE, NONE
};

struct Domain;
typedef std::shared_ptr<Domain> DomainPtr;

struct Domain {
  virtual ~Domain() = default;
  virtual SetContainer to_finite(const size_t max_size=DEF_COMP) const = 0;
};

struct PosZDomain : public Domain {
  PosZDomain() = default;
  SetContainer to_finite(const size_t max_size=DEF_COMP) const;
};
struct NegZDomain : public Domain {
  NegZDomain() = default;
  SetContainer to_finite(const size_t max_size=DEF_COMP) const;
};
struct ZDomain : public Domain {
  ZDomain() = default;
  SetContainer to_finite(const size_t max_size=DEF_COMP) const;
};

struct ArrDomain : public Domain {
  ArrDomain(const std::vector<PrimObjPtr> &_domain)
    : domain(_domain) { }
  const std::vector<PrimObjPtr> domain;
  SetContainer to_finite(const size_t max_size=DEF_COMP) const;
};

struct MySet : public Domain {
  MySet(const DomainPtr &_domain, const std::shared_ptr<FuncObj> &_func, 
        const std::shared_ptr<FuncObj> &_cond_func)
    : domain(_domain), func(_func), cond_func(_cond_func) { }
  MySet(const DomainPtr &_domain, const std::shared_ptr<FuncObj> &_func)
    : domain(_domain), func(_func) { }

  SetContainer to_finite(const size_t max_size=DEF_COMP) const;

  const DomainPtr domain;
  const std::shared_ptr<FuncObj> func;
  const std::shared_ptr<FuncObj> cond_func;
};

struct SetOp : public Domain {
  SetOp(const DomainPtr &_lhs, const DomainPtr &_rhs, const SetOpType _op_type)
    : lhs(_lhs), rhs(_rhs), op_type(_op_type) { }

  SetContainer finite_union(const size_t) const;
  SetContainer finite_intersection(const size_t) const;
  SetContainer finite_difference(const size_t) const;
  SetContainer to_finite(const size_t max_size=DEF_COMP) const;

  const DomainPtr lhs;
  const DomainPtr rhs;
  const SetOpType op_type;
};


typedef std::shared_ptr<MySet> SetPtr;

#endif
