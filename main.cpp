#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Headers/Lexer.h"
#include "Headers/Parser.h"
#include "Headers/Interpreter.h"

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::ostringstream;

int main() {
 //  string line;
	// while (cout << ">> " && getline(cin, line) && line != "exit") {
 //    Parser parser(line);
 //    Interpreter::set_parser(parser);
 //    Interpreter::interpret();
	// }

  ifstream file("source.txt");
  ostringstream buffer;
  buffer << file.rdbuf();

  string s = buffer.str();
  // IDK how to skip eof char
  Parser parser(string(s.cbegin(), s.cend()-1));
  Interpreter::set_parser(parser);
  Interpreter::interpret();

	return 0;
}
