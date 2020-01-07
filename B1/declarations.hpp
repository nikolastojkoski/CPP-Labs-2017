#ifndef DECL_HPP
#define DECL_HPP
#include <iostream>
#include <vector>
#include <forward_list>
#include <functional>

namespace detail
{
  enum sortType_t { ascending, descending };

  template<typename C>
  struct bracketAccess
  {
    typedef std::size_t indexType;
    static typename C::value_type& getElement(C &cont, size_t index)
    {
      return cont[index];
    }
    static size_t getBegin(const C &)
    {
      return 0;
    }
    static size_t getEnd(const C &cont)
    {
      return cont.size();
    }
    static size_t getNextIndex(size_t cur)
    {
      return cur + 1;
    }
  };
  template<typename C>
  struct atAccess
  {
    typedef std::size_t indexType;
    static typename C::value_type& getElement(C &cont, size_t index)
    {
      return cont.at(index);
    }
    static size_t getBegin(const C &)
    {
      return 0;
    }
    static size_t getEnd(const C &cont)
    {
      return cont.size();
    }
    static size_t getNextIndex(size_t cur)
    {
      return cur + 1;
    }
  };
  template<typename C>
  struct iteratorAccess
  {
    typedef typename C::iterator indexType;
    static typename C::value_type& getElement(C &, typename C::iterator &it)
    {
      return *it;
    }
    static typename C::iterator getBegin(C &cont)
    {
      return cont.begin();
    }
    static typename C::iterator getEnd(C &cont)
    {
      return cont.end();
    }
    static typename C::iterator getNextIndex(typename C::iterator &it)
    {
      return std::next(it);
    }
  };

  template<template<class C> class Traits, typename C>
  void sort(C &container, sortType_t type)
  {
    std::function<bool(typename C::value_type, typename C::value_type)> comp;
    if(type == ascending)
    {
      comp = std::greater<typename C::value_type>();
    }
    else
    {
      comp = std::less<typename C::value_type>();
    }

    using indexType = typename Traits<C>::indexType;
    const indexType containerEnd = Traits<C>::getEnd(container);
    for(indexType i = Traits<C>::getBegin(container); i != containerEnd; i++)
    {
      for(indexType j = Traits<C>::getNextIndex(i); j != containerEnd; j++)
      {
        typename C::value_type &a = Traits<C>::getElement(container, i);
        typename C::value_type &b = Traits<C>::getElement(container, j);
        if(comp(a, b))
        {
          std::swap(a, b);
        }
      }
    }
  }

  template<typename T>
  void printContainer(const T &v)
  {
    for(typename T::const_iterator it = v.cbegin(); it != v.cend(); it++)
    {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }

}

detail::sortType_t getSortType(const std::string &param);

void executeTask1(int args, char *argv[]);
void executeTask2(int args, char *argv[]);
void executeTask3(int args, char *argv[]);
void executeTask4(int args, char *argv[]);

#endif
