#ifndef PRIM_OBJ_H
#define PRIM_OBJ_H

#include <string>
#include <list>
#include <memory>

class Tok;

class PrimObj;
typedef std::shared_ptr<PrimObj> PrimObjPtr;

struct PrimObj {
	friend std::ostream &operator<<(std::ostream &os, const PrimObj &obj) 
		{ os << obj.to_str(); return os; }
	virtual ~PrimObj() = default;
	virtual std::string to_str() const = 0;
  virtual double to_double() const = 0;
	virtual bool to_bool() const = 0;
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
	DoubleObj(const std::shared_ptr<Tok>&);
	DoubleObj(double _data) : data(_data) { } // nonexplicit
	std::string to_str() const { return std::to_string(data); }
  double to_double() const { return data; }
	bool to_bool() const { return data != 0; }
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
	StrObj(const std::shared_ptr<Tok>&);
	StrObj(const std::string &_data) : data(_data) { } // nonexplicit
	std::string to_str() const { return data; }
  double to_double() const
    { throw std::runtime_error("No type conversion from string to double"); }
	bool to_bool() const { return data.length() != 0; }
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
	BoolObj(const std::shared_ptr<Tok>&);
	BoolObj(bool _data) : data(_data) { } // nonexplicit
	std::string to_str() const { return std::to_string(data); }
  double to_double() const
    { throw std::runtime_error("No type conversion from bool to double"); }
	bool to_bool() const { return data; }
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

struct CallableObj : public PrimObj {
	virtual ~CallableObj() = default;

	bool to_bool() const { return true; }

  double to_double() const 
    { throw std::runtime_error("No type conversion from callable to double"); }
	virtual std::string to_str() const { return "<callable>"; }
	virtual unsigned arity() const = 0;

	virtual PrimObjPtr call(const std::list<PrimObjPtr> &args) = 0;
};

class FuncStmt;
struct FuncObj : public CallableObj {
  const std::shared_ptr<FuncStmt> decl;

  FuncObj(const std::shared_ptr<FuncStmt> &_decl) : decl(_decl) { }
  std::string to_str() const;
  std::shared_ptr<Tok> get_tok() const { return tok; }
  unsigned arity() const;

  PrimObjPtr call(const std::list<PrimObjPtr> &args);

  const std::shared_ptr<Tok> tok;
};

#endif
