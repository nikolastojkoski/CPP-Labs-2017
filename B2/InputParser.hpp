#ifndef INPUTPARSER_HPP
#define INPUTPARSER_HPP

#include <iostream>
#include <list>
#include <memory>
#include "phrase.hpp"

class InputParser
{
public:
  InputParser(std::istream &in);
  void parseInput();
  std::list<phrase_t>::iterator begin();
  std::list<phrase_t>::iterator end();

private:
  std::istream & in_;
  std::list<phrase_t> text_;

  void readPhrase();
  void readWord();
  void readNumber();
  void readDash();
};


#endif
