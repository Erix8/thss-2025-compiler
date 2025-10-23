#include "SysYFormatter.h"

// TODO: Implement specific visitXXX methods.

std::any SysYFormatter::visit(antlr4::tree::ParseTree *tree)
{
    return tree->accept(this);
}
