#include "ANTLRInputStream.h"
#include "CalculatorLexer.h"
#include "CalculatorParser.h"
#include "InterpreterVisitor.h"
#include "ParseTree.h"

#include <fstream>

using namespace antlr4;

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: interpreter <input-file>" << std::endl;
    return 1;
  }

  std::ifstream stream;
  stream.open(argv[1]);
  ANTLRInputStream input(stream);

  CalculatorLexer lexer(&input);
  CommonTokenStream tokens(&lexer);
  CalculatorParser parser(&tokens);

  tree::ParseTree *tree = parser.program();

  // TODO: Create your visitor and interpret the parse tree
  return 0;
}
