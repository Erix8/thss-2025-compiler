#pragma once
#include <string>
#include <any>
#include "../src/SysYParserBaseVisitor.h"
// TODO: Implement SysYFormatter

class SysYFormatter : public SysYParserBaseVisitor
{
private:
    std::string formattedCode;             // 存储格式化后的代码
    int indentLevel = 0;                   // 缩进级别控制
    const std::string indentUnit = "    "; // 缩进单位（4空格）
    void addIndent();                      // 辅助方法：添加缩进
    void addNewline();                     // 辅助方法：添加换行

public:
    std::any visit(antlr4::tree::ParseTree *tree) override;
    std::any visitCompUnit(SysYParser::CompUnitContext *ctx) override;
    std::any visitDecl(SysYParser::DeclContext *ctx) override;
    std::any visitConstDecl(SysYParser::ConstDeclContext *ctx) override;
    std::any visitBType(SysYParser::BTypeContext *ctx) override;
    std::any visitConstDef(SysYParser::ConstDefContext *ctx) override;
    std::any visitConstInitVal(SysYParser::ConstInitValContext *ctx) override;
    std::any visitVarDecl(SysYParser::VarDeclContext *ctx) override;
    std::any visitVarDef(SysYParser::VarDefContext *ctx) override;
    std::any visitInitVal(SysYParser::InitValContext *ctx) override;
    std::any visitFuncDef(SysYParser::FuncDefContext *ctx) override;
    std::any visitFuncType(SysYParser::FuncTypeContext *ctx) override;
    std::any visitFuncFParams(SysYParser::FuncFParamsContext *ctx) override;
    std::any visitFuncFParam(SysYParser::FuncFParamContext *ctx) override;
    std::any visitBlock(SysYParser::BlockContext *ctx) override;
    std::any visitBlockItem(SysYParser::BlockItemContext *ctx) override;
    std::any visitStmt(SysYParser::StmtContext *ctx) override;
    std::any visitExp(SysYParser::ExpContext *ctx) override;
    std::any visitCond(SysYParser::CondContext *ctx) override;
    std::any visitLVal(SysYParser::LValContext *ctx) override;
    std::any visitPrimaryExp(SysYParser::PrimaryExpContext *ctx) override;
    std::any visitNumber(SysYParser::NumberContext *ctx) override;
    std::any visitUnaryExp(SysYParser::UnaryExpContext *ctx) override;
    std::any visitUnaryOp(SysYParser::UnaryOpContext *ctx) override;
    std::any visitFuncRParams(SysYParser::FuncRParamsContext *ctx) override;
    std::any visitMulExp(SysYParser::MulExpContext *ctx) override;
    std::any visitAddExp(SysYParser::AddExpContext *ctx) override;
    std::any visitRelExp(SysYParser::RelExpContext *ctx) override;
    std::any visitEqExp(SysYParser::EqExpContext *ctx) override;
    std::any visitLAndExp(SysYParser::LAndExpContext *ctx) override;
    std::any visitLOrExp(SysYParser::LOrExpContext *ctx) override;
    std::any visitConstExp(SysYParser::ConstExpContext *ctx) override;
};