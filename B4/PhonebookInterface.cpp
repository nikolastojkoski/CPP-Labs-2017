#include "PhonebookInterface.hpp"

#include <iostream>
#include <sstream>
#include <string>

std::string formatName(const std::string &name)
{
  if(name.empty())
  {
    return name;
  }
  if((name.front() != '\"') || (name.back() != '\"'))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string formatted;
  for(size_t i = 1; i < name.size() - 1; i++)
  {
    if(name[i] != '\\')
    {
      formatted.push_back(name[i]);
    }
  }
  return formatted;
}
std::string readNumber(std::stringstream &in)
{
  std::string number;
  in >> number;

  for(auto it = number.begin(); it != number.end(); it++)
  {
    if(!isdigit(*it))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  return number;
}
std::string readName(std::stringstream &in)
{
  in.ignore();
  std::string name;
  std::getline(in, name);
  return formatName(name);
}
std::string readMarkName(std::stringstream &in)
{
  std::string markName;
  in >> markName;
  for(auto it = markName.begin(); it != markName.end(); it++)
  {
    if((!isalnum(*it)) && (*it != '-'))
    {
      throw std::invalid_argument("<INVALID BOOKMARK>");
    }
  }
  return markName;
}
void executeCommand(const std::string &line, std::ostream &out, Phonebook &phonebook)
{
  std::stringstream stream(line);

  std::string command;
  stream >> command;

  if(command == "add")
  {
    std::string number = readNumber(stream);
    std::string name = readName(stream);
    phonebook.addEntry(PhonebookEntry{ number, name });
  }
  else if(command == "store")
  {
    std::string oldMarkName = readMarkName(stream);
    std::string newMarkName = readMarkName(stream);
    phonebook.addBookmark(oldMarkName, newMarkName);
  }
  else if(command == "insert")
  {
    std::string place;
    stream >> place;

    if((place != "before") && (place != "after"))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    std::string markName = readMarkName(stream);
    std::string number = readNumber(stream);
    std::string name = readName(stream);

    if(place == "after")
    {
      phonebook.insertAfter(markName, PhonebookEntry{ number,name });
    }
    else
    {
      phonebook.insertBefore(markName, PhonebookEntry{ number,name });
    }
  }
  else if(command == "delete")
  {
    std::string markName = readMarkName(stream);
    phonebook.deleteEntry(markName);
  }
  else if(command == "show")
  {
    std::string markName = readMarkName(stream);
    phonebook.showEntryName(markName, out);
  }
  else if(command == "move")
  {
    std::string markName = readMarkName(stream);
    std::string steps;
    stream >> steps;
    try
    {
      int stepsInt = std::stoi(steps);
      phonebook.moveBoomark(markName, stepsInt);
    }
    catch(const std::invalid_argument&)
    {
      phonebook.moveBoomark(markName, steps);
    }
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}
void openPhonebookInterface(std::istream &in, std::ostream &out)
{
  Phonebook phonebook;
  std::string line;
  while(std::getline(in, line))
  {
    try
    {
      executeCommand(line, out, phonebook);
    }
    catch(const std::invalid_argument &e)
    {
      out << e.what() << std::endl;
    }
  }
}
