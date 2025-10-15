#include "Token.hpp"
#include <unordered_map>

std::string tokenTypeToString(TokenType t)
{
  static const std::unordered_map<TokenType, std::string> names = {
      {TokenType::EOF_T, "EOF"},
      {TokenType::WS, "WS"},
      {TokenType::UNKNOWN, "UNKNOWN"},
      {TokenType::IF, "IF"},
      {TokenType::ELSE, "ELSE"},
      {TokenType::ID, "IDENT"},
      {TokenType::INT, "INT"},
      {TokenType::REAL, "REAL"},
      {TokenType::SCI, "SCI"},
      {TokenType::EQ, "EQ"},
      {TokenType::NE, "NE"},
      {TokenType::LT, "LT"},
      {TokenType::LE, "LE"},
      {TokenType::GT, "GT"},
      {TokenType::GE, "GE"},
      {TokenType::L_PAREN, "L_PAREN"},
      {TokenType::R_PAREN, "R_PAREN"},
      {TokenType::L_BRACE, "L_BRACE"},
      {TokenType::R_BRACE, "R_BRACE"},
      {TokenType::L_BRACKET, "L_BRACKET"},
      {TokenType::R_BRACKET, "R_BRACKET"},
      {TokenType::COMMA, "COMMA"},
      {TokenType::SEMI, "SEMI"},
      {TokenType::PLUS, "PLUS"},
      {TokenType::MINUS, "MINUS"},
      {TokenType::MUL, "MUL"},
      {TokenType::DIV, "DIV"},
      {TokenType::DOT, "DOT"},
      // TODO: add more token types
      {TokenType::SQUOTE, "SQUOTE"}};
  auto it = names.find(t);
  if (it != names.end())
    return it->second;
  return "UNK";
}
