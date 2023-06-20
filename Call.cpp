#include <memory>
#include "Call.h"

using std::dynamic_pointer_cast;
using std::runtime_error;
using std::list;

void Call::print_expr(std::ostream &os) const {
	os << *callee << '(';
	// Probably a much cleaner way of doing this... too bad
	for (auto it = args.cbegin(); it != args.cend(); ++it)
		{ os << **it; if (++std::move(it) != args.cend()) os << ", "; }
	os << ')';
}

PrimObjPtr Call::eval() const {
	auto func_obj = dynamic_pointer_cast<FuncObj>(callee->eval());
	if (!func_obj) throw runtime_error("Invalid callable object");

	list<PrimObjPtr> args_objs;
	for (auto it = args.cbegin(); it != args.cend(); ++it)
		args_objs.push_back((*it)->eval());
	
	return func_obj->call(args_objs);
}
