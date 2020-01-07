#include <iostream>
#include "ShapeMatrix.hpp"
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
  std::cout << "-----CompositeShape" << num << std::endl;
  printInfo(shape);
  std::cout << "Size = " << shape.size() <<", elements: " << std::endl;
  for(size_t i = 0; i < shape.size(); i++)
  {
    printInfo(shape[i]);
  }
  std::cout << "--------------------------" << std::endl;
}
void printShapeMatrix(ShapeMatrix &sm)
{
  for(size_t i = 0; i < sm.size(); i++)
  {
    for(size_t j = 0; j < sm[i].size(); j++)
    {
      std::cout << "ShapeMatrix[" << i << "][" << j << "] " << std::endl;
      printInfo(sm[i][j]);
    }
  }
  std::cout << "--------------------------" << std::endl << std::endl;
}

int main()
{
  Rectangle r({ 5,5 }, 5, 10);
  std::cout << "Creating Rectangle:" << std::endl;
  printInfo(r);

  std::cout << "Rotating Rectangle by 90 degrees" << std::endl;
  r.rotate(degrees_t{ 90 });
  printInfo(r);

  Triangle t({ 1,1 }, { 3, 4 }, { 6, 11 });
  std::cout << "Creating Triangle: " << std::endl;
  printInfo(t);
 
  CompositeShape cs;
  cs.addShape(r);
  cs.addShape(t);
  std::cout << "Creating CompositeShape with Rectangle and Triangle" << std::endl;
  printInfo(cs, 1);

  std::cout << "Rotating CompositeShape by 90 degrees" << std::endl;
  cs.rotate(degrees_t{ 90 });
  printInfo(cs, 1);

  std::cout << "Rotating Triangle by 90 degrees: " << std::endl;
  t.rotate(degrees_t{ 90 });
  printInfo(t);

  Circle c({ -4, -10 }, 10);
  std::cout << "Creating Circle: " << std::endl;
  printInfo(c);

  std::cout << "Adding Circle to CompositeShape" << std::endl;
  cs.addShape(c);
  printInfo(cs, 1);

  ShapeMatrix sm;
  sm.addCompositeShapeElements(cs);
  std::cout << "Creating ShapeMatrix from CompositeShapeElements: " << std::endl;
  printShapeMatrix(sm);

  std::cout << "Adding (the same) Circle to ShapeMatrix" << std::endl;
  sm.addShape(c);
  printShapeMatrix(sm);

  std::cout << "Removing the first Circle from ShapeMatrix" << std::endl;
  sm.removeShape(0, 1);
  printShapeMatrix(sm);

  std::cout << "Balancing ShapeMatrix" << std::endl;
  sm.balance();
  printShapeMatrix(sm);

  return 0;
}
