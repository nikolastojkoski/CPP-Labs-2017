#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>

class Shape
{
public:
  Shape(double x, double y);
  virtual ~Shape() = default;
  bool isMoreLeft(const Shape *other) const;
  bool isUpper(const Shape *other) const;
  virtual void draw(std::ostream &out) const = 0;
protected:
  double x_, y_;
};


#endif
