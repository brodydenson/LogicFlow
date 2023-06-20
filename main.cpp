#include <iostream>
#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "Lit.h"
#include "BinOp.h"
#include "Expr.h"
#include "Interpreter.h"

using std::cout;
using std::cin;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::endl;
using tok_t::TokType;

int main() {
	// string content = "var x = 5; print x - 3;";
	// Parser parser(content);
	// parser.print_toks();
	// Interpreter interpreter(parser);
	// interpreter.interpret();
	string line;
	while (cout << ">> " && getline(cin, line) && line != "exit") {
		Parser parser(line);
		parser.print_toks();
		Interpreter interpreter(parser);
		interpreter.interpret();
	}

	return 0;
}
