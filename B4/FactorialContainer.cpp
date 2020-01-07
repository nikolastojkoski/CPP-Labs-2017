#include "FactorialContainer.hpp"

FactorialContainer::iterator FactorialContainer::begin()
{
  return FactorialContainer::iterator(1, 1);
}
FactorialContainer::iterator FactorialContainer::end()
{
  return FactorialContainer::iterator(39916800, 11);
}
FactorialContainer::iterator::iterator(unsigned int value, unsigned int index)
{
  value_ = value;
  index_ = index;
}
FactorialContainer::iterator& FactorialContainer::iterator::operator++()
{
  if(index_ < 11)
  {
    index_ ++;
    value_ *= index_;
  }
  return *this;
}
FactorialContainer::iterator FactorialContainer::iterator::operator++(int)
{
  iterator old = *this;
  if(index_ < 11)
  {
    index_++;
    value_ *= index_;
  }
  return old;
}
FactorialContainer::iterator& FactorialContainer::iterator::operator--()
{
  if(index_ > 1)
  {
    value_ /= index_;
    index_--;
  }
  return *this;
}
FactorialContainer::iterator FactorialContainer::iterator::operator--(int)
{
  iterator old = *this;
  if(index_ > 1)
  {
    value_ /= index_;
    index_--;
  }
  return old;
}
bool FactorialContainer::iterator::operator==(const iterator &other) const
{
  return (index_ == other.index_);
}
bool FactorialContainer::iterator::operator!=(const iterator &other) const
{
  return (index_ != other.index_);
}
const unsigned int& FactorialContainer::iterator::operator*() const
{
  return value_;
}
const unsigned int* FactorialContainer::iterator::operator->() const
{
  return &value_;
}
