#ifndef OUTPUTFORMATTING_HPP
#define OUTPUTFORMATTING_HPP

#include <iostream>
#include <list>
#include "phrase.hpp"

void formatAndOutput(std::ostream &out, unsigned int lineWidth, const std::list<phrase_t> &vec);
bool checkCorectness(const std::list<phrase_t> &vec);

#endif
