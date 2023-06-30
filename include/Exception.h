#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include "PrimObj.h"
#include "Tok.h"

class ReturnExcept : public std::exception {
public:
  ReturnExcept(const PrimObjPtr &_val) : val(_val) { }

  std::shared_ptr<PrimObj> get_val() const { return val; }
private:
  const PrimObjPtr val;
};

class ProgError : public std::exception {
public:
  ProgError(const std::string &_msg, const TokPtr &_cur_tok)
    : msg(_msg), cur_tok(_cur_tok) { }
  // I hate c strings, i cant be bothered -w-
  std::string err_msg() const noexcept
    { return "Line " + std::to_string(cur_tok->line) + " | " + msg; }
private:
  const std::string msg;
  const TokPtr cur_tok;
};

#endif
