#include <iostream>
#include <stdexcept>
#include <string>
#include "declarations.hpp"

int main(int args, char *argv[])
{
  if(args < 2)
  {
    std::cerr << "Missing task number argument" << std::endl;
    return 1;
  }

  try
  {
    int variant = std::stoi(argv[1]);
    switch(variant)
    {
    case 1:
      executeTask1(args, argv);
      break;
    case 2:
      executeTask2(args, argv);
      break;
    case 3:
      executeTask3(args, argv);
      break;
    case 4:
      executeTask4(args, argv);
      break;
    default:
      std::cerr << "Invalid task number argument" << std::endl;
      return 1;
    }
  }
  catch(const std::invalid_argument &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch(const std::ios_base::failure &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch(const std::out_of_range &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
