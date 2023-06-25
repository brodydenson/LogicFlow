#include "Headers/Interpreter.h"

EnvPtr Interpreter::global_env = std::make_shared<Env>(nullptr);
Parser Interpreter::parser;

void Interpreter::interpret() {
	for (auto &stmt : parser.parse()) {
		stmt->exec(global_env);
	}
}
