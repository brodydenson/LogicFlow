#ifndef PRIM_OBJ_H
#define PRIM_OBJ_H

#include <string>
#include <list>
#include <memory>
#include <vector>

// Also used in MySet
constexpr size_t DEF_SIZE = 0x1000;
constexpr size_t DEF_COMP = 0x10000;

class Tok;

struct MySet;
struct Domain;
typedef std::shared_ptr<MySet> SetPtr;
typedef std::shared_ptr<Domain> DomainPtr;

struct PrimObj;
typedef std::shared_ptr<PrimObj> PrimObjPtr;

struct PrimObj {
	friend std::ostream &operator<<(std::ostream &os, const PrimObj &obj) 
		{ os << obj.to_str(); return os; }
	virtual ~PrimObj() = default;
	virtual std::string to_str() const;
  virtual int to_int() const;
  virtual double to_double() const;
	virtual bool to_bool() const;
  virtual std::vector<PrimObjPtr> to_arr(const size_t max_size=DEF_SIZE, 
                                         const size_t max_comp=DEF_COMP) const;
  virtual DomainPtr to_set() const;

  virtual PrimObjPtr bar() const;
	virtual PrimObjPtr negative() const;
	virtual PrimObjPtr negate() const;
  virtual PrimObjPtr push(const PrimObjPtr&) const;
  virtual PrimObjPtr pop(const PrimObjPtr&) const;
	virtual PrimObjPtr add(const PrimObjPtr&) const;
	virtual PrimObjPtr sub(const PrimObjPtr&) const;
	virtual PrimObjPtr mul(const PrimObjPtr&) const;
	virtual PrimObjPtr div(const PrimObjPtr&) const;
	virtual PrimObjPtr pow(const PrimObjPtr&) const;
	virtual PrimObjPtr gt(const PrimObjPtr&) const;
	virtual PrimObjPtr gte(const PrimObjPtr&) const;
	virtual PrimObjPtr lt(const PrimObjPtr&) const;
	virtual PrimObjPtr lte(const PrimObjPtr&) const;
	virtual PrimObjPtr eq(const PrimObjPtr&) const;
	virtual PrimObjPtr neq(const PrimObjPtr&) const;
	virtual PrimObjPtr conj(const PrimObjPtr&) const;
	virtual PrimObjPtr disj(const PrimObjPtr&) const;
	virtual PrimObjPtr at(const PrimObjPtr&) const;
	virtual PrimObjPtr in(const PrimObjPtr&) const;
};

struct IntObj : public PrimObj {
	IntObj(int _data) : data(_data) { } // nonexplicit
	std::string to_str() const { return std::to_string(data); }
  int to_int() const { return data; }
  double to_double() const { return data; }
	bool to_bool() const { return data != 0; }

	PrimObjPtr bar() const;
	PrimObjPtr negative() const;
	PrimObjPtr add(const PrimObjPtr&) const;
	PrimObjPtr sub(const PrimObjPtr&) const;
	PrimObjPtr mul(const PrimObjPtr&) const;
	PrimObjPtr div(const PrimObjPtr&) const;
	PrimObjPtr pow(const PrimObjPtr&) const;
	PrimObjPtr gt(const PrimObjPtr&) const;
	PrimObjPtr gte(const PrimObjPtr&) const;
	PrimObjPtr lt(const PrimObjPtr&) const;
	PrimObjPtr lte(const PrimObjPtr&) const;
	PrimObjPtr eq(const PrimObjPtr&) const;
	PrimObjPtr neq(const PrimObjPtr&) const;

	const int data;
};

struct DoubleObj : public PrimObj {
	DoubleObj(double _data) : data(_data) { } // nonexplicit
	std::string to_str() const { return std::to_string(data); }
  int to_int() const { return data; }
  double to_double() const { return data; }
	bool to_bool() const { return data != 0; }

	PrimObjPtr bar() const;
	PrimObjPtr negative() const;
	PrimObjPtr add(const PrimObjPtr&) const;
	PrimObjPtr sub(const PrimObjPtr&) const;
	PrimObjPtr mul(const PrimObjPtr&) const;
	PrimObjPtr div(const PrimObjPtr&) const;
	PrimObjPtr pow(const PrimObjPtr&) const;
	PrimObjPtr gt(const PrimObjPtr&) const;
	PrimObjPtr gte(const PrimObjPtr&) const;
	PrimObjPtr lt(const PrimObjPtr&) const;
	PrimObjPtr lte(const PrimObjPtr&) const;
	PrimObjPtr eq(const PrimObjPtr&) const;
	PrimObjPtr neq(const PrimObjPtr&) const;

	const double data;
};

struct StrObj : public PrimObj {
	StrObj(const std::string &_data) : data(_data) { } // nonexplicit
	std::string to_str() const { return data; }
	bool to_bool() const { return data.length() != 0; }

	PrimObjPtr bar() const;
	PrimObjPtr push(const PrimObjPtr&) const;
	PrimObjPtr pop(const PrimObjPtr&) const;
	PrimObjPtr gt(const PrimObjPtr&) const;
	PrimObjPtr gte(const PrimObjPtr&) const;
	PrimObjPtr lt(const PrimObjPtr&) const;
	PrimObjPtr lte(const PrimObjPtr&) const;
	PrimObjPtr eq(const PrimObjPtr&) const;
	PrimObjPtr neq(const PrimObjPtr&) const;
	PrimObjPtr at(const PrimObjPtr&) const;
	PrimObjPtr in(const PrimObjPtr&) const;

	const std::string data;
};

struct BoolObj : public PrimObj {
	BoolObj(bool _data) : data(_data) { } // nonexplicit
	std::string to_str() const { return data ? "true" : "false"; }
	bool to_bool() const { return data; }

	PrimObjPtr negate() const;
	PrimObjPtr add(const PrimObjPtr&) const;
	PrimObjPtr mul(const PrimObjPtr&) const;
	PrimObjPtr gt(const PrimObjPtr&) const;
	PrimObjPtr gte(const PrimObjPtr&) const;
	PrimObjPtr lt(const PrimObjPtr&) const;
	PrimObjPtr lte(const PrimObjPtr&) const;
	PrimObjPtr eq(const PrimObjPtr&) const;
	PrimObjPtr neq(const PrimObjPtr&) const;

	const bool data;
};

struct ArrObj : public PrimObj {
	ArrObj(const std::vector<PrimObjPtr> &_data) : data(_data) { } // nonexplicit
	std::string to_str() const;
	bool to_bool() const { return data.size() > 0; }
  std::vector<PrimObjPtr> to_arr(const size_t, const size_t) const { return data; }
  DomainPtr to_set() const;

  PrimObjPtr bar() const;
	PrimObjPtr negative() const;
	PrimObjPtr negate() const;
  PrimObjPtr push(const PrimObjPtr&) const;
  PrimObjPtr pop(const PrimObjPtr&) const;
	PrimObjPtr add(const PrimObjPtr&) const;
	PrimObjPtr sub(const PrimObjPtr&) const;
	PrimObjPtr mul(const PrimObjPtr&) const;
	PrimObjPtr div(const PrimObjPtr&) const;
	PrimObjPtr gt(const PrimObjPtr&) const;
	PrimObjPtr gte(const PrimObjPtr&) const;
	PrimObjPtr lt(const PrimObjPtr&) const;
	PrimObjPtr lte(const PrimObjPtr&) const;
	PrimObjPtr eq(const PrimObjPtr&) const;
	PrimObjPtr neq(const PrimObjPtr&) const;
	PrimObjPtr at(const PrimObjPtr&) const;
	PrimObjPtr in(const PrimObjPtr&) const;

	const std::vector<PrimObjPtr> data;
};


struct CallableObj : public PrimObj {
	virtual ~CallableObj() = default;

	virtual std::string to_str() const { return "<callable>"; }
	virtual unsigned arity() const = 0;

	virtual PrimObjPtr call(const std::list<PrimObjPtr> &args) const = 0;
};

struct ToInt : public CallableObj {
	ToInt() = default;
  PrimObjPtr call(const std::list<PrimObjPtr> &args) const;
	unsigned arity() const { return 1; }
};
struct ToDouble : public CallableObj {
	ToDouble() = default;
  PrimObjPtr call(const std::list<PrimObjPtr> &args) const;
	unsigned arity() const { return 1; }
};
struct ToStr : public CallableObj {
	ToStr() = default;
  PrimObjPtr call(const std::list<PrimObjPtr> &args) const;
	unsigned arity() const { return 1; }
};
struct ToBool : public CallableObj {
	ToBool() = default;
  PrimObjPtr call(const std::list<PrimObjPtr> &args) const;
	unsigned arity() const { return 1; }
};
struct ToArr : public CallableObj {
	ToArr() = default;
  PrimObjPtr call(const std::list<PrimObjPtr> &args) const;
	unsigned arity() const { return 1; }
};
struct ToArr2 : public CallableObj {
	ToArr2() = default;
  PrimObjPtr call(const std::list<PrimObjPtr> &args) const;
	unsigned arity() const { return 2; }
};
struct ToArr3 : public CallableObj {
	ToArr3() = default;
  PrimObjPtr call(const std::list<PrimObjPtr> &args) const;
	unsigned arity() const { return 3; }
};
struct ToSet : public CallableObj {
	ToSet() = default;
  PrimObjPtr call(const std::list<PrimObjPtr> &args) const;
	unsigned arity() const { return 1; }
};

// Uses FuncStmt
// might change this since this isn't really my style
class FuncStmt;
class Env;
struct FuncObj : public CallableObj {
  const std::shared_ptr<FuncStmt> decl;
  const std::shared_ptr<Env> closure;

  FuncObj(const std::shared_ptr<FuncStmt> &_decl, 
          const std::shared_ptr<Env> &_closure) 
  : decl(_decl), closure(_closure) { } 
  std::string to_str() const;
  unsigned arity() const;

  PrimObjPtr call(const std::list<PrimObjPtr> &args) const;
};


struct SetObj : public PrimObj {
	SetObj(const DomainPtr &_data) : data(_data) { } // nonexplicit
	std::string to_str() const;
	bool to_bool() const;
  std::vector<PrimObjPtr> to_arr(const size_t, const size_t) const;
  DomainPtr to_set() const;

	PrimObjPtr bar() const;
	PrimObjPtr add(const PrimObjPtr&) const;
	PrimObjPtr sub(const PrimObjPtr&) const;
	PrimObjPtr mul(const PrimObjPtr&) const;
	PrimObjPtr in(const PrimObjPtr&) const;
	// PrimObjPtr pow(const PrimObjPtr&) const;

	const DomainPtr data;
};

#endif
