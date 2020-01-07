#include "declarations.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

void fillRandom(double * array, int size)
{
  std::mt19937 rng(std::random_device{}());
  std::uniform_real_distribution<double> dist(-1.0, 1.0);
  for(int i = 0; i < size; i++)
  {
    array[i] = dist(rng);
  }
}
void executeTask4(int args, char *argv[])
{
  if(args != 4)
  {
    throw std::invalid_argument("Incorrect arguments for task 4");
  }

  detail::sortType_t type = getSortType(argv[2]);

  std::vector<double> vec(std::stoi(argv[3]));
  if(!vec.empty())
  {
    fillRandom(&vec[0], vec.size());

    detail::printContainer(vec);

   detail::sort<detail::bracketAccess>(vec, type);


    detail::printContainer(vec);
  }
}
