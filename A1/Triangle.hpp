#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.hpp"
#include "base-types.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t p1, const point_t p2, const point_t p3);

  double getArea() const;
  rectangle_t getFrameRect() const;
  void move(const double dx, const double dy);
  void move(const point_t p);

private:
  point_t a_, b_, c_;
  point_t getCenter() const;
  double getDistance(const point_t p1, const point_t p2) const;
};

#endif
