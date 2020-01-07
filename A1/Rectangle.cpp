#include "Rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t center, const double width, const double height) :
  rect_({ center, width, height })
{
  if(width <= 0 || height <= 0)
  {
    std::cerr << "Invalid Rectangle parameters! ";
    std::cerr << "Width and height need to be greather than zero" << std::endl;
  }
}
double Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}
rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}
void Rectangle::move(const double dx, const double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}
void Rectangle::move(const point_t p)
{
  rect_.pos = p;
}
