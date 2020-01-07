#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.hpp"
#include "base-types.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &center, double radius);

  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void move(double dx, double dy) noexcept override;
  void move(const point_t &p) noexcept override;
  void scale(double k) override;
  void rotate(const degrees_t&) noexcept;
  void rotate(const radians_t&) noexcept;

  std::unique_ptr<Shape> getCopy() const override;

private:
  point_t center_;
  double radius_;
};

#endif
