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

  // TODO:You need to consider when to call ID()
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
  case '=':
    advance();
    return Token(TokenType::EQ, "=", line);
  case '<':
  {
    int startPos = pos;
    advance(); // consume '<'
    if (peek == '>')
    {
      advance(); // consume '>'
      return Token(TokenType::NE, "<>", line);
    }
    else if (peek == '=')
    {
      advance(); // comsume '='
      return Token(TokenType::LE, "<=", line);
    }
    else
    {
      // reset pos to '<' and re-comsume '<'
      resetPos(startPos);
      advance();
      return Token(TokenType::LT, "<", line);
    }
  }
  case '>':
  {
    int startPos = pos;
    advance(); // consume '>'
    if (peek == '=')
    {
      advance(); // consume '='
      return Token(TokenType::GE, ">=", line);
    }
    else
    {
      // reset pos to '>' and re-consume '>'
      resetPos(startPos);
      advance();
      return Token(TokenType::GT, ">", line);
    }
  }
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
  case '\'':
    advance();
    return Token(TokenType::SQUOTE, "\'", line);
  default:
    char ch = static_cast<char>(peek);
    std::string s(1, ch);
    advance();
    return Token(TokenType::UNKNOWN, s, line);
  }
}

Token DragonLexer::WS()
{
  // TODO:The WS() method should consume all whitespace characters (spaces, tabs, newlines)
  // consume all the whitespaces at once
  std::string wsStr;
  while (peek != EOF_CHAR && std::isspace(static_cast<char>(peek)))
  {
    wsStr += static_cast<char>(peek);
    advance();
  }
  return Token(TokenType::WS, wsStr, line);
}

Token DragonLexer::ID()
{
  // TODO:The ID() method should consume an identifier or keyword.

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
  // TODO:The NUMBER() method should consume an integer,
  // real number, or scientific notation number.

  // If isn't start with digit, just in case
  if (!std::isdigit(static_cast<char>(peek)))
  {
    char ch = static_cast<char>(peek);
    advance();
    return Token(TokenType::UNKNOWN, std::string(1, ch), line);
  }

  std::string numStr;
  bool hasDot = false;
  bool hasExp = false;

  // Collect continuous digits
  while (peek != EOF_CHAR)
  {
    char c = static_cast<char>(peek);
    if (std::isdigit(c))
    {
      numStr += c;
      advance();
    }
    else if (c == '\'') // \' can be between digits
    {
      int startPos = pos;
      advance();
      // \' must followed by digits
      if (peek == EOF_CHAR || !std::isdigit(static_cast<char>(peek)))
      {
        resetPos(startPos);
        break;
      }
      else
      {
        numStr += '\'';
      }
    }
    else
    {
      break;
    }
  }

  // Check REAL
  if (peek == '.' && !hasDot && !hasExp)
  {
    int dotPos = pos;
    std::string tempStr = numStr;
    tempStr += static_cast<char>(peek);
    advance();
    hasDot = true;

    bool hasFractionDigits = false;
    // Check digit after '.'
    if (peek != EOF_CHAR && std::isdigit(static_cast<char>(peek)))
    {
      // collect digits after '.'
      while (peek != EOF_CHAR)
      {
        char c = static_cast<char>(peek);
        if (std::isdigit(c))
        {
          tempStr += c;
          advance();
          hasFractionDigits = true;
        }
        else if (c == '\'')
        {
          int startPos = pos;
          advance();
          if (peek == EOF_CHAR || !std::isdigit(static_cast<char>(peek)))
          {
            resetPos(startPos);
            break;
          }
          else
          {
            tempStr += '\'';
          }
        }
        else
        {
          break;
        }
      }
    }

    if (hasFractionDigits)
    {
      numStr = tempStr;
    }
    else
    {
      resetPos(dotPos);
      hasDot = false;
    }
  }

  // Check SCI
  if ((peek == 'e' || peek == 'E') && !hasExp)
  {
    numStr += static_cast<char>(peek);
    advance();
    hasExp = true;

    // Check +/- after eE
    if (peek == '+' || peek == '-')
    {
      numStr += static_cast<char>(peek);
      advance();
    }

    // Collect digits in exp
    bool hasExpDigits = false;
    while (peek != EOF_CHAR)
    {
      char c = static_cast<char>(peek);
      if (std::isdigit(c))
      {
        numStr += c;
        advance();
        hasExpDigits = true;
      }
      else if (c == '\'')
      {
        int startPos = pos;
        advance();
        // \' must followed by digits
        if (peek == EOF_CHAR || !std::isdigit(static_cast<char>(peek)))
        {
          resetPos(startPos);
          break;
        }
        else
        {
          numStr += '\'';
        }
      }
      else
      {
        break;
      }
    }

    // If no digits in exp, then not SCI
    if (!hasExpDigits)
    {
      // reset pos to e/E
      int expStart = numStr.find_last_of("eE");
      resetPos(pos - (numStr.length() - expStart));
      numStr = numStr.substr(0, expStart);
      hasExp = false;
    }
  }
  if (hasExp)
  {
    return Token(TokenType::SCI, numStr, line);
  }
  else if (hasDot)
  {
    return Token(TokenType::REAL, numStr, line);
  }
  else
  {
    return Token(TokenType::INT, numStr, line);
  }
}
