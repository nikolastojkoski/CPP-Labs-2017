#include "InputParser.hpp"
#include <locale>

InputParser::InputParser(std::istream &in) :
  in_(in)
{
}
void InputParser::parseInput()
{
  while(in_)
  {
    readPhrase();
  }
}
void InputParser::readPhrase()
{
  char c = in_.get();
  while(std::isspace(c, std::locale()))
  {
    c = in_.get();
  }

  if(isalpha(c, std::locale()))
  {
    in_.unget();
    readWord();
  }
  else if(c == '-')
  {
    if(in_.peek() == '-')
    {
      in_.unget();
      readDash();
    }
    else
    {
      in_.unget();
      readNumber();
    }
  }
  else if((c == '+') || (isdigit(c, std::locale())))
  {
    in_.unget();
    readNumber();
  }
  else if(ispunct(c, std::locale()))
  {
    phrase_t phrase{ "", phrase_t::PUNCT };
    phrase.value.push_back(c);
    text_.push_back(phrase);
  }
}
void InputParser::readWord()
{
  phrase_t phrase{ "", phrase_t::WORD };
  do
  {
    char c = in_.get(); 
    phrase.value.push_back(c);
    if(c == '-' && in_.peek() == '-')
    {
      phrase.value.pop_back(); 
      in_.unget();
      break;
    }
  } while((std::isalpha<char>(in_.peek(), std::locale())) || (in_.peek() == '-'));
  text_.push_back(phrase);
}
void InputParser::readNumber()
{
  phrase_t phrase{ "", phrase_t::NUMB };

  char decimalPoint = std::use_facet<std::numpunct<char>>(std::locale()).decimal_point();
  bool decimalPointRead = false;
  do
  {
    char c = in_.get();
    if(c == decimalPoint)
    {
      if(decimalPointRead)
      {
        in_.unget();
        break;
      }
      decimalPointRead = true;
    }
    phrase.value.push_back(c);
  } while((std::isdigit<char>(in_.peek(), std::locale()) || (in_.peek() == decimalPoint)));

  text_.push_back(phrase);
}

void InputParser::readDash()
{
  phrase_t phrase{ "", phrase_t::DASH };
  while(in_.peek() == '-')
  {
    char c = in_.get();
    phrase.value.push_back(c);
  }
  text_.push_back(phrase);
}
std::list<phrase_t>::iterator InputParser::begin()
{
  return text_.begin();
}
std::list<phrase_t>::iterator InputParser::end()
{
  return text_.end();
}
