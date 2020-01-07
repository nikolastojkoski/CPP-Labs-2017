#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Shape.hpp"
#include "base-types.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t &p1, const point_t &p2, const point_t &p3);

  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void move(double dx, double dy) noexcept override;
  void move(const point_t &p) noexcept override;
  void scale(double k) override;
  void rotate(const degrees_t&) noexcept;
  void rotate(const radians_t&) noexcept;

  std::unique_ptr<Shape> getCopy() const override;

private:
  point_t a_, b_, c_;
  point_t getCenter() const noexcept;
  static double getDistance(const point_t &p1, const point_t &p2) noexcept;
};

#endif
