#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t center, double width, const double height);

  double getArea() const;
  rectangle_t getFrameRect() const;
  void move(const double dx, const double dy);
  void move(const point_t p);

private:
  rectangle_t rect_;
};

#endif
