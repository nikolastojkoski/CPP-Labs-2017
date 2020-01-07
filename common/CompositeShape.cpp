#include "CompositeShape.hpp"
#include <stdexcept>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

CompositeShape::CompositeShape() :
  reserved_(1),
  size_(0)
{
  arr_ = new std::unique_ptr<Shape>[1];
}
CompositeShape::CompositeShape(const CompositeShape &comp) :
  reserved_(comp.reserved_),
  size_(0)
{
  arr_ = new std::unique_ptr<Shape>[comp.reserved_];
  *this = comp;
}
CompositeShape::CompositeShape(CompositeShape &&comp) :
  arr_(nullptr),
  reserved_(0),
  size_(0)
{
  *this = std::move(comp);
}
CompositeShape::~CompositeShape()
{
  delete[] arr_;
  arr_ = nullptr;
}
CompositeShape& CompositeShape::operator=(const CompositeShape &other)
{
  if(this != &other)
  {
    if(reserved_ >= other.reserved_)
    {
      for(size_t i = 0; i < size_; i++)
      {
        arr_[i].reset(nullptr);
      }
      size_ = 0;
    }
    else
    {
      reinitArray(other.reserved_);
    }

    for(size_t i = 0; i < other.size(); i++)
    {
      addShape(other[i]);
    }
  }
  return *this;
}
CompositeShape& CompositeShape::operator=(CompositeShape &&other) noexcept
{
  if(this != &other)
  {
    delete[] arr_;
    arr_ = other.arr_;
    other.arr_ = nullptr;

    size_ = other.size_;
    other.size_ = 0;

    reserved_ = other.reserved_;
    other.reserved_ = 0;
  }
  return *this;
}
void CompositeShape::resizeArray()
{
  std::unique_ptr<Shape> *temp = new std::unique_ptr<Shape>[2 * reserved_];
  for(size_t i = 0; i < size_; i++)
  {
    temp[i] = std::move(arr_[i]);
  }
  delete[] arr_;
  arr_ = temp;
  reserved_ *= 2;
}
void CompositeShape::reinitArray(size_t length)
{
  std::unique_ptr<Shape> *temp = new std::unique_ptr<Shape>[length];
  delete[] arr_;
  arr_ = temp;
  reserved_ = length;
  size_ = 0;
}
Shape& CompositeShape::operator[](size_t index)
{
  if(index >= size_)
  {
    throw std::out_of_range("CompositeShape index out of range");
  }
  return *arr_[index];
}
const Shape& CompositeShape::operator[](size_t index) const
{
  if(index >= size_)
  {
    throw std::out_of_range("CompositeShape index out of range");
  }
  return *arr_[index];
}
void CompositeShape::removeShape(size_t index)
{
  if(index >= size_)
  {
    throw std::out_of_range("CompositeShape index out of range");
  }
  for(size_t i = index + 1; i < size_; i++)
  {
    arr_[i - 1] = std::move(arr_[i]);
  }
  arr_[--size_].reset(nullptr);
}
size_t CompositeShape::size() const noexcept
{
  return size_;
}
void CompositeShape::addShape(const Shape &shape)
{
  if(size_ == reserved_)
  {
    resizeArray();
  }
  arr_[size_++] = std::move(shape.getCopy());
}
std::unique_ptr<Shape> CompositeShape::getCopy() const
{
  return std::unique_ptr<CompositeShape>(new CompositeShape(*this));
}
double CompositeShape::getArea() const noexcept
{
  double area = 0;
  for(size_t i = 0; i < size_; i++)
  {
    area += arr_[i]->getArea();
  }
  return area;
}
rectangle_t CompositeShape::getFrameRect() const noexcept
{
  if(size_ == 0)
  {
    return { { 0, 0 }, 0, 0 };
  }

  rectangle_t r0 = arr_[0]->getFrameRect();
  double left = r0.pos.x - r0.width / 2;
  double right = r0.pos.x + r0.width / 2;
  double bot = r0.pos.y - r0.height / 2;
  double top = r0.pos.y + r0.height / 2;

  using namespace std;
  for(size_t i = 1; i < size_; i++)
  {
    rectangle_t ri = arr_[i]->getFrameRect();
    left = min(left, ri.pos.x - ri.width / 2);
    right = max(right, ri.pos.x + ri.width / 2);
    bot = min(bot, ri.pos.y - ri.height / 2);
    top = max(top, ri.pos.y + ri.height / 2);
  }
  return { (left + right) / 2, (bot + top) / 2, right - left, top - bot };
}
void CompositeShape::move(double dx, double dy) noexcept
{
  for(size_t i = 0; i < size_; i++)
  {
    arr_[i]->move(dx, dy);
  }
}
void CompositeShape::move(const point_t &p) noexcept
{
  point_t center = getFrameRect().pos;
  move(p.x - center.x, p.y - center.y);
}
void CompositeShape::scale(double k)
{
  if(k <= 0)
  {
    throw std::invalid_argument("Invalid CompositeShape scale coefficient!");
  }
  point_t compCenter = getFrameRect().pos;
  for(size_t i = 0; i < size_; i++)
  { 
    arr_[i]->scale(k);
    point_t shapeCenter = arr_[i]->getFrameRect().pos;
    arr_[i]->move((compCenter.x - shapeCenter.x) * k, (compCenter.y - shapeCenter.y) * k);
  }
}
void CompositeShape::rotate(const radians_t& rad) noexcept
{
  point_t compCenter = getFrameRect().pos;

  for(size_t i = 0; i < size_; i++)
  {
    point_t shapeCenter = arr_[i]->getFrameRect().pos;
    shapeCenter.rotateAroundCenter(compCenter, rad);
    arr_[i]->rotate(rad);
    arr_[i]->move(shapeCenter);
  }
}
void CompositeShape::rotate(const degrees_t& deg) noexcept
{
  rotate(radians_t{ (deg.angle * M_PI) / 180 });
}