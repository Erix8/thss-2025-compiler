#pragma once
#include <string>

enum class TokenType
{
  EOF_T,
  WS,
  UNKNOWN,

  IF,
  ELSE,
  ID,  // IDENT
  INT, // integer literal or keyword
  REAL,
  SCI,

  EQ,
  NE,
  LT,
  LE,
  GT,
  GE,

  L_PAREN,
  R_PAREN,
  L_BRACE,
  R_BRACE,
  L_BRACKET,
  R_BRACKET,
  COMMA,
  SEMI,

  PLUS,
  MINUS,
  MUL,
  DIV,
  DOT,
  // TODO: add more
  SQUOTE
};

struct Token
{
  TokenType type;
  std::string text;
  int line;

  Token(TokenType t = TokenType::EOF_T, std::string tx = "", int ln = 1)
      : type(t), text(std::move(tx)), line(ln) {}
};

std::string tokenTypeToString(TokenType t);
