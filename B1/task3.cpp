#include "declarations.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>

void executeTask3(int args, char*[])
{
  if(args != 2)
  {
    throw std::invalid_argument("Incorrect arguments for task 3");
  }

  std::vector<int> vec;
  int temp;
  while(std::cin >> temp)
  {
    vec.push_back(temp);
  }
  if(std::cin.fail() && !std::cin.eof())
  {
    throw std::invalid_argument("Incorrect input - expected integer type");
  }
  if(!vec.empty())
  {
    if(vec.back() != 0)
    {
      throw std::invalid_argument("Incorrect input - expected zero before end of input");
    }
    else
    {
      vec.pop_back();
    }
  }

  if(!vec.empty())
  {
    int lastNum = vec.back();
    if(lastNum == 1)
    {
      int numEven = 0;
      for(auto i = vec.begin(); i != vec.end(); i++)
      {
        if(*i % 2 == 0)
        {
          std::swap(*i, *std::prev(i, numEven));
          numEven++;
        }
        else if(numEven > 0)
        {
          std::swap(*i, *std::prev(i, numEven));
        }
      }
      vec.erase(std::prev(vec.end(), numEven), vec.end());
    }
    else if(lastNum == 2)
    {
      int numOnes = 0;
      for(auto i = vec.begin(); i != vec.end(); i++)
      {
        if(*i % 3 == 0)
        {
          numOnes += 3;
        }
      }

      if(numOnes > 0)
      {
        vec.resize(vec.size() + numOnes, 1);

        for(auto i = std::next(vec.rbegin(), numOnes); i != vec.rend(); i++)
        {
          if(*i % 3 == 0)
          {
            numOnes -= 3;
          }
          std::swap(*i, *std::prev(i, numOnes));
        }
      }
    }
    detail::printContainer(vec);
  }
}
