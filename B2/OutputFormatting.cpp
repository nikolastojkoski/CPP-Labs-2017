#include "OutputFormatting.hpp"
#include <list>

void printLine(std::ostream &out, const std::list<phrase_t> &line)
{
  for(auto it = line.begin(); it != line.end(); it++)
  {
    out << (*it).value;
  }
  out << "\n";
}
int reformatAndPrint(std::ostream &out, std::list<phrase_t> &line)
{
  std::size_t width = 0;
  std::list<phrase_t>newLine;
  while(!line.empty())
  {
    newLine.push_front(line.back());
    width += line.back().value.size();
    line.pop_back();
    if(newLine.front().type == phrase_t::WORD || newLine.front().type == phrase_t::NUMB)
    {
      break;
    }
  }
  printLine(out, line);
  line = newLine;
  return width;
}
void formatAndOutput(std::ostream &out, unsigned int lineWidth, const std::list<phrase_t> &vec)
{
  std::size_t currentWidth = 0;
  std::list<phrase_t> line;
  for(auto it = vec.begin(); it != vec.end(); it++)
  {
    switch((*it).type)
    {
    case phrase_t::PUNCT:
      if(currentWidth + 1 > lineWidth)
      {
        currentWidth = reformatAndPrint(out, line);
      }
      line.push_back(*it);
      currentWidth += (*it).value.size();
      break;
    case phrase_t::DASH:
      if(currentWidth + 4 > lineWidth)
      {
        currentWidth = reformatAndPrint(out, line);
      }
      line.push_back(phrase_t{ " ", phrase_t::WHITESPACE });
      line.push_back(*it);
      currentWidth += (*it).value.size() + 1;
      break;
    case phrase_t::WORD:
    case phrase_t::NUMB:
      if(currentWidth + (*it).value.size() + 1 > lineWidth)
      {
        printLine(out, line);
        line.clear();
        currentWidth = 0;
      }
      else if(!line.empty())
      {
        line.push_back(phrase_t{ " ", phrase_t::WHITESPACE });
        currentWidth++;
      }
      line.push_back(*it);
      currentWidth += (*it).value.size();
      break;
    case phrase_t::WHITESPACE:
      break;
    }

  }
  if(!line.empty())
  {
    printLine(out, line);
  }
}

bool checkCorectness(const std::list<phrase_t> &vec)
{
  if(!vec.empty() && (vec.front().type != phrase_t::WORD) && (vec.front().type != phrase_t::NUMB))
  {
    return false;
  }
  for(auto it = vec.begin(); it != vec.end(); it++)
  {
    switch((*it).type)
    {
    case phrase_t::WORD:
    case phrase_t::NUMB:
      if((*it).value.size() > 20)
      {
        return false;
      }
      break;
    case phrase_t::DASH:
      if((*it).value.size() != 3)
      {
        return false;
      }
      if(it != vec.begin())
      {
        const phrase_t &prev = *std::prev(it);
        if((prev.type == phrase_t::DASH) || ((prev.type == phrase_t::PUNCT) && (prev.value != ",")))
        {
          return false;
        }
      }
      break;
    case phrase_t::PUNCT:
      if(it != vec.begin())
      {
        const phrase_t &prev = *std::prev(it);
        if((prev.type == phrase_t::DASH) || (prev.type == phrase_t::PUNCT))
        {
          return false;
        }
      }
      break;
    case phrase_t::WHITESPACE:
      break;
    }
  }
  return true;
}
