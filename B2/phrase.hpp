#ifndef PHRASE_HPP
#define PHRASE_HPP

#include <string>

struct phrase_t
{
  enum type_t
  {
    WORD,
    NUMB,
    PUNCT,
    DASH,
    WHITESPACE
  };
  std::string value;
  type_t type;
};

#endif
