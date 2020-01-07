#ifndef COMPSHAPE_H
#define COMPSHAPE_H
#include "Shape.hpp"
#include "base-types.hpp"

class CompositeShape : public Shape
{
public:
  CompositeShape();
  CompositeShape(const CompositeShape &comp);
  CompositeShape(CompositeShape &&comp);
  ~CompositeShape();
  
  CompositeShape& operator=(const CompositeShape &other);
  CompositeShape& operator=(CompositeShape &&other) noexcept;
  
  void addShape(const Shape &shape);
  void removeShape(size_t index);

  Shape& operator[](size_t index);
  const Shape& operator[](size_t index) const;

  size_t size() const noexcept;
  std::unique_ptr<Shape> getCopy() const override;

  double getArea() const noexcept override;
  rectangle_t getFrameRect() const noexcept override;
  void move(double dx, double dy) noexcept override;
  void move(const point_t &p) noexcept override;
  void scale(double k) override;
  void rotate(const degrees_t&) noexcept;
  void rotate(const radians_t&) noexcept;

private:
  std::unique_ptr<Shape> *arr_;
  size_t reserved_, size_;
  void reinitArray(size_t length);
  void resizeArray();
};

#endif
