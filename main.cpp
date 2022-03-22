#include <iostream>

#include "Parser.h"
#include "Interpreter.h"

int main(int argc, char* argv[]) {

  vector<Token> myTokens;
  
  string fileName = argv[1];
  
  Token t;

  Scanner s = Scanner(s.ReadFile(fileName));

  while(!(t.checkEnd())) {
    t = s.scanToken();
    myTokens.push_back(t);

  }

  Parser p = Parser(myTokens);

  p.removeComment();

  p.datalogProgram();

  Interpreter i(p.getDataLog());
  
  i.evalRules();

  i.evalQueries();

  return 0;

}