
// Generated from Calculator.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CalculatorParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CalculatorParser.
 */
class  CalculatorVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CalculatorParser.
   */
    virtual std::any visitProgram(CalculatorParser::ProgramContext *context) = 0;

    virtual std::any visitStatement(CalculatorParser::StatementContext *context) = 0;

    virtual std::any visitAssignment(CalculatorParser::AssignmentContext *context) = 0;

    virtual std::any visitBlock(CalculatorParser::BlockContext *context) = 0;

    virtual std::any visitPrintStmt(CalculatorParser::PrintStmtContext *context) = 0;

    virtual std::any visitIntExpr(CalculatorParser::IntExprContext *context) = 0;

    virtual std::any visitMulExpr(CalculatorParser::MulExprContext *context) = 0;

    virtual std::any visitLvalExpr(CalculatorParser::LvalExprContext *context) = 0;

    virtual std::any visitParenExpr(CalculatorParser::ParenExprContext *context) = 0;

    virtual std::any visitPlusExpr(CalculatorParser::PlusExprContext *context) = 0;


};

