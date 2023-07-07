#ifndef SET_H
#define SET_H

#include <memory>
#include <vector>
#include "PrimObj.h"

struct PrimObj;
typedef std::shared_ptr<PrimObj> PrimObjPtr;

enum SetOpType {
  UNION, INTERSECTION, DIFFERENCE, COMPLEMENT, NONE
};

struct Domain;
typedef std::shared_ptr<Domain> DomainPtr;

struct Domain {
  virtual ~Domain() = default;
  virtual std::vector<PrimObjPtr> to_vec() const = 0;
};

struct DirectDomain : public Domain {
  DirectDomain(const std::vector<PrimObjPtr> &_domain)
    : domain(_domain), op_type(SetOpType::NONE), operand(nullptr) { }
  DirectDomain(const std::vector<PrimObjPtr> &_domain, SetOpType _op_type,
               const DomainPtr &_operand)
    : domain(_domain), op_type(_op_type), operand(_operand) { }
  std::vector<PrimObjPtr> to_vec() const;
  const std::vector<PrimObjPtr> domain;
  const SetOpType op_type;
  const DomainPtr operand;
};

struct MySet : public Domain {
  MySet(const DomainPtr &_domain, const std::shared_ptr<FuncObj> &_func)
    : domain(_domain), func(_func), op_type(SetOpType::NONE), operand(nullptr) { }
  MySet(const DomainPtr &_domain, const std::shared_ptr<FuncObj> &_func,
      SetOpType _op_type, const DomainPtr &_operand)
    : domain(_domain), func(_func), op_type(_op_type), operand(_operand) { }
  std::vector<PrimObjPtr> to_vec() const;
  std::vector<PrimObjPtr>::size_type size() const
    { return domain->to_vec().size(); }

  const DomainPtr domain;
  const std::shared_ptr<FuncObj> func;
  const SetOpType op_type;
  const DomainPtr operand;
};


typedef std::shared_ptr<MySet> SetPtr;

#endif
