#include "options.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <memory>
#include <sstream>
#include <locale>
#include <list>
#include "Shape.hpp"
#include "Figures.hpp"

class Line : public std::string
{
public:
  bool containsNonSpaceCharacters()
  {
    return (std::find_if(begin(), end(), 
      [](char c) { return !std::isspace(c, std::locale()); }) != end());
  }

  friend std::istream& operator>>(std::istream &in, Line &line)
  {
    while(std::getline(in, line))
    {
      if(!line.empty() && line.containsNonSpaceCharacters())
      {
        break;
      }
    }
    return in;
  }
};

std::unique_ptr<Shape> getShapeFromLine(const Line &line)
{
  std::stringstream stream(line);

  std::string shapeType;
  std::getline(stream, shapeType, '(');

  auto firstChar = std::find_if(shapeType.begin(), shapeType.end(),
    std::bind(std::isalpha<char>, std::placeholders::_1, std::locale()));

  shapeType.erase(shapeType.begin(), firstChar);
  shapeType.erase(std::find_if(firstChar, shapeType.end(),
    std::bind(std::isspace<char>, std::placeholders::_1, std::locale())), shapeType.end());

  double x_, y_;

  stream >> x_;

  stream.ignore(std::numeric_limits<std::streamsize>::max(), ';');
  stream >> y_;

  stream.ignore(std::numeric_limits<std::streamsize>::max(), ')');

  if(stream.fail())
  {
    throw std::invalid_argument("invalid values");
  }

  Line remLine;
  std::getline(stream, remLine);
  if(remLine.containsNonSpaceCharacters())
  {
    throw std::invalid_argument("invalid input");
  }
  
  if(shapeType == "CIRCLE")
  {
    return std::unique_ptr<Shape>(new Circle(x_, y_));
  }
  else if(shapeType == "TRIANGLE")
  {
    return std::unique_ptr<Shape>(new Triangle(x_, y_));
  }
  else if(shapeType == "SQUARE")
  {
    return std::unique_ptr<Shape>(new Square(x_, y_));
  }
  else
  {
    throw std::invalid_argument("Invalid shape type");
  }
}

void optionTwo(std::istream &in, std::ostream &out)
{

  std::list<std::unique_ptr<Shape>> shapeList;

  std::transform(std::istream_iterator<Line>(in), std::istream_iterator<Line>(), 
    std::back_inserter(shapeList), getShapeFromLine);

  out << "Original:" << std::endl;
  std::for_each(shapeList.begin(), shapeList.end(), 
    std::bind(&Shape::draw, std::placeholders::_1, std::ref(out)));

  out << "Left-Right:" << std::endl;
  shapeList.sort(std::bind(&Shape::isMoreLeft,
    std::bind(&std::unique_ptr<Shape>::get, std::placeholders::_1),
    std::bind(&std::unique_ptr<Shape>::get, std::placeholders::_2)));

  std::for_each(shapeList.begin(), shapeList.end(),
    std::bind(&Shape::draw, std::placeholders::_1, std::ref(out)));

  out << "Right-Left:" << std::endl;
  std::for_each(shapeList.rbegin(), shapeList.rend(), 
    std::bind(&Shape::draw, std::placeholders::_1, std::ref(out)));


  out << "Top-Bottom:" << std::endl;
  shapeList.sort(std::bind(&Shape::isUpper,
    std::bind(&std::unique_ptr<Shape>::get, std::placeholders::_1),
    std::bind(&std::unique_ptr<Shape>::get, std::placeholders::_2)));

  std::for_each(shapeList.begin(), shapeList.end(), 
    std::bind(&Shape::draw, std::placeholders::_1, std::ref(out)));

  out << "Bottom-Top:" << std::endl;
  std::for_each(shapeList.rbegin(), shapeList.rend(), 
    std::bind(&Shape::draw, std::placeholders::_1, std::ref(out)));

}
