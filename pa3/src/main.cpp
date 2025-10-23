#include <iostream>
#include <fstream>
#include <any>
#include "antlr4-runtime.h"
#include "SysYLexer.h"
#include "SysYParser.h"
#include "SysYFormatter.h"

using namespace antlr4;

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: sysy_formatter <input-file>" << std::endl;
        return 1;
    }

    std::ifstream stream;
    stream.open(argv[1]);

    ANTLRInputStream input(stream);            // 创建 ANTLRInputStream 对象
    SysYLexer lexer(&input);                   // 创建 SysYLexer 对象
    CommonTokenStream tokens(&lexer);          // 创建 CommonTokenStream 对象
    SysYParser parser(&tokens);                // 创建 SysYParser 对象
    tree::ParseTree *tree = parser.compUnit(); // 获取语法分析树

    SysYFormatter formatter;                                // 创建 SysYFormatter 对象
    formatter.visit(tree);                                  // 进行代码格式化排版
    std::cout << formatter.getFormattedCode() << std::endl; // 输出格式化后代码
    return 0;
}