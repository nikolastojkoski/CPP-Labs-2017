#ifndef SHAPEMATRIX_H
#define SHAPEMATRIX_H
#include "Shape.hpp"
#include "CompositeShape.hpp"
#include "base-types.hpp"

/* Strong exception safety*/
class ShapeMatrix
{
public:
  class MatrixRow
  {
  public:
    friend class Matrix;
    MatrixRow(size_t row, const ShapeMatrix* parent);
    const Shape& operator[](size_t col) const;
    size_t size() const noexcept;
  private:
    size_t row_, size_;
    const ShapeMatrix *parent_;
  };

  ShapeMatrix();
  ShapeMatrix(const ShapeMatrix &matrix);
  ShapeMatrix(ShapeMatrix &&matrix);
  ~ShapeMatrix() = default;

  ShapeMatrix& operator=(const ShapeMatrix &other);
  ShapeMatrix& operator=(ShapeMatrix &&other) noexcept;

  MatrixRow operator[](size_t row) const;
  size_t size() const noexcept;

  void addCompositeShapeElements(const CompositeShape &comp);
  void addShape(const Shape &shape);
  void removeShape(size_t row, size_t col);

  bool isBalanced() const noexcept;
  void balance();

private:
  std::unique_ptr<std::unique_ptr<Shape>[]> arr_;
  std::unique_ptr < size_t[]> rowSize_;
  size_t nonEmptyRows_, rows_, cols_;
  bool balanced_;
  void addRow();
  void addColumn();
  void resizeArray(size_t rows, size_t cols);
  static bool areOverlapping(const Shape &a, const Shape &b) noexcept;
};

#endif
