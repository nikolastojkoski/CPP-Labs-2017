#include "Triangle.hpp"
#include <algorithm>
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>
#include "base-types.hpp"

Triangle::Triangle(const point_t &p1, const point_t &p2, const point_t &p3) :
  a_(p1), 
  b_(p2), 
  c_(p3) 
{
  if(getArea() <= 0)
  {
    throw std::invalid_argument("Invalid triangle parameters!");
  }
}
double Triangle::getArea() const noexcept
{
  double ab = getDistance(a_, b_);
  double ac = getDistance(a_, c_);
  double bc = getDistance(b_, c_);
  double s = (ab + ac + bc) / 2;
  return std::sqrt(s*(s - ab)*(s - ac)*(s - bc));
}
rectangle_t Triangle::getFrameRect() const noexcept
{
  using namespace std;
  double left = min(min(a_.x, b_.x), c_.x);
  double bot = min(min(a_.y, b_.y), c_.y);
  double h = fabs(max(max(a_.y, b_.y), c_.y) - bot);
  double w = fabs(max(max(a_.x, b_.x), c_.x) - left);
  return rectangle_t{ getCenter(), w, h };
}
void Triangle::move(double dx, double dy) noexcept
{
  a_.x += dx;
  b_.x += dx;
  c_.x += dx;
  a_.y += dy;
  b_.y += dy;
  c_.y += dy;
}
void Triangle::move(const point_t &p) noexcept
{
  move(p.x - getCenter().x, p.y - getCenter().y);
}
void Triangle::scale(double k)
{
  if(k <= 0)
  {
    throw std::invalid_argument("Invalid Triangle scale coefficient!");
  }
  point_t center = getCenter();
  a_.x = center.x + (a_.x - center.x) * k;
  a_.y = center.y + (a_.y - center.y) * k;
  b_.x = center.x + (b_.x - center.x) * k;
  b_.y = center.y + (b_.y - center.y) * k;
  c_.x = center.x + (c_.x - center.x) * k;
  c_.y = center.y + (c_.y - center.y) * k;
}
void Triangle::rotate(const radians_t& rad) noexcept
{
  point_t center = getCenter();
  a_.rotateAroundCenter(center, rad);
  b_.rotateAroundCenter(center, rad);
  c_.rotateAroundCenter(center, rad);
}
void Triangle::rotate(const degrees_t& deg) noexcept
{
  rotate(radians_t{ (deg.angle * M_PI) / 180 });
}
point_t Triangle::getCenter() const noexcept
{
  return point_t{ (a_.x + b_.x + c_.x) / 3, (a_.y + b_.y + c_.y) / 3 };
}
double Triangle::getDistance(const point_t &p1, const point_t &p2) noexcept
{
  return std::sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}
std::unique_ptr<Shape> Triangle::getCopy() const
{
  return std::unique_ptr<Shape>(new Triangle(a_, b_, c_));
}
