#include <iostream>
#include "PhonebookInterface.hpp"
#include "Factorials.hpp"

int main(int args, char *argv[])
{
  if(args != 2)
  {
    std::cerr << "Invalid number of arguments";
    return 1;
  }

  try
  {
    int option = std::stoi(argv[1]);
    switch(option)
    {
    case 1:
      openPhonebookInterface(std::cin, std::cout);
      break;
    case 2:
      calculateFactorials(std::cout);
      break;
    default:
      std::cerr << "Invalid argument";
      return 1;
    }
  }
  catch(const std::invalid_argument &e)
  {
    std::cerr << e.what();
    return 1;
  }

}
