#include <iostream>
#include <string>
#include "QueueWithPriority.hpp"
#include "Options.hpp"

int main(int args, char *argv[])
{
  if(args != 2)
  {
    std::cerr << "Incorrect number of parameters";
    return 1;
  }

  try
  {
    switch(std::stoi(argv[1]))
    {
    case 1:
      executeOption1();
      break;
    case 2:
      executeOption2();
      break;
    default:
      std::cerr << "Invalid parameters";
      return 1;
    }
  }
  catch(const std::invalid_argument &e)
  {
    std::cerr << e.what();
    return 1;
  }
  catch(const std::out_of_range &e)
  {
    std::cerr << e.what();
    return 1;
  }



  return 0;
}
