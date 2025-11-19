
// Generated from Calculator.g4 by ANTLR 4.13.1


#include "CalculatorVisitor.h"

#include "CalculatorParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CalculatorParserStaticData final {
  CalculatorParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CalculatorParserStaticData(const CalculatorParserStaticData&) = delete;
  CalculatorParserStaticData(CalculatorParserStaticData&&) = delete;
  CalculatorParserStaticData& operator=(const CalculatorParserStaticData&) = delete;
  CalculatorParserStaticData& operator=(CalculatorParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag calculatorParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
CalculatorParserStaticData *calculatorParserStaticData = nullptr;

void calculatorParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (calculatorParserStaticData != nullptr) {
    return;
  }
#else
  assert(calculatorParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CalculatorParserStaticData>(
    std::vector<std::string>{
      "program", "statement", "assignment", "block", "printStmt", "expr"
    },
    std::vector<std::string>{
      "", "'='", "';'", "'{'", "'}'", "'print'", "'('", "')'", "", "", "'*'", 
      "'/'", "'%'", "'+'", "'-'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "INT", "ID", "MUL", "DIV", "MOD", 
      "PLUS", "MINUS", "WS", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,16,63,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,1,0,4,0,14,
  	8,0,11,0,12,0,15,1,0,1,0,1,1,1,1,1,1,3,1,23,8,1,1,2,1,2,1,2,1,2,1,2,1,
  	3,1,3,5,3,32,8,3,10,3,12,3,35,9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,5,1,5,1,5,
  	1,5,1,5,1,5,1,5,3,5,50,8,5,1,5,1,5,1,5,1,5,1,5,1,5,5,5,58,8,5,10,5,12,
  	5,61,9,5,1,5,0,1,10,6,0,2,4,6,8,10,0,2,1,0,10,12,1,0,13,14,64,0,13,1,
  	0,0,0,2,22,1,0,0,0,4,24,1,0,0,0,6,29,1,0,0,0,8,38,1,0,0,0,10,49,1,0,0,
  	0,12,14,3,2,1,0,13,12,1,0,0,0,14,15,1,0,0,0,15,13,1,0,0,0,15,16,1,0,0,
  	0,16,17,1,0,0,0,17,18,5,0,0,1,18,1,1,0,0,0,19,23,3,4,2,0,20,23,3,6,3,
  	0,21,23,3,8,4,0,22,19,1,0,0,0,22,20,1,0,0,0,22,21,1,0,0,0,23,3,1,0,0,
  	0,24,25,5,9,0,0,25,26,5,1,0,0,26,27,3,10,5,0,27,28,5,2,0,0,28,5,1,0,0,
  	0,29,33,5,3,0,0,30,32,3,2,1,0,31,30,1,0,0,0,32,35,1,0,0,0,33,31,1,0,0,
  	0,33,34,1,0,0,0,34,36,1,0,0,0,35,33,1,0,0,0,36,37,5,4,0,0,37,7,1,0,0,
  	0,38,39,5,5,0,0,39,40,3,10,5,0,40,41,5,2,0,0,41,9,1,0,0,0,42,43,6,5,-1,
  	0,43,44,5,6,0,0,44,45,3,10,5,0,45,46,5,7,0,0,46,50,1,0,0,0,47,50,5,9,
  	0,0,48,50,5,8,0,0,49,42,1,0,0,0,49,47,1,0,0,0,49,48,1,0,0,0,50,59,1,0,
  	0,0,51,52,10,2,0,0,52,53,7,0,0,0,53,58,3,10,5,3,54,55,10,1,0,0,55,56,
  	7,1,0,0,56,58,3,10,5,2,57,51,1,0,0,0,57,54,1,0,0,0,58,61,1,0,0,0,59,57,
  	1,0,0,0,59,60,1,0,0,0,60,11,1,0,0,0,61,59,1,0,0,0,6,15,22,33,49,57,59
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  calculatorParserStaticData = staticData.release();
}

}

CalculatorParser::CalculatorParser(TokenStream *input) : CalculatorParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CalculatorParser::CalculatorParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CalculatorParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *calculatorParserStaticData->atn, calculatorParserStaticData->decisionToDFA, calculatorParserStaticData->sharedContextCache, options);
}

CalculatorParser::~CalculatorParser() {
  delete _interpreter;
}

const atn::ATN& CalculatorParser::getATN() const {
  return *calculatorParserStaticData->atn;
}

std::string CalculatorParser::getGrammarFileName() const {
  return "Calculator.g4";
}

const std::vector<std::string>& CalculatorParser::getRuleNames() const {
  return calculatorParserStaticData->ruleNames;
}

const dfa::Vocabulary& CalculatorParser::getVocabulary() const {
  return calculatorParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CalculatorParser::getSerializedATN() const {
  return calculatorParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

CalculatorParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CalculatorParser::ProgramContext::EOF() {
  return getToken(CalculatorParser::EOF, 0);
}

std::vector<CalculatorParser::StatementContext *> CalculatorParser::ProgramContext::statement() {
  return getRuleContexts<CalculatorParser::StatementContext>();
}

CalculatorParser::StatementContext* CalculatorParser::ProgramContext::statement(size_t i) {
  return getRuleContext<CalculatorParser::StatementContext>(i);
}


size_t CalculatorParser::ProgramContext::getRuleIndex() const {
  return CalculatorParser::RuleProgram;
}


std::any CalculatorParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

CalculatorParser::ProgramContext* CalculatorParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, CalculatorParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(13); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(12);
      statement();
      setState(15); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 552) != 0));
    setState(17);
    match(CalculatorParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

CalculatorParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CalculatorParser::AssignmentContext* CalculatorParser::StatementContext::assignment() {
  return getRuleContext<CalculatorParser::AssignmentContext>(0);
}

CalculatorParser::BlockContext* CalculatorParser::StatementContext::block() {
  return getRuleContext<CalculatorParser::BlockContext>(0);
}

CalculatorParser::PrintStmtContext* CalculatorParser::StatementContext::printStmt() {
  return getRuleContext<CalculatorParser::PrintStmtContext>(0);
}


size_t CalculatorParser::StatementContext::getRuleIndex() const {
  return CalculatorParser::RuleStatement;
}


std::any CalculatorParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

CalculatorParser::StatementContext* CalculatorParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, CalculatorParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(22);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CalculatorParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(19);
        assignment();
        break;
      }

      case CalculatorParser::T__2: {
        enterOuterAlt(_localctx, 2);
        setState(20);
        block();
        break;
      }

      case CalculatorParser::T__4: {
        enterOuterAlt(_localctx, 3);
        setState(21);
        printStmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

CalculatorParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CalculatorParser::AssignmentContext::ID() {
  return getToken(CalculatorParser::ID, 0);
}

CalculatorParser::ExprContext* CalculatorParser::AssignmentContext::expr() {
  return getRuleContext<CalculatorParser::ExprContext>(0);
}


size_t CalculatorParser::AssignmentContext::getRuleIndex() const {
  return CalculatorParser::RuleAssignment;
}


std::any CalculatorParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

CalculatorParser::AssignmentContext* CalculatorParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 4, CalculatorParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(24);
    match(CalculatorParser::ID);
    setState(25);
    match(CalculatorParser::T__0);
    setState(26);
    expr(0);
    setState(27);
    match(CalculatorParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

CalculatorParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CalculatorParser::StatementContext *> CalculatorParser::BlockContext::statement() {
  return getRuleContexts<CalculatorParser::StatementContext>();
}

CalculatorParser::StatementContext* CalculatorParser::BlockContext::statement(size_t i) {
  return getRuleContext<CalculatorParser::StatementContext>(i);
}


size_t CalculatorParser::BlockContext::getRuleIndex() const {
  return CalculatorParser::RuleBlock;
}


std::any CalculatorParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

CalculatorParser::BlockContext* CalculatorParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 6, CalculatorParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(29);
    match(CalculatorParser::T__2);
    setState(33);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 552) != 0)) {
      setState(30);
      statement();
      setState(35);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(36);
    match(CalculatorParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrintStmtContext ------------------------------------------------------------------

CalculatorParser::PrintStmtContext::PrintStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CalculatorParser::ExprContext* CalculatorParser::PrintStmtContext::expr() {
  return getRuleContext<CalculatorParser::ExprContext>(0);
}


size_t CalculatorParser::PrintStmtContext::getRuleIndex() const {
  return CalculatorParser::RulePrintStmt;
}


std::any CalculatorParser::PrintStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitPrintStmt(this);
  else
    return visitor->visitChildren(this);
}

CalculatorParser::PrintStmtContext* CalculatorParser::printStmt() {
  PrintStmtContext *_localctx = _tracker.createInstance<PrintStmtContext>(_ctx, getState());
  enterRule(_localctx, 8, CalculatorParser::RulePrintStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(38);
    match(CalculatorParser::T__4);
    setState(39);
    expr(0);
    setState(40);
    match(CalculatorParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

CalculatorParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CalculatorParser::ExprContext::getRuleIndex() const {
  return CalculatorParser::RuleExpr;
}

void CalculatorParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IntExprContext ------------------------------------------------------------------

tree::TerminalNode* CalculatorParser::IntExprContext::INT() {
  return getToken(CalculatorParser::INT, 0);
}

CalculatorParser::IntExprContext::IntExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalculatorParser::IntExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitIntExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulExprContext ------------------------------------------------------------------

std::vector<CalculatorParser::ExprContext *> CalculatorParser::MulExprContext::expr() {
  return getRuleContexts<CalculatorParser::ExprContext>();
}

CalculatorParser::ExprContext* CalculatorParser::MulExprContext::expr(size_t i) {
  return getRuleContext<CalculatorParser::ExprContext>(i);
}

tree::TerminalNode* CalculatorParser::MulExprContext::MUL() {
  return getToken(CalculatorParser::MUL, 0);
}

tree::TerminalNode* CalculatorParser::MulExprContext::DIV() {
  return getToken(CalculatorParser::DIV, 0);
}

tree::TerminalNode* CalculatorParser::MulExprContext::MOD() {
  return getToken(CalculatorParser::MOD, 0);
}

CalculatorParser::MulExprContext::MulExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalculatorParser::MulExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitMulExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LvalExprContext ------------------------------------------------------------------

tree::TerminalNode* CalculatorParser::LvalExprContext::ID() {
  return getToken(CalculatorParser::ID, 0);
}

CalculatorParser::LvalExprContext::LvalExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalculatorParser::LvalExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitLvalExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

CalculatorParser::ExprContext* CalculatorParser::ParenExprContext::expr() {
  return getRuleContext<CalculatorParser::ExprContext>(0);
}

CalculatorParser::ParenExprContext::ParenExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalculatorParser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PlusExprContext ------------------------------------------------------------------

std::vector<CalculatorParser::ExprContext *> CalculatorParser::PlusExprContext::expr() {
  return getRuleContexts<CalculatorParser::ExprContext>();
}

CalculatorParser::ExprContext* CalculatorParser::PlusExprContext::expr(size_t i) {
  return getRuleContext<CalculatorParser::ExprContext>(i);
}

tree::TerminalNode* CalculatorParser::PlusExprContext::PLUS() {
  return getToken(CalculatorParser::PLUS, 0);
}

tree::TerminalNode* CalculatorParser::PlusExprContext::MINUS() {
  return getToken(CalculatorParser::MINUS, 0);
}

CalculatorParser::PlusExprContext::PlusExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any CalculatorParser::PlusExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CalculatorVisitor*>(visitor))
    return parserVisitor->visitPlusExpr(this);
  else
    return visitor->visitChildren(this);
}

CalculatorParser::ExprContext* CalculatorParser::expr() {
   return expr(0);
}

CalculatorParser::ExprContext* CalculatorParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CalculatorParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  CalculatorParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, CalculatorParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(49);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CalculatorParser::T__5: {
        _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(43);
        match(CalculatorParser::T__5);
        setState(44);
        expr(0);
        setState(45);
        match(CalculatorParser::T__6);
        break;
      }

      case CalculatorParser::ID: {
        _localctx = _tracker.createInstance<LvalExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(47);
        match(CalculatorParser::ID);
        break;
      }

      case CalculatorParser::INT: {
        _localctx = _tracker.createInstance<IntExprContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(48);
        match(CalculatorParser::INT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(59);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(57);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MulExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(51);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(52);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 7168) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(53);
          expr(3);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<PlusExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(54);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(55);
          _la = _input->LA(1);
          if (!(_la == CalculatorParser::PLUS

          || _la == CalculatorParser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(56);
          expr(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(61);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool CalculatorParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 5: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CalculatorParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void CalculatorParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  calculatorParserInitialize();
#else
  ::antlr4::internal::call_once(calculatorParserOnceFlag, calculatorParserInitialize);
#endif
}
