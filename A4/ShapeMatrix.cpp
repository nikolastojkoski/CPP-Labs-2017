#include "ShapeMatrix.hpp"
#include <stdexcept>

ShapeMatrix::MatrixRow::MatrixRow(size_t row, const ShapeMatrix* parent) :
  row_(row),
  parent_(parent)
{
}
const Shape& ShapeMatrix::MatrixRow::operator[](size_t col) const
{
  if(col >= parent_->rowSize_[row_])
  {
    throw std::out_of_range("ShapeMatrix column index out of range");
  }
  return *(parent_->arr_[row_*parent_->cols_ + col]);
}
size_t ShapeMatrix::MatrixRow::size() const noexcept
{
  return parent_->rowSize_[row_];
}
ShapeMatrix::ShapeMatrix():
  nonEmptyRows_(0),
  rows_(0),
  cols_(0),
  balanced_(true)
{
  arr_ = nullptr;
  rowSize_ = nullptr;
}
ShapeMatrix::ShapeMatrix(const ShapeMatrix &matrix) :
  arr_(nullptr),
  rowSize_(nullptr)
{
  *this = matrix;
}
ShapeMatrix::ShapeMatrix(ShapeMatrix &&matrix) :
  arr_(nullptr),
  rowSize_(nullptr)
{
  *this = std::move(matrix);
}
ShapeMatrix& ShapeMatrix::operator=(const ShapeMatrix &other)
{
  if(this != &other)
  {
    std::unique_ptr<size_t[]>tempRowSize(new size_t[other.rows_]);
    for(size_t i = 0; i < other.rows_; i++)
    {
      tempRowSize[i] = other.rowSize_[i];
    }

    std::unique_ptr<std::unique_ptr<Shape>[]> tempArr(new std::unique_ptr<Shape>[other.rows_ * other.cols_]);
    for(size_t i = 0; i < other.size(); i++)
    {
      for(size_t j = 0; j < other[i].size(); j++)
      {
        tempArr[i*other.cols_ + j] = other[i][j].getCopy();
      }
    }

    arr_ = std::move(tempArr);
    rowSize_ = std::move(tempRowSize);
    nonEmptyRows_ = other.nonEmptyRows_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    balanced_ = other.balanced_;
  }
  return *this;
}
ShapeMatrix& ShapeMatrix::operator=(ShapeMatrix &&other) noexcept
{
  if(this != &other)
  {
    arr_ = std::move(other.arr_);
    other.arr_ = nullptr;

    rowSize_ = std::move(other.rowSize_);
    other.rowSize_ = nullptr;

    nonEmptyRows_ = other.nonEmptyRows_;
    other.nonEmptyRows_ = 0;
    
    rows_ = other.rows_;
    other.rows_ = 0;

    cols_ = other.cols_;
    other.cols_ = 0;

    balanced_ = other.balanced_;
    other.balanced_ = true;
  }
  return *this;
}
ShapeMatrix::MatrixRow ShapeMatrix::operator[](size_t row) const
{
  if(row >= nonEmptyRows_)
  {
    throw std::out_of_range("ShapeMatrix row index out of range");
  }
  return MatrixRow(row, this);
}
size_t ShapeMatrix::size() const noexcept
{
  return nonEmptyRows_;
}
void ShapeMatrix::resizeArray(size_t rows, size_t cols)
{
  std::unique_ptr<std::unique_ptr<Shape>[]> temp(new std::unique_ptr<Shape>[rows*cols]);
  for(size_t i = 0; i < nonEmptyRows_; i++)
  {
    for(size_t j = 0; j < rowSize_[i]; j++)
    {
      temp[i*cols + j] = std::move(arr_[i*cols_ + j]);
    }
  }
  arr_ = std::move(temp);
}
void ShapeMatrix::addRow()
{
  std::unique_ptr<size_t[]> temp(new size_t[rows_ + 1]);
  for(size_t i = 0; i < rows_; i++)
  {
    temp[i] = rowSize_[i];
  }
  temp[rows_] = 0;

  if(cols_ == 0)
  {
    resizeArray(rows_ + 1, cols_ + 1);
    cols_++;
  }
  else
  {
    resizeArray(rows_ + 1, cols_);
  }
  rowSize_ = std::move(temp);
  rows_++;
}
void ShapeMatrix::addColumn()
{
  resizeArray(rows_, cols_ + 1);
  cols_++;
}
void ShapeMatrix::addShape(const Shape &shape)
{
  std::unique_ptr<Shape> tempShape = shape.getCopy();
  bool addedToMatrix = false;
  for(size_t i = 0; i < rows_; i++)
  {
    bool overlapsLayer = false;
    for(size_t j = 0; j < rowSize_[i]; j++)
    {
      if(areOverlapping(shape, *arr_[i*cols_ + j]))
      {
        overlapsLayer = true;
        break;
      }
    }
    if(!overlapsLayer)
    {
      if(rowSize_[i] == cols_)
      {
        addColumn();
      }
      arr_[i*cols_ + rowSize_[i]] = std::move(tempShape);
      if(rowSize_[i] == 0)
      {
        nonEmptyRows_++;
      }
      rowSize_[i]++;
      addedToMatrix = true;
      break;
    }
  }
  if(!addedToMatrix)
  {
    addRow();
    arr_[(rows_ - 1) * cols_] = std::move(tempShape);
    rowSize_[rows_ - 1] = 1;
    nonEmptyRows_++;
  }
}
void ShapeMatrix::removeShape(size_t row, size_t col)
{
  if((row >= nonEmptyRows_) || (col >= rowSize_[row]))
  {
    throw std::out_of_range("MatrixShape index out of range");
  }
  for(size_t i = col + 1; i < rowSize_[row]; i++)
  {
    arr_[row*cols_ + i - 1] = std::move(arr_[row*cols_ + i]);
  }
  arr_[row*cols_ + rowSize_[row] - 1].reset(nullptr);
  rowSize_[row]--;

  if(rowSize_[row] == 0)
  {
    for(size_t i = row + 1; i < nonEmptyRows_; i++)
    {
      for(size_t j = 0; j < rowSize_[i]; j++)
      {
        arr_[(i - 1)*cols_ + j] = std::move(arr_[i*cols_ + j]);
      }
      rowSize_[i - 1] = rowSize_[i];
    }
    rowSize_[nonEmptyRows_ - 1] = 0;
    nonEmptyRows_--;
  }
  balanced_ = false;
}
void ShapeMatrix::addCompositeShapeElements(const CompositeShape &comp)
{
  ShapeMatrix temp(*this);
  for(size_t i = 0; i < comp.size(); i++)
  {
    temp.addShape(comp[i]);
  }
  *this = std::move(temp);
}
bool ShapeMatrix::isBalanced() const noexcept
{
  return balanced_;
}
void ShapeMatrix::balance()
{
  ShapeMatrix temp;
  for(size_t i = 0; i < nonEmptyRows_; i++)
  {
    for(size_t j = 0; j < rowSize_[i]; j++)
    {
      temp.addShape(*arr_[i*cols_ + j]);
    }
  }
  *this = std::move(temp);
  balanced_ = true;
}
bool ShapeMatrix::areOverlapping(const Shape &a, const Shape &b) noexcept
{
  rectangle_t frameA = a.getFrameRect();
  rectangle_t frameB = b.getFrameRect();

  if((frameA.pos.x - frameA.width / 2) < (frameB.pos.x + frameB.width / 2)
    && (frameA.pos.x + frameA.width / 2) > (frameB.pos.x - frameB.width / 2)
    && (frameA.pos.y + frameA.height / 2) > (frameB.pos.y - frameB.height / 2)
    && (frameA.pos.y - frameA.height / 2) < (frameB.pos.y + frameB.height / 2))
  {
    return true;
  }
  else
  {
    return false;
  }
}