#include <iostream>
#include "PrimObj.h"

class ReturnExcept : public std::exception {
public:
  ReturnExcept(const PrimObjPtr &_val) : val(_val) { }

  PrimObjPtr get_val() const { return val; }
private:
  PrimObjPtr val;
};
