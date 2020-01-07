#ifndef FACTORIALCONTAINER_HPP
#define FACTIORIALCONTAINER_HPP

#include <iterator>

class FactorialContainer
{
public:
  class iterator;
  FactorialContainer() = default;
  iterator begin();
  iterator end();
};

class FactorialContainer::iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
{
public:
  iterator(unsigned int value, unsigned int index);
  iterator(const iterator &other) = default;

  iterator& operator=(const iterator &other) = default;
  iterator& operator++();
  iterator operator++(int);
  iterator& operator--();
  iterator operator--(int);

  bool operator==(const iterator &other) const;
  bool operator!=(const iterator &other) const;

  const unsigned int& operator*() const;
  const unsigned int* operator->() const;
private:
  unsigned int value_;
  unsigned int index_;
};

#endif
