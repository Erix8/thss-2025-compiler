#include "KeywordTable.hpp"

KeywordTable::KeywordTable()
{
  table.emplace("if", Token(TokenType::IF, "if", 0));
  table.emplace("else", Token(TokenType::ELSE, "else", 0));
  // table.emplace("int", Token(TokenType::INT, "int", 0)); // keyword int
}

Token KeywordTable::getKeyword(const std::string &s) const
{
  auto it = table.find(s);
  if (it == table.end())
    return Token(TokenType::ID, s, 0);
  return it->second;
}
