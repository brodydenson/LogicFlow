#include "include/Interpreter.h"
#include "include/Exception.h"

using std::cerr;
using std::endl;

EnvPtr Interpreter::global_env = std::make_shared<Env>(nullptr);
Parser Interpreter::parser;

void Interpreter::interpret() {
	for (auto &stmt : parser.parse()) {
    try {
      stmt->exec(global_env);
    } catch (ProgError e) {
      cerr << "Runtime Error: " << e.err_msg() << endl;
      exit(0);
    }
	}
}
