#ifndef BASETYPES_H
#define BASETYPES_H

struct radians_t
{
  double angle;
};
struct degrees_t
{
  double angle;
};
struct point_t
{
  double x;
  double y;
  void rotateAroundCenter(const point_t &center, const radians_t &rad);
  void rotateAroundCenter(const point_t &center, const degrees_t &deg);
};
struct rectangle_t
{
  point_t pos;
  double width;
  double height;
};

#endif
