#include "Circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

Circle::Circle(const point_t center, const double radius) :
  center_(center),
  radius_(radius)
{
  if(radius_ <= 0)
  {
    std::cerr << "Invalid circle parameters! ";
    std::cerr << "Radius can not be <= 0" << std::endl;
  }
}
double Circle::getArea() const
{
  return radius_*radius_*M_PI;
}
rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ center_, radius_ * 2, radius_ * 2 };
}
void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
void Circle::move(const point_t p)
{
  center_ = p;
}
