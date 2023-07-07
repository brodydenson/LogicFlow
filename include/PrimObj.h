#ifndef PRIM_OBJ_H
#define PRIM_OBJ_H

#include <string>
#include <list>
#include <memory>
#include <vector>

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
	virtual std::string to_str() const = 0;
  virtual double to_double() const = 0;
	virtual bool to_bool() const = 0;
  virtual std::vector<PrimObjPtr> to_arr() const = 0;
  virtual DomainPtr to_set() const = 0;
	virtual PrimObjPtr operator-() const;
	virtual PrimObjPtr operator!() const;
	virtual PrimObjPtr operator+(const PrimObj&) const;
	virtual PrimObjPtr operator-(const PrimObj&) const;
	virtual PrimObjPtr operator*(const PrimObj&) const;
	virtual PrimObjPtr operator/(const PrimObj&) const;
	virtual PrimObjPtr operator>(const PrimObj&) const;
	virtual PrimObjPtr operator>=(const PrimObj&) const;
	virtual PrimObjPtr operator<(const PrimObj&) const;
	virtual PrimObjPtr operator<=(const PrimObj&) const;
	virtual PrimObjPtr operator==(const PrimObj&) const;
	virtual PrimObjPtr operator!=(const PrimObj&) const;
	virtual PrimObjPtr operator&&(const PrimObj&) const;
	virtual PrimObjPtr operator||(const PrimObj&) const;
};

struct DoubleObj : public PrimObj {
	DoubleObj(double _data) : data(_data) { } // nonexplicit
	std::string to_str() const { return std::to_string(data); }
  double to_double() const { return data; }
	bool to_bool() const { return data != 0; }
  std::vector<PrimObjPtr> to_arr() const
    { throw std::runtime_error("No type conversion from double to array"); }
  DomainPtr to_set() const
    { throw std::runtime_error("No type conversion from double to set"); }
	PrimObjPtr operator-() const;
	PrimObjPtr operator!() const;
	PrimObjPtr operator+(const PrimObj&) const;
	PrimObjPtr operator-(const PrimObj&) const;
	PrimObjPtr operator*(const PrimObj&) const;
	PrimObjPtr operator/(const PrimObj&) const;
	PrimObjPtr operator>(const PrimObj&) const;
	PrimObjPtr operator>=(const PrimObj&) const;
	PrimObjPtr operator<(const PrimObj&) const;
	PrimObjPtr operator<=(const PrimObj&) const;
	PrimObjPtr operator==(const PrimObj&) const;
	PrimObjPtr operator!=(const PrimObj&) const;
	PrimObjPtr operator&&(const PrimObj&) const;
	PrimObjPtr operator||(const PrimObj&) const;

	const double data;
};

struct StrObj : public PrimObj {
	StrObj(const std::string &_data) : data(_data) { } // nonexplicit
	std::string to_str() const { return data; }
  double to_double() const
    { throw std::runtime_error("No type conversion from string to double"); }
	bool to_bool() const { return data.length() != 0; }
  std::vector<PrimObjPtr> to_arr() const
    { throw std::runtime_error("No type conversion from string to array"); }
  DomainPtr to_set() const
    { throw std::runtime_error("No type conversion from string to set"); }
	PrimObjPtr operator+(const PrimObj&) const;
	PrimObjPtr operator>(const PrimObj&) const;
	PrimObjPtr operator>=(const PrimObj&) const;
	PrimObjPtr operator<(const PrimObj&) const;
	PrimObjPtr operator<=(const PrimObj&) const;
	PrimObjPtr operator==(const PrimObj&) const;
	PrimObjPtr operator!=(const PrimObj&) const;
	PrimObjPtr operator&&(const PrimObj&) const;
	PrimObjPtr operator||(const PrimObj&) const;

	const std::string data;
};

struct BoolObj : public PrimObj {
	BoolObj(bool _data) : data(_data) { } // nonexplicit
	std::string to_str() const { return data ? "true" : "false"; }
  double to_double() const
    { throw std::runtime_error("No type conversion from bool to double"); }
	bool to_bool() const { return data; }
  std::vector<PrimObjPtr> to_arr() const
    { throw std::runtime_error("No type conversion from bool to array"); }
  DomainPtr to_set() const
    { throw std::runtime_error("No type conversion from bool to set"); }
	PrimObjPtr operator!() const;
	PrimObjPtr operator+(const PrimObj&) const;
	PrimObjPtr operator*(const PrimObj&) const;
	PrimObjPtr operator>(const PrimObj&) const;
	PrimObjPtr operator>=(const PrimObj&) const;
	PrimObjPtr operator<(const PrimObj&) const;
	PrimObjPtr operator<=(const PrimObj&) const;
	PrimObjPtr operator==(const PrimObj&) const;
	PrimObjPtr operator!=(const PrimObj&) const;
	PrimObjPtr operator&&(const PrimObj&) const;
	PrimObjPtr operator||(const PrimObj&) const;

	const bool data;
};

struct ArrObj : public PrimObj {
	ArrObj(const std::vector<PrimObjPtr> &_data) : data(_data) { } // nonexplicit
	std::string to_str() const;
  double to_double() const
    { throw std::runtime_error("No type conversion from array to double"); }
	bool to_bool() const { return data.size() > 0; }
  std::vector<PrimObjPtr> to_arr() const { return data; }
  DomainPtr to_set() const;
	PrimObjPtr operator-() const;
	PrimObjPtr operator!() const;
	PrimObjPtr operator+(const PrimObj&) const;
	PrimObjPtr operator-(const PrimObj&) const;
	PrimObjPtr operator*(const PrimObj&) const;
	PrimObjPtr operator/(const PrimObj&) const;
	PrimObjPtr operator>(const PrimObj&) const;
	PrimObjPtr operator>=(const PrimObj&) const;
	PrimObjPtr operator<(const PrimObj&) const;
	PrimObjPtr operator<=(const PrimObj&) const;
	PrimObjPtr operator==(const PrimObj&) const;
	PrimObjPtr operator!=(const PrimObj&) const;
	PrimObjPtr operator&&(const PrimObj&) const;
	PrimObjPtr operator||(const PrimObj&) const;

	const std::vector<PrimObjPtr> data;
};


struct CallableObj : public PrimObj {
	virtual ~CallableObj() = default;

	bool to_bool() const { return true; }

  double to_double() const 
    { throw std::runtime_error("No type conversion from callable to double"); }
	virtual std::string to_str() const { return "<callable>"; }
  std::vector<PrimObjPtr> to_arr() const
    { throw std::runtime_error("No type conversion from callable to array"); }
  DomainPtr to_set() const
    { throw std::runtime_error("No type conversion from callable to set"); }
	virtual unsigned arity() const = 0;

	virtual PrimObjPtr call(const std::list<PrimObjPtr> &args) const = 0;
};

// Uses FuncStmt
// might change this since this isn't really my style
class FuncStmt;
struct FuncObj : public CallableObj {
  const std::shared_ptr<FuncStmt> decl;

  FuncObj(const std::shared_ptr<FuncStmt> &_decl) : decl(_decl) { }
  std::string to_str() const;
  unsigned arity() const;

  PrimObjPtr call(const std::list<PrimObjPtr> &args) const;
};


struct SetObj : public PrimObj {
	SetObj(const SetPtr &_data) : data(_data) { } // nonexplicit
	// SetObj(const SetPtr &_data, const SetPtr &_operand)
 //  : data(_data), operand(_operand) { } // nonexplicit
	std::string to_str() const;
  double to_double() const
    { throw std::runtime_error("No type conversion from set to double"); }
	bool to_bool() const;
  std::vector<PrimObjPtr> to_arr() const;
  DomainPtr to_set() const;

	// PrimObjPtr operator!() const;
	PrimObjPtr operator+(const PrimObj&) const;
	// PrimObjPtr operator-(const PrimObj&) const;
	// PrimObjPtr operator*(const PrimObj&) const;
	// PrimObjPtr operator>(const PrimObj&) const;
	// PrimObjPtr operator>=(const PrimObj&) const;
	// PrimObjPtr operator<(const PrimObj&) const;
	// PrimObjPtr operator<=(const PrimObj&) const;
	// PrimObjPtr operator==(const PrimObj&) const;
	// PrimObjPtr operator!=(const PrimObj&) const;
	// PrimObjPtr operator&&(const PrimObj&) const;
	// PrimObjPtr operator||(const PrimObj&) const;

	const SetPtr data;
};

#endif
