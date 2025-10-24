#include "SysYFormatter.h"

// TODO: Implement specific visitXXX methods.

// 根据 indentLevel 在 formattedCode 中增加缩进，一个缩进包含4个空格符
void SysYFormatter::addIndent()
{
    for (int i = 0; i < indentLevel; ++i)
    {
        formattedCode += indentUnit;
    }
}

// 在 formattedCode 中增加换行
void SysYFormatter::addNewline()
{
    formattedCode += "\n";
}

// 获取 formattedCode
std::string SysYFormatter::getFormattedCode()
{
    return formattedCode;
}

// 重写 visit 方法
std::any SysYFormatter::visit(antlr4::tree::ParseTree *tree)
{
    return tree->accept(this);
}