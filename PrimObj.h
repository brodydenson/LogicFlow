#ifndef PRIM_OBJ_H
#define PRIM_OBJ_H

#include <string>
#include <list>
#include <memory>

class PrimObj;
typedef std::shared_ptr<PrimObj> PrimObjPtr;

struct PrimObj {
	friend std::ostream &operator<<(std::ostream &os, const PrimObj &obj) 
		{ os << obj.to_string(); return os; }
	virtual ~PrimObj() = default;
	virtual std::string to_string() const;
	virtual bool to_bool() const;
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
	std::string to_string() const { return std::to_string(data); }
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

	double data;
};

struct StrObj : public PrimObj {
	StrObj(const std::string &_data) : data(_data) { } // nonexplicit
	std::string to_string() const { return data; }
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

	std::string data;
};

struct BoolObj : public PrimObj {
	BoolObj(bool _data) : data(_data) { } // nonexplicit
	std::string to_string() const { return std::to_string(data); }
	bool to_bool() const { return data; }
	PrimObjPtr operator!() const;
	PrimObjPtr operator+(const PrimObj&) const;
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

	bool data;
};

struct FuncObj : public PrimObj {
	FuncObj();
};

// struct CallableObj : public PrimObj {
// 	CallableObj(unsigned _arity) { } // nonexplicit
// 	std::string to_string() const { return "<function>"; }
// 	bool to_bool() const { return true; }
//
// 	PrimObjPtr call(const std::list<PrimObjPtr> &args) const;
//
// 	unsigned arity;
// };

#endif
