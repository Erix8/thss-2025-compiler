#include "Lexer.hpp"

Lexer::Lexer(const std::string &input)
    : input(input), pos(0), peek(0), line(1)
{
  if (input.empty())
  {
    peek = EOF_CHAR;
  }
  else
  {
    peek = static_cast<unsigned char>(input[0]);
  }
}

void Lexer::advance()
{
  // TODO:The advance() method moves the pointer 'pos' forward by one position.
  // When the end of the string is reached, set 'peek' to EOF_CHAR.
  // You should use static_cast<unsigned char> to ensure 'peek' stores an unsigned char value.

  if (peek == '\n')
  {
    ++line; // when at end of the line, update line number
  }
  ++pos; // move pos forward by one
  if (pos >= input.length())
  {
    peek = EOF_CHAR; // when at end of input, update peek as EOF_CHAR
  }
  else
  {
    peek = static_cast<unsigned char>(input[pos]); // else update peek as next char
  }
}

void Lexer::resetPos(int newPos)
{
  // TODO:The resetPos(int newPos) method resets 'pos' to newPos
  // and updates 'peek' accordingly.

  int len = input.length();

  if (newPos < 0)
  {
    newPos = 0;
  }
  else if (newPos > len)
  {
    newPos = len;
  }

  pos = newPos;

  if (newPos < len)
  {
    peek = static_cast<unsigned char>(input[newPos]);
  }
  else
  {
    peek = EOF_CHAR;
  }
}
