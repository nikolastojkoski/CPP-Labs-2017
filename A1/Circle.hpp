#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.hpp"
#include "base-types.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t center, const double radius);
  double getArea() const;
  rectangle_t getFrameRect() const;
  void move(const double dx, const double dy);
  void move(const point_t p);

private:
  point_t center_;
  double radius_;
};

#endif
