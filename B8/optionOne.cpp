#include "options.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <list>
#define _USE_MATH_DEFINES
#include <math.h>

class MultiplyBy
{
public:
  MultiplyBy(double k) : k_(k) {}
  void operator() (double &num) { num *= k_; }
private:
  double k_;
};

void optionOne(std::istream &in, std::ostream &out)
{
  std::list<double> numList;
  std::copy(std::istream_iterator<double>(in), std::istream_iterator<double>(), 
    std::back_inserter(numList));

  if(!in.eof())
  {
    throw std::invalid_argument("Invalid input");
  }

  std::for_each(numList.begin(), numList.end(), MultiplyBy(M_PI));

  std::copy(numList.begin(), numList.end(), std::ostream_iterator<double>(out, " "));
}
