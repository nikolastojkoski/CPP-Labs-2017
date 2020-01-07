#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t &center, double width, double height);

  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void move(double dx, double dy) noexcept override;
  void move(const point_t &p) noexcept override;
  void scale(double k) override;
  void rotate(const degrees_t&) noexcept;
  void rotate(const radians_t&) noexcept;

  std::unique_ptr<Shape> getCopy() const override;

private:
  point_t vertices_[4];
  point_t getCenter() const noexcept;
  static double getDistance(const point_t &p1, const point_t &p2) noexcept;
};

#endif
