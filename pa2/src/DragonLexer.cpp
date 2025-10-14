#include "DragonLexer.hpp"
#include "Token.hpp"
#include <cctype>
#include <string>

DragonLexer::DragonLexer(const std::string &input)
    : Lexer(input) {}

Token DragonLexer::nextToken()
{
  if (peek == EOF_CHAR)
  {
    return Token(TokenType::EOF_T, "EOF", line);
  }

  if (std::isspace(static_cast<char>(peek)))
  {
    return WS();
  }

  // You need to consider when to call ID()
  if (std::isalpha(static_cast<char>(peek)))
  {
    return ID();
  }

  if (std::isdigit(static_cast<char>(peek)))
  {
    return NUMBER();
  }

  int cur = peek;
  switch (cur)
  {
  // TODO: finish me. You need to consider EQ, NE, LT, LE, GT, GE
  case '(':
    advance();
    return Token(TokenType::L_PAREN, "(", line);
  case ')':
    advance();
    return Token(TokenType::R_PAREN, ")", line);
  case '{':
    advance();
    return Token(TokenType::L_BRACE, "{", line);
  case '}':
    advance();
    return Token(TokenType::R_BRACE, "}", line);
  case '[':
    advance();
    return Token(TokenType::L_BRACKET, "[", line);
  case ']':
    advance();
    return Token(TokenType::R_BRACKET, "]", line);
  case ',':
    advance();
    return Token(TokenType::COMMA, ",", line);
  case ';':
    advance();
    return Token(TokenType::SEMI, ";", line);
  case '+':
    advance();
    return Token(TokenType::PLUS, "+", line);
  case '-':
    advance();
    return Token(TokenType::MINUS, "-", line);
  case '*':
    advance();
    return Token(TokenType::MUL, "*", line);
  case '/':
    advance();
    return Token(TokenType::DIV, "/", line);
  case '.':
    advance();
    return Token(TokenType::DOT, ".", line);
  default:
    char ch = static_cast<char>(peek);
    std::string s(1, ch);
    advance();
    return Token(TokenType::UNKNOWN, s, line);
  }
}

Token DragonLexer::WS()
{
  // The WS() method should consume all whitespace characters (spaces, tabs, newlines)
  advance();
  return Token(TokenType::WS, " ");
}

Token DragonLexer::ID()
{
  // The ID() method should consume an identifier or keyword.

  // If isn't start with a LETTER, just in case.
  if (!isalpha(peek))
  {
    char ch = static_cast<char>(peek);
    advance();
    return Token(TokenType::UNKNOWN, std::string(1, ch), line);
  }

  std::string str;
  // Start with a LETTER
  str += static_cast<char>(peek);
  advance();

  // Followed by LETTER or DIGIT until it isn't
  while (isalpha(peek) || isdigit(peek))
  {
    str += static_cast<char>(peek);
    advance();
  }
  Token tmp = kwTable.getKeyword(str);
  return (Token(tmp.type, str, line));
}

Token DragonLexer::NUMBER()
{
  // The NUMBER() method should consume an integer, real number, or scientific notation number.
}
