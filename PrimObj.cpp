#include <memory>
#include <iostream>
#include "PrimObj.h"

using std::shared_ptr;
using std::make_shared;
using std::runtime_error;

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
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	return make_shared<DoubleObj>(data + double_rhs.data);
}
PrimObjPtr DoubleObj::operator-(const PrimObj &rhs) const { 
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	return make_shared<DoubleObj>(data - double_rhs.data);
}
PrimObjPtr DoubleObj::operator*(const PrimObj &rhs) const { 
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	return make_shared<DoubleObj>(data * double_rhs.data);
}
PrimObjPtr DoubleObj::operator/(const PrimObj &rhs) const { 
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	if (double_rhs.data == 0) throw runtime_error("Division by 0");
	return make_shared<DoubleObj>(data / double_rhs.data);
}
PrimObjPtr DoubleObj::operator>(const PrimObj &rhs) const { 
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	return make_shared<BoolObj>(data > double_rhs.data);
}
PrimObjPtr DoubleObj::operator>=(const PrimObj &rhs) const { 
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	return make_shared<BoolObj>(data >= double_rhs.data);
}
PrimObjPtr DoubleObj::operator<(const PrimObj &rhs) const { 
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	return make_shared<BoolObj>(data < double_rhs.data);
}
PrimObjPtr DoubleObj::operator<=(const PrimObj &rhs) const { 
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	return make_shared<BoolObj>(data <= double_rhs.data);
}
PrimObjPtr DoubleObj::operator==(const PrimObj &rhs) const { 
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	return make_shared<BoolObj>(data == double_rhs.data);
}
PrimObjPtr DoubleObj::operator!=(const PrimObj &rhs) const { 
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	return make_shared<BoolObj>(data != double_rhs.data);
}
PrimObjPtr DoubleObj::operator&&(const PrimObj &rhs) const { 
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	return make_shared<BoolObj>(data && double_rhs.data);
}
PrimObjPtr DoubleObj::operator||(const PrimObj &rhs) const { 
	const DoubleObj &double_rhs = dynamic_cast<const DoubleObj&>(rhs);
	return make_shared<BoolObj>(data || double_rhs.data);
}

PrimObjPtr StrObj::operator+(const PrimObj &rhs) const { 
	const StrObj &str_rhs = dynamic_cast<const StrObj&>(rhs);
	return make_shared<StrObj>(data + str_rhs.data);
}
PrimObjPtr StrObj::operator>(const PrimObj &rhs) const { 
	const StrObj &str_rhs = dynamic_cast<const StrObj&>(rhs);
	return make_shared<BoolObj>(data > str_rhs.data);
}
PrimObjPtr StrObj::operator>=(const PrimObj &rhs) const { 
	const StrObj &str_rhs = dynamic_cast<const StrObj&>(rhs);
	return make_shared<BoolObj>(data >= str_rhs.data);
}
PrimObjPtr StrObj::operator<(const PrimObj &rhs) const { 
	const StrObj &str_rhs = dynamic_cast<const StrObj&>(rhs);
	return make_shared<BoolObj>(data < str_rhs.data);
}
PrimObjPtr StrObj::operator<=(const PrimObj &rhs) const { 
	const StrObj &str_rhs = dynamic_cast<const StrObj&>(rhs);
	return make_shared<BoolObj>(data <= str_rhs.data);
}
PrimObjPtr StrObj::operator==(const PrimObj &rhs) const { 
	const StrObj &str_rhs = dynamic_cast<const StrObj&>(rhs);
	return make_shared<BoolObj>(data == str_rhs.data);
}
PrimObjPtr StrObj::operator!=(const PrimObj &rhs) const { 
	const StrObj &str_rhs = dynamic_cast<const StrObj&>(rhs);
	return make_shared<BoolObj>(data != str_rhs.data);
}
PrimObjPtr StrObj::operator&&(const PrimObj &rhs) const { 
	const StrObj &str_rhs = dynamic_cast<const StrObj&>(rhs);
	return make_shared<BoolObj>(to_bool() && str_rhs.to_bool());
}
PrimObjPtr StrObj::operator||(const PrimObj &rhs) const { 
	const StrObj &str_rhs = dynamic_cast<const StrObj&>(rhs);
	return make_shared<BoolObj>(to_bool() != str_rhs.to_bool());
}

PrimObjPtr BoolObj::operator!() const { 
	return make_shared<BoolObj>(!data);
}
PrimObjPtr BoolObj::operator+(const PrimObj &rhs) const { 
	const BoolObj &bool_rhs = dynamic_cast<const BoolObj&>(rhs);
	return make_shared<BoolObj>(data + bool_rhs.data);
}
PrimObjPtr BoolObj::operator*(const PrimObj &rhs) const { 
	const BoolObj &bool_rhs = dynamic_cast<const BoolObj&>(rhs);
	return make_shared<BoolObj>(data * bool_rhs.data);
}
PrimObjPtr BoolObj::operator>(const PrimObj &rhs) const { 
	const BoolObj &bool_rhs = dynamic_cast<const BoolObj&>(rhs);
	return make_shared<BoolObj>(data > bool_rhs.data);
}
PrimObjPtr BoolObj::operator>=(const PrimObj &rhs) const { 
	const BoolObj &bool_rhs = dynamic_cast<const BoolObj&>(rhs);
	return make_shared<BoolObj>(data >= bool_rhs.data);
}
PrimObjPtr BoolObj::operator<(const PrimObj &rhs) const { 
	const BoolObj &bool_rhs = dynamic_cast<const BoolObj&>(rhs);
	return make_shared<BoolObj>(data < bool_rhs.data);
}
PrimObjPtr BoolObj::operator<=(const PrimObj &rhs) const { 
	const BoolObj &bool_rhs = dynamic_cast<const BoolObj&>(rhs);
	return make_shared<BoolObj>(data <= bool_rhs.data);
}
PrimObjPtr BoolObj::operator==(const PrimObj &rhs) const { 
	const BoolObj &bool_rhs = dynamic_cast<const BoolObj&>(rhs);
	return make_shared<BoolObj>(data == bool_rhs.data);
}
PrimObjPtr BoolObj::operator!=(const PrimObj &rhs) const { 
	const BoolObj &bool_rhs = dynamic_cast<const BoolObj&>(rhs);
	return make_shared<BoolObj>(data != bool_rhs.data);
}
PrimObjPtr BoolObj::operator&&(const PrimObj &rhs) const { 
	const BoolObj &bool_rhs = dynamic_cast<const BoolObj&>(rhs);
	return make_shared<BoolObj>(data && bool_rhs.data);
}
PrimObjPtr BoolObj::operator||(const PrimObj &rhs) const { 
	const BoolObj &bool_rhs = dynamic_cast<const BoolObj&>(rhs);
	return make_shared<BoolObj>(data || bool_rhs.data);
}
