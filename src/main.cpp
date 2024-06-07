#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ostringstream;

string read_file(const string &path) {
  ifstream file(path);
  ostringstream buffer;
  buffer << file.rdbuf();
  file.close();
  return buffer.str();
}

void interpret_file(const string &path) {
  const string content = read_file(path);

  Parser parser(content);
  Interpreter::set_parser(parser);
  Interpreter::interpret();
}

int main() {
 //  string line;
	// while (cout << ">> " && getline(cin, line) && line != "exit") {
 //    Parser parser(line);
 //    Interpreter::set_parser(parser);
 //    Interpreter::interpret();
	// }

  Interpreter::build_env();
  interpret_file("../std.lf");
  interpret_file("../main.lf");

	return 0;
}
