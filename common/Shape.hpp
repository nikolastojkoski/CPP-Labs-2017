#ifndef SHAPE_H
#define SHAPE_H
#include <memory>
#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const noexcept = 0;
  virtual rectangle_t getFrameRect() const noexcept = 0;
  virtual void move(double dx, double dy) noexcept = 0;
  virtual void move(const point_t &p)  noexcept = 0;
  virtual void scale(double k) = 0;
  virtual void rotate(const degrees_t &rad) noexcept = 0;
  virtual void rotate(const radians_t &deg) noexcept = 0;

  virtual std::unique_ptr<Shape> getCopy() const = 0;
};

#endif
