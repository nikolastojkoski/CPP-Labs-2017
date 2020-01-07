#include "Rectangle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <stdexcept>

Rectangle::Rectangle(const point_t &center, double width, double height) :
  vertices_{ {center.x - width / 2, center.y + height / 2},
    {center.x + width / 2, center.y + height / 2},
    {center.x + width / 2, center.y - height / 2},
    {center.x - width / 2, center.y - height / 2} }
{
  if(width <= 0 || height <= 0)
  {
    throw std::invalid_argument("Invalid Rectangle parameters!");
  }
}
double Rectangle::getArea() const noexcept
{
  return getDistance(vertices_[0], vertices_[1]) * getDistance(vertices_[1], vertices_[3]);
}
rectangle_t Rectangle::getFrameRect() const noexcept
{
  using namespace std;
  double left = vertices_[0].x;
  double right = vertices_[0].x;
  double top = vertices_[0].y;
  double bot = vertices_[0].y;

  for(size_t i = 1; i < 4; i++)
  {
    left = min(left, vertices_[i].x);
    right = max(right, vertices_[i].x);
    bot = min(bot, vertices_[i].y);
    top = max(top, vertices_[i].y);
  }
  return rectangle_t{ getCenter(), right - left , top - bot };
}
void Rectangle::move(double dx, double dy) noexcept
{
  for(size_t i = 0; i < 4; i++)
  {
    vertices_[i].x += dx;
    vertices_[i].y += dy;
  }
}
void Rectangle::move(const point_t &p) noexcept
{
  move(p.x - getCenter().x, p.y - getCenter().y);
}
void Rectangle::scale(double k)
{
  if(k <= 0)
  {
    throw std::invalid_argument("Invalid Rectangle scale coefficient!");
  }

  point_t center = getCenter();
  for(size_t i = 0; i < 4; i++)
  {
    vertices_[i].x = center.x + (vertices_[i].x - center.x) * k;
    vertices_[i].y = center.y + (vertices_[i].y - center.y) * k;
  }
}
void Rectangle::rotate(const radians_t &rad) noexcept
{
  point_t center = getCenter();

  for(size_t i = 0; i < 4; i++)
  {
    vertices_[i].rotateAroundCenter(center, rad);
  }
}
void Rectangle::rotate(const degrees_t& deg) noexcept
{
  rotate(radians_t{ (deg.angle * M_PI) / 180 });
}
point_t Rectangle::getCenter() const noexcept
{
  return point_t{ (vertices_[0].x + vertices_[1].x + vertices_[2].x + vertices_[3].x) / 4, 
    (vertices_[0].y + vertices_[1].y + vertices_[2].y + vertices_[3].y) / 4 };
}
double Rectangle::getDistance(const point_t &p1, const point_t &p2) noexcept
{
  return std::sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}
std::unique_ptr<Shape> Rectangle::getCopy() const
{
  return std::unique_ptr<Shape>(new Rectangle(*this));
}
