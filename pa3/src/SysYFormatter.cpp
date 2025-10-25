#include "SysYFormatter.h"

// 根据 indentLevel 在 formattedCode 中增加缩进，一个缩进包含4个空格符
void SysYFormatter::addIndent()
{
    for (int i = 0; i < indentLevel; ++i)
        formattedCode += indentUnit;
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

std::any SysYFormatter::visitCompUnit(SysYParser::CompUnitContext *ctx)
{
    addIndent();
    visitChildren(ctx);
    return nullptr;
}

std::any SysYFormatter::visitDecl(SysYParser::DeclContext *ctx)
{
    addIndent();
    visitChildren(ctx);
    addNewline();
    return nullptr;
}

std::any SysYFormatter::visitConstDecl(SysYParser::ConstDeclContext *ctx)
{
    addIndent();
    formattedCode += "const ";
    visit(ctx->bType());
    for (size_t i = 0; i < ctx->constDef().size(); ++i)
    {
        if (i > 0)
            formattedCode += ", ";
        visit(ctx->constDef(i));
    }
    formattedCode += ";";
    addNewline();
    return nullptr;
}

std::any SysYFormatter::visitBType(SysYParser::BTypeContext *ctx)
{
    if (ctx->INT())
        formattedCode += "int ";
    return nullptr;
}

std::any SysYFormatter::visitConstDef(SysYParser::ConstDefContext *ctx)
{
    formattedCode += ctx->IDENT()->getText();
    for (int i = 0; i < ctx->constExp().size(); ++i)
    {
        formattedCode += "[";
        visit(ctx->constExp(i));
        formattedCode += "]";
    }
    formattedCode += " = ";
    visit(ctx->constInitVal());
    return nullptr;
}

std::any SysYFormatter::visitConstInitVal(SysYParser::ConstInitValContext *ctx)
{
    if (ctx->constExp())
        visitChildren(ctx);
    else
    {
        formattedCode += "{";
        for (int i = 0; i < ctx->constInitVal().size(); ++i)
        {
            if (i > 0)
                formattedCode += ", ";
            visit(ctx->constInitVal(i));
        }
        formattedCode += "}";
    }
    return nullptr;
}

std::any SysYFormatter::visitVarDecl(SysYParser::VarDeclContext *ctx)
{
    addIndent();
    visit(ctx->bType());
    for (int i = 0; i < ctx->varDef().size(); ++i)
    {
        if (i > 0)
            formattedCode += ", ";
        visit(ctx->varDef(i));
    }
    formattedCode += ";";
    addNewline();
    return nullptr;
}

std::any SysYFormatter::visitVarDef(SysYParser::VarDefContext *ctx)
{
    formattedCode += ctx->IDENT()->getText();
    for (int i = 0; i < ctx->constExp().size(); ++i)
    {
        formattedCode += "[";
        visit(ctx->constExp(i));
        formattedCode += "]";
    }
    if (ctx->ASSIGN())
    {
        formattedCode += " = ";
        visit(ctx->initVal());
    }
    return nullptr;
}

std::any SysYFormatter::visitInitVal(SysYParser::InitValContext *ctx)
{
    if (ctx->exp())
        visitChildren(ctx);
    else
    {
        formattedCode += "{";
        for (int i = 0; i < ctx->initVal().size(); ++i)
        {
            if (i > 0)
                formattedCode += " ,";
            visit(ctx->initVal(i));
        }
        formattedCode += "}";
    }
    return nullptr;
}

std::any SysYFormatter::visitFuncDef(SysYParser::FuncDefContext *ctx)
{
    visit(ctx->funcType());
    formattedCode += ctx->IDENT()->getText();
    formattedCode += "(";
    if (ctx->funcFParams())
        visit(ctx->funcFParams());
    formattedCode += ") ";
    visit(ctx->block());
    return nullptr;
}

std::any SysYFormatter::visitFuncType(SysYParser::FuncTypeContext *ctx)
{
    if (ctx->VOID())
        formattedCode += "void ";
    else if (ctx->INT())
        formattedCode += "int ";
    return nullptr;
}

std::any SysYFormatter::visitFuncFParams(SysYParser::FuncFParamsContext *ctx)
{
    for (int i = 0; i < ctx->funcFParam().size(); ++i)
    {
        if (i > 0)
            formattedCode += ", ";
        visit(ctx->funcFParam(i));
    }
    return nullptr;
}

std::any SysYFormatter::visitFuncFParam(SysYParser::FuncFParamContext *ctx)
{
    visit(ctx->bType());
    formattedCode += ctx->IDENT()->getText();
    if (ctx->L_BRACKT(0))
    {
        formattedCode += "[]";
        if (ctx->exp(0))
        {
            for (int i = 0; i < ctx->exp().size(); ++i)
            {
                formattedCode += "[";
                visit(ctx->exp(i));
                formattedCode += "]";
            }
        }
    }
    return nullptr;
}

std::any SysYFormatter::visitBlock(SysYParser::BlockContext *ctx)
{
    formattedCode += "{";
    addNewline();
    indentLevel++;
    for (int i = 0; i < ctx->blockItem().size(); ++i)
        visit(ctx->blockItem(i));
    indentLevel--;
    addIndent();
    formattedCode += "}";
    addNewline();
    return nullptr;
}

std::any SysYFormatter::visitBlockItem(SysYParser::BlockItemContext *ctx)
{
    visitChildren(ctx);
    return nullptr;
}

std::any SysYFormatter::visitStmt(SysYParser::StmtContext *ctx)
{
    if (ctx->lVal())
    {
        addIndent();
        visit(ctx->lVal());
        formattedCode += " = ";
        visit(ctx->exp());
        formattedCode += ";";
        addNewline();
    }
    else if (ctx->block())
    {
        visitChildren(ctx);
    }
    else if (ctx->IF())
    {
        // TODO:缩进规范调整
        formattedCode += "if (";
        visit(ctx->cond());
        formattedCode += ") ";
        visit(ctx->stmt(0));
        if (ctx->ELSE())
        {
            formattedCode += "else ";
            visit(ctx->stmt(1));
        }
    }
    else if (ctx->WHILE())
    {
        // TODO:缩进规范调整
        formattedCode += "while (";
        visit(ctx->cond());
        formattedCode += ") ";
        visit(ctx->stmt(0));
    }
    else if (ctx->BREAK())
    {
        formattedCode += "break;";
        addNewline();
    }
    else if (ctx->CONTINUE())
    {
        formattedCode += "continue;";
        addNewline();
    }
    else if (ctx->RETURN())
    {
        formattedCode += "return";
        if (ctx->exp())
        {
            formattedCode += " ";
            visit(ctx->exp());
        }
        formattedCode += ";";
        addNewline();
    }
    else
    {
        if (ctx->exp())
            visit(ctx->exp());
        formattedCode += ";";
        addNewline();
    };
    return nullptr;
}

std::any SysYFormatter::visitExp(SysYParser::ExpContext *ctx)
{
    visitChildren(ctx);
    return nullptr;
}

std::any SysYFormatter::visitCond(SysYParser::CondContext *ctx)
{
    visitChildren(ctx);
    return nullptr;
}

std::any SysYFormatter::visitLVal(SysYParser::LValContext *ctx)
{
    formattedCode += ctx->IDENT()->getText();
    for (int i = 0; i < ctx->exp().size(); ++i)
    {
        formattedCode += "[";
        visit(ctx->exp(i));
        formattedCode += "]";
    }
    return nullptr;
}

std::any SysYFormatter::visitPrimaryExp(SysYParser::PrimaryExpContext *ctx)
{
    if (ctx->exp())
    {
        formattedCode += "(";
        visitChildren(ctx);
        formattedCode += ")";
    }
    else
    {
        visitChildren(ctx);
    }
    return nullptr;
}

std::any SysYFormatter::visitNumber(SysYParser::NumberContext *ctx)
{
    formattedCode += ctx->INTEGER_CONST()->getText();
    return nullptr;
}

std::any SysYFormatter::visitUnaryExp(SysYParser::UnaryExpContext *ctx)
{
    if (ctx->primaryExp())
    {
        visitChildren(ctx);
    }
    else if (ctx->funcRParams())
    {
        formattedCode += ctx->IDENT()->getText();
        formattedCode += "(";
        visit(ctx->funcRParams());
        formattedCode += ")";
    }
    else if (ctx->unaryOp())
    {
        visit(ctx->unaryOp());
        visit(ctx->unaryExp());
    }
    return nullptr;
}

std::any SysYFormatter::visitUnaryOp(SysYParser::UnaryOpContext *ctx)
{
    if (ctx->PLUS())
        formattedCode += " + ";
    else if (ctx->MINUS())
        formattedCode += " - ";
    else if (ctx->NOT())
        formattedCode += "!";
    return nullptr;
}

std::any SysYFormatter::visitFuncRParams(SysYParser::FuncRParamsContext *ctx)
{
    for (int i = 0; i < ctx->exp().size(); ++i)
    {
        if (i > 0)
            formattedCode += ", ";
        visit(ctx->exp(i));
    }
    return nullptr;
}

std::any SysYFormatter::visitMulExp(SysYParser::MulExpContext *ctx)
{
    if (ctx->mulExp())
    {
        visit(ctx->mulExp());
        if (ctx->MUL())
            formattedCode += " * ";
        else if (ctx->DIV())
            formattedCode += " / ";
        else if (ctx->MOD())
            formattedCode += " % ";
        visit(ctx->unaryExp());
    }
    else
        visitChildren(ctx);
    return nullptr;
}

std::any SysYFormatter::visitAddExp(SysYParser::AddExpContext *ctx)
{
    if (ctx->addExp())
    {
        visit(ctx->addExp());
        if (ctx->PLUS())
            formattedCode += " + ";
        else if (ctx->MINUS())
            formattedCode += " - ";
        visit(ctx->mulExp());
    }
    else
        visitChildren(ctx);
    return nullptr;
}

std::any SysYFormatter::visitRelExp(SysYParser::RelExpContext *ctx)
{
    if (ctx->relExp())
    {
        visit(ctx->relExp());
        if (ctx->LT())
            formattedCode += " < ";
        else if (ctx->GT())
            formattedCode += " > ";
        else if (ctx->LE())
            formattedCode += " <= ";
        else if (ctx->GE())
            formattedCode += " >= ";
        visit(ctx->addExp());
    }
    else
        visitChildren(ctx);
    return nullptr;
}

std::any SysYFormatter::visitEqExp(SysYParser::EqExpContext *ctx)
{
    if (ctx->eqExp())
    {
        visit(ctx->eqExp());
        if (ctx->EQ())
            formattedCode += " == ";
        else if (ctx->NEQ())
            formattedCode += " != ";
        visit(ctx->relExp());
    }
    else
        visitChildren(ctx);
    return nullptr;
}

std::any SysYFormatter::visitLAndExp(SysYParser::LAndExpContext *ctx)
{
    if (ctx->lAndExp())
    {
        visit(ctx->lAndExp());
        formattedCode += " && ";
        visit(ctx->eqExp());
    }
    else
        visitChildren(ctx);
    return nullptr;
}

std::any SysYFormatter::visitLOrExp(SysYParser::LOrExpContext *ctx)
{
    if (ctx->lOrExp())
    {
        visit(ctx->lOrExp());
        formattedCode += " || ";
        visit(ctx->lAndExp());
    }
    else
        visitChildren(ctx);
    return nullptr;
}

std::any SysYFormatter::visitConstExp(SysYParser::ConstExpContext *ctx)
{
    visitChildren(ctx);
    return nullptr;
}