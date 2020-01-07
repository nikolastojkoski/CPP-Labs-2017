#include <iostream>
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include "base-types.hpp"

void printInfo(const Shape &s)
{
  std::cout << "Area: " << s.getArea() << std::endl;
  rectangle_t fr = s.getFrameRect();
  std::cout << "Frame Rectangle - X: " << fr.pos.x << "; Y: " << fr.pos.y << std::endl;
  std::cout << "Frame Rectangle - Width: " << fr.width << "; Height: " << fr.height << "\n\n";
}
int main()
{
  std::cout << "Creating Rectangle x=14, y=19, w=3, h=5" << std::endl;
  Rectangle r({ 14,19 }, 3, 5);
  printInfo(r);

  std::cout << "Moving rectangle by dx=5, dy=10" << std::endl;
  r.move(5, 10);
  printInfo(r);

  std::cout << "Moving rectangle to point x=44.31, y=18.19" << std::endl;
  r.move({ 44.31, 18.19 });
  printInfo(r);

  std::cout << "Creating Circle x=14 y=18 r=3" << std::endl;
  Circle c({ 14, 18 }, 3);
  printInfo(c);

  std::cout << "Moving circle to point x=11.31, y=10" << std::endl;
  c.move({ 11.31, 10 });
  printInfo(c);

  std::cout << "Moving circle by dx = 5.5, dy = 21.1" << std::endl;
  c.move(5.5, 21.1);
  printInfo(c);

  std::cout << "Creating Triangle with points A(13,42), B(31,28), C(25,20)" << std::endl;
  Triangle t({ 13, 42 }, { 31, 28 }, { 25, 20 });
  printInfo(t);

  std::cout << "Moving triangle by dx = 1.8, dy = 5" << std::endl;
  t.move(1.8, 5);
  printInfo(t);

  std::cout << "Moving triangle to point x=22, y = 107" << std::endl;
  t.move({ 22, 107 });
  printInfo(t);

  return 0;
}
