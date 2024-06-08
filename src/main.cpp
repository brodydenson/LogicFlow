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

bool interpret_file(const string &path) {
  const string content = read_file(path);
  if (content == "") return false;

  Parser parser(content);
  Interpreter::set_parser(parser);
  Interpreter::interpret();
  return true;
}

int main(int argc, char *args[]) {
 //  string line;
	// while (cout << ">> " && getline(cin, line) && line != "exit") {
 //    Parser parser(line);
 //    Interpreter::set_parser(parser);
 //    Interpreter::interpret();
	// }


  if (argc != 2) {
    cout << "please enter (1) file as argument (file type must be .lf)" << endl;
    return 0;
  }

  Interpreter::build_env();
  
  if (!interpret_file("std.lf"))
    interpret_file("../std.lf");
  if (!interpret_file(args[1]))
    cout << "cannot find file: " << args[1] << endl;


	return 0;
}
