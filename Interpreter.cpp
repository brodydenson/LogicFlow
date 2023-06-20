#include "Interpreter.h"

void Interpreter::interpret() {
	for (auto &stmt : parser.parse()) {
		stmt->exec();
	}
}
