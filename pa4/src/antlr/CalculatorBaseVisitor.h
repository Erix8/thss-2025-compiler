
// Generated from Calculator.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "CalculatorVisitor.h"


/**
 * This class provides an empty implementation of CalculatorVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CalculatorBaseVisitor : public CalculatorVisitor {
public:

  virtual std::any visitProgram(CalculatorParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(CalculatorParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(CalculatorParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(CalculatorParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrintStmt(CalculatorParser::PrintStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntExpr(CalculatorParser::IntExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulExpr(CalculatorParser::MulExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLvalExpr(CalculatorParser::LvalExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpr(CalculatorParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPlusExpr(CalculatorParser::PlusExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

