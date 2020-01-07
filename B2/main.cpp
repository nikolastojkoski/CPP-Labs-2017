#include <iostream>
#include "InputParser.hpp"
#include "OutputFormatting.hpp"

int main(int args, char * argv[])
{
  int lineWidth = 40;

  if(args > 1)
  {
    if(args != 3)
    {
      std::cerr << "Invalid number of arguments";
      return 1;
    }
    else if(std::string(argv[1]) != "--line-width")
    {
      std::cerr << "Invalid arguments";
      return 1;
    }
    else
    {
      lineWidth = std::stoi(argv[2]);
      if(lineWidth < 24)
      {
        std::cerr << "Invalid line width";
        return 1;
      }
    }
  }

  try
  {
    InputParser parser(std::cin);
    parser.parseInput();

    std::list<phrase_t> vec(parser.begin(), parser.end());
    if(!checkCorectness(vec))
    {
      std::cerr << "Invalid input";
      return 1;
    }
    formatAndOutput(std::cout, lineWidth, vec);
  }
  catch(const std::invalid_argument &e)
  {
    std::cerr << e.what();
    return 1;
  }

  return 0;
}
