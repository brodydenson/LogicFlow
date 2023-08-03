#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include "include/Lexer.h"
#include "include/Parser.h"
#include "include/Interpreter.h"

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
  const string s = buffer.str();
  file.close();

  Interpreter::build_env();

  Parser parser(s);
  Interpreter::set_parser(parser);
  Interpreter::interpret();

	return 0;
}
