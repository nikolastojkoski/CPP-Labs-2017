#include "declarations.hpp"
#include <iostream>
#include <vector>
#include <forward_list>
#include <stdexcept>
#include <string>

detail::sortType_t getSortType(const std::string &param)
{
  if(param == "ascending")
  {
    return detail::sortType_t::ascending;
  }
  else if(param == "descending")
  {
    return detail::sortType_t::descending;
  }
  else
  {
    throw std::invalid_argument("Incorrect sort type parameter");
  }
}

void executeTask1(int args, char *argv[])
{
  if(args != 3)
  {
    throw std::invalid_argument("Incorrect arguments for task 1");
  }

  detail::sortType_t type = getSortType(argv[2]);

  std::forward_list<int>list1;
  int nextNum;
  while(std::cin >> nextNum)
  {
    list1.push_front(nextNum);
  }
  if(std::cin.fail() && !std::cin.eof())
  {
    throw std::invalid_argument("Incorrect input - expected integer type");
  }
  std::vector<int>vec1(list1.begin(), list1.end());
  std::vector<int>vec2(list1.begin(), list1.end());

  detail::sort<detail::bracketAccess>(vec1, type);
  detail::printContainer(vec1);

  detail::sort<detail::atAccess>(vec2, type);
  detail::printContainer(vec2);

  detail::sort<detail::iteratorAccess>(list1, type);
  detail::printContainer(list1);
}
