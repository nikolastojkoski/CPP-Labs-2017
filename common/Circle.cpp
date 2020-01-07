#include "Circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

Circle::Circle(const point_t &center, double radius) :
  center_(center),
  radius_(radius)
{
  if(radius_ <= 0)
  {
    throw std::invalid_argument("Invalid circle parameters!");
  }
}
double Circle::getArea() const noexcept
{
  return radius_*radius_*M_PI;
}
rectangle_t Circle::getFrameRect() const noexcept
{
  return rectangle_t{ center_, radius_ * 2, radius_ * 2 };
}
void Circle::move(double dx, double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}
void Circle::move(const point_t &p) noexcept
{
  center_ = p;
}
void Circle::scale(double k)
{
  if(k <= 0)
  {
    throw std::invalid_argument("Invalid Circle scale coefficient!");
  }
  radius_ *= k;
}
void Circle::rotate(const degrees_t&) noexcept
{
}
void Circle::rotate(const radians_t&) noexcept
{
}
std::unique_ptr<Shape> Circle::getCopy() const
{
  return std::unique_ptr<Shape>(new Circle({ center_.x, center_.y }, radius_));
}
