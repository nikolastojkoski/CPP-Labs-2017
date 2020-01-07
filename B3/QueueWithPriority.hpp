#ifndef QUEUEWITHPRIO_HPP
#define QUEUEWITHPRIO_HPP

#include <list>
#include <stdexcept>

typedef enum
{
  LOW,
  NORMAL,
  HIGH
} ElementPriority;

namespace detail
{
  template<typename T>
  class QueueWithPriority
  {
  public:
    QueueWithPriority()
    {
      T dummyElement;
      highSeperator = queue_.insert(queue_.end(), dummyElement);
      normalSeperator = queue_.insert(queue_.end(), dummyElement);
    }
    virtual ~QueueWithPriority() = default;

    void PutElementToQueue(const T &element, ElementPriority priority)
    {
      switch(priority)
      {
      case ElementPriority::HIGH:
        queue_.insert(highSeperator, element);
        break;
      case ElementPriority::NORMAL:
        queue_.insert(normalSeperator, element);
        break;
      case ElementPriority::LOW:
        queue_.insert(queue_.end(), element);
        break;
      }
    }
    T GetElementFromQueue()
    {
      if(empty())
      {
        throw std::invalid_argument("Queue is empty!");
      }
      if(queue_.begin() != highSeperator)
      {
        T frontElem = queue_.front();
        queue_.pop_front();
        return frontElem;
      }
      else if(std::next(highSeperator) != normalSeperator)
      {
        T frontElem = *std::next(highSeperator);
        queue_.erase(std::next(highSeperator));
        return frontElem;
      }
      else
      {
        T frontElem = *std::next(normalSeperator);
        queue_.erase(std::next(normalSeperator));
        return frontElem;
      }
    }
    void Accelerate()
    {
      auto it = std::next(normalSeperator);
      while(it != queue_.end())
      {
        queue_.insert(highSeperator, *it);
        it++;
        queue_.erase(std::prev(it));
      }
    }
    bool empty() const
    {
      if((queue_.begin() == highSeperator) && (std::next(highSeperator) == normalSeperator)
        && (std::next(normalSeperator) == queue_.end()))
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  private:
    std::list<T> queue_;
    typename std::list<T>::iterator highSeperator, normalSeperator;
  };

}

#endif
