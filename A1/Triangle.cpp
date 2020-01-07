#include "Triangle.hpp"
#include <algorithm>
#include <iostream>
#include "base-types.hpp"

Triangle::Triangle(const point_t p1, const point_t p2, const point_t p3) :
  a_(p1), 
  b_(p2), 
  c_(p3) 
{
  if(getArea() <= 0)
  {
    std::cerr << "Invalid triangle parameters! ";
    std::cerr << "Points do not form triangle" << std::endl;
  }
}
double Triangle::getArea() const
{
  double ab = getDistance(a_, b_);
  double ac = getDistance(a_, c_);
  double bc = getDistance(b_, c_);
  double s = (ab + ac + bc) / 2;
  return sqrt(s*(s - ab)*(s - ac)*(s - bc));
}
rectangle_t Triangle::getFrameRect() const
{
  using namespace std;
  double left = min(min(a_.x, b_.x), c_.x);
  double bot = min(min(a_.y, b_.y), c_.y);
  double h = abs(max(max(a_.y, b_.y), c_.y) - bot);
  double w = abs(max(max(a_.x, b_.x), c_.x) - left);
  return rectangle_t{ getCenter(), w, h };
}
void Triangle::move(const double dx, const double dy)
{
  a_.x += dx;
  b_.x += dx;
  c_.x += dx;
  a_.y += dy;
  b_.y += dy;
  c_.y += dy;
}
void Triangle::move(const point_t p)
{
  move(p.x - getCenter().x, p.y - getCenter().y);
}
point_t Triangle::getCenter() const
{
  return point_t{ (a_.x + b_.x + c_.x) / 3, (a_.y + b_.y + c_.y) / 3 };
}
double Triangle::getDistance(const point_t p1, const point_t p2) const
{
  return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}
