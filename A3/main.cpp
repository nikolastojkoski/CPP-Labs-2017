#include <iostream>
#include "CompositeShape.hpp"
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
void printInfo(CompositeShape &shape, int num)
{
  printInfo(shape);
  std::cout << "-----CompositeShape" << num << " elements:" << std::endl;
  std::cout << "Size = " << shape.size() << std::endl;
  for(size_t i = 0; i < shape.size(); i++)
  {
    printInfo(shape[i]);
  }
  std::cout << "--------------------------" << std::endl;
}
int main()
{
  std::cout << "Creating Circle x=11, y=20, r=5" << std::endl;
  Circle c({ 11,20 }, 5);
  printInfo(c);

  std::cout << "Creating Rectangle x=16, y=8, w=6, h=2" << std::endl;
  Rectangle r({ 16,8 }, 6, 2);
  printInfo(r);

  std::cout << "Creating Triangle with points A(13,42), B(31,28), C(25,20)" << std::endl;
  Triangle t({ 13, 42 }, { 31, 28 }, { 25, 20 });
  printInfo(t);

  std::cout << "Creating CompositeShape1 with Circle" << std::endl;
  CompositeShape cs1;
  cs1.addShape(c);
  printInfo(cs1, 1);

  std::cout << "Adding Rectangle to CompositeShape1" << std::endl;
  cs1.addShape(r);
  printInfo(cs1, 1);

  std::cout << "Moving CompositeShape1 by dx=3, dy=10" << std::endl;
  cs1.move(3, 10);
  printInfo(cs1, 1);

  std::cout << "Moving CompositeShape1 to point x=14, y=28" << std::endl;
  cs1.move({ 14,28 });
  printInfo(cs1, 1);

  std::cout << "Creating CompositeShape2 from CompositeShape1" << std::endl;
  CompositeShape cs2(cs1);
  printInfo(cs2, 2);

  std::cout << "Scaling CompositeShape2 by k=1.4" << std::endl;
  cs2.scale(1.4);
  printInfo(cs2, 2);

  std::cout << "Adding Triangle to CompositeShape2" << std::endl;
  cs2.addShape(t);
  printInfo(cs2, 2);

  std::cout << "Assigning CompositeShape2 to CompositeShape1" << std::endl;
  cs1 = cs2;
  printInfo(cs1, 1);

  std::cout << "Scaling CompositeShape2 by k=1.4" << std::endl;
  cs2.scale(1.4);
  printInfo(cs2, 2);

  return 0;
}
