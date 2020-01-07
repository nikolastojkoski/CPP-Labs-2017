#include <vector>
#include <iostream>
#include <fstream>
#include "declarations.hpp"
#include <memory>
#include <stdexcept>

void executeTask2(int args, char *argv[])
{
  if(args != 3)
  {
    throw std::invalid_argument("Incorrect arguments for task 2");
  }

  std::ifstream inp(argv[2], std::ios_base::binary);
 
  if(!inp.good())
  {
    throw std::invalid_argument("Incorrect filename for task 2");
  }
  
  inp.seekg(0, std::ios_base::end);
  std::streamsize size = inp.tellg();
  inp.seekg(0, std::ios_base::beg);

  std::size_t length = static_cast<size_t>(size);
  std::unique_ptr<char[]> contents(new char[length]);

  inp.read(contents.get(), size);

  if(!inp)
  {
    throw std::ios_base::failure("Error reading file contents, The file might have been modified while trying to extract data.");
  }

  std::vector<char>vec(contents.get(), contents.get() + length);

  for(auto it = vec.begin(); it != vec.end(); it++)
  {
    std::cout << *it;
  }

}
