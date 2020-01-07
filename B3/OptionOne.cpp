#include "Options.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include "QueueWithPriority.hpp"

void executeOption1()
{
  detail::QueueWithPriority<std::string> queue;

  std::string line;
  while(std::getline(std::cin, line))
  {
    std::stringstream stream(line);
    std::string command;
    stream >> command;

    if(command == "add")
    {
      std::string priority;
      stream >> priority;

      std::string data;
      stream.ignore();
      std::getline(stream, data);

      if(data.empty())
      {
        std::cout << "<INVALID COMMAND>" << std::endl;
      }
      else if(priority == "high")
      {
        queue.PutElementToQueue(data, ElementPriority::HIGH);
      }
      else if(priority == "normal")
      {
        queue.PutElementToQueue(data, ElementPriority::NORMAL);
      }
      else if(priority == "low")
      {
        queue.PutElementToQueue(data, ElementPriority::LOW);
      }
      else
      {
        std::cout << "<INVALID COMMAND>" << std::endl;
      }
    }
    else if(command == "accelerate" && stream.eof())
    {
      queue.Accelerate();
    }
    else if(command == "get" && stream.eof())
    {
      if(queue.empty())
      {
        std::cout << "<EMPTY>" << std::endl;
      }
      else
      {
        std::cout << queue.GetElementFromQueue() << std::endl;
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
    }

    if(std::cin.eof())
    {
      break;
    }
  }


}
