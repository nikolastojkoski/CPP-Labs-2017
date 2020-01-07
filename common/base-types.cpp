#include "base-types.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

void point_t::rotateAroundCenter(const point_t &center, const radians_t &rad)
{
  double cosA = std::cos(rad.angle);
  double sinA = std::sin(rad.angle);

  double tx = x - center.x;
  double ty = y - center.y;

  x = tx*cosA - ty*sinA + center.x;
  y = tx*sinA + ty*cosA + center.y;
}
void point_t::rotateAroundCenter(const point_t &center, const degrees_t &deg)
{
  rotateAroundCenter(center, radians_t{ (deg.angle * M_PI) / 180 });
}
