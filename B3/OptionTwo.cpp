#include "Options.hpp"

#include <iostream>
#include <list>

void executeOption2()
{
  std::list<int> list;

  int nextNum;
  while(std::cin >> nextNum)
  {
    if((nextNum < 1) || (nextNum > 20))
    {
      throw std::out_of_range("Value not in range");
    }
    list.push_back(nextNum);
  }
  if(std::cin.fail() && !std::cin.eof())
  {
    throw std::invalid_argument("incorrect input");
  }
  if(list.size() > 20)
  {
    throw std::invalid_argument("too many elements");
  }

  auto i = list.begin();
  auto j = std::prev(list.end());

  if(list.size() == 1)
  {
    std::cout << *i << std::endl;
  }
  else
  {
    while(i != j)
    {
      std::cout << *i << " " << *j << " ";
      i++;
      if(i == j)
      {
        break;
      }
      j--;
    }
    if(list.size() % 2 == 1)
    {
      std::cout << *i;
    }
    std::cout << std::endl;
  }

}
