#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <math.h>
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "CompositeShape.hpp"
#include "ShapeMatrix.hpp"

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(shapeMatrix_tests)
BOOST_AUTO_TEST_CASE(shapeMatrix_addShape)
{
  ShapeMatrix sm;
  BOOST_CHECK(sm.size() == 0);
  BOOST_CHECK(sm.isBalanced() == true);
  sm.addShape(Circle({ 2,2 }, 4));
  BOOST_CHECK(sm.size() == 1);
  BOOST_CHECK(sm[0].size() == 1);
  BOOST_CHECK(sm.isBalanced() == true);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_matching_shape)
{
  Circle c({ 11,4 }, 8);
  ShapeMatrix sm;
  sm.addShape(c);
  BOOST_CHECK_CLOSE(sm[0][0].getArea(), c.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_removeShape)
{
  Circle c({ 11,4 }, 8);
  ShapeMatrix sm;
  sm.addShape(c);
  sm.removeShape(0, 0);
  BOOST_CHECK(sm.size() == 0);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_layers)
{
  Circle c1({ 1,1 }, 5);
  Circle c2({ 2,2 }, 10); // ^overlaps c1
  Circle c3({ 15,15 }, 1); // ^no overlap

  ShapeMatrix sm;
  sm.addShape(c2);
  sm.addShape(c1);
  sm.addShape(c3);
  sm.addShape(c3);
  sm.addShape(c2);

  BOOST_CHECK(sm.size() == 3);
  BOOST_CHECK(sm[0].size() == 2);
  BOOST_CHECK(sm[1].size() == 2);
  BOOST_CHECK(sm[2].size() == 1);
  BOOST_CHECK_CLOSE(sm[0][0].getArea(), c2.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm[0][1].getArea(), c3.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm[1][0].getArea(), c1.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm[1][1].getArea(), c3.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm[2][0].getArea(), c2.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_removeLayer)
{
  Circle c1({ 1,1 }, 5);
  Circle c2({ 2,2 }, 10); // ^overlaps c1
  Circle c3({ 15,15 }, 1); // ^no overlap

  ShapeMatrix sm;
  sm.addShape(c2);
  sm.addShape(c1);
  sm.addShape(c3);
  sm.addShape(c3);
  sm.addShape(c2);

  sm.removeShape(0, 0);
  BOOST_CHECK(sm[0].size() == 1);

  sm.removeShape(0, 0);
  BOOST_CHECK(sm.size() == 2);

  BOOST_CHECK(sm[0].size() == 2);
  BOOST_CHECK(sm[1].size() == 1);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_balance)
{
  Circle c1({ 1,1 }, 5);
  Circle c2({ 2,2 }, 10); // ^overlaps c1
  Circle c3({ 15,15 }, 1); // ^no overlap

  ShapeMatrix sm;
  sm.addShape(c2);
  sm.addShape(c1);
  sm.addShape(c3);
  sm.addShape(c3);
  sm.addShape(c2);

  sm.removeShape(0, 0);
  BOOST_CHECK(sm[0].size() == 1);
  BOOST_CHECK_CLOSE(sm[0][0].getArea(), c3.getArea(), EPSILON);
  BOOST_CHECK(sm.isBalanced() == false);

  sm.balance();
  BOOST_CHECK(sm.isBalanced() == true);
  BOOST_CHECK(sm.size() == 2);
  BOOST_CHECK(sm[0].size() == 2);
  BOOST_CHECK_CLOSE(sm[0][1].getArea(), c1.getArea(), EPSILON);
  BOOST_CHECK(sm[1].size() == 2);
  BOOST_CHECK_CLOSE(sm[1][1].getArea(), c2.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_assignment)
{
  Circle c1({ 1,1 }, 14);
  Circle c2({ 4,4 }, 10);
  ShapeMatrix sm1;
  sm1.addShape(c1);
  sm1.addShape(c2);

  ShapeMatrix sm2;
  sm2 = sm1;

  BOOST_CHECK(sm1.size() == sm2.size());
  BOOST_CHECK_CLOSE(sm1[0][0].getArea(), sm2[0][0].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm1[1][0].getArea(), sm2[1][0].getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(unbalancedShapeMatrix_assignment)
{
  Circle c1({ 1,1 }, 5);
  Circle c2({ 2,2 }, 10); // ^overlaps c1
  Circle c3({ 15,15 }, 1); // ^no overlap
  ShapeMatrix sm;
  sm.addShape(c2);
  sm.addShape(c1);
  sm.addShape(c3);

  sm.removeShape(0, 0);
  BOOST_CHECK(sm.size() == 2);
  BOOST_CHECK(sm.isBalanced() == false);

  ShapeMatrix sm2;
  sm2 = sm;
  BOOST_CHECK(sm2.size() == 2);
  BOOST_CHECK(sm2.isBalanced() == false);
  BOOST_CHECK_CLOSE(sm2[0][0].getArea(), sm[0][0].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm2[1][0].getArea(), sm[1][0].getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_self_assignment)
{
  Circle c1({ 1,1 }, 14);
  Circle c2({ 4,4 }, 10);
  ShapeMatrix sm1;
  sm1.addShape(c1);
  sm1.addShape(c2);
  
  sm1 = sm1;

  BOOST_CHECK(sm1.size() == 2);
  BOOST_CHECK_CLOSE(sm1[0][0].getArea(), c1.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm1[1][0].getArea(), c2.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_multiple_assignment)
{
  Circle c1({ 1,1 }, 14);
  ShapeMatrix sm1;
  ShapeMatrix sm2;
  ShapeMatrix sm3;
  sm3.addShape(c1);

  sm1 = sm2 = sm3;

  BOOST_CHECK(sm1.size() == 1);
  BOOST_CHECK(sm2.size() == 1);
  BOOST_CHECK_CLOSE(sm1[0][0].getArea(), sm3[0][0].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm2[0][0].getArea(), sm3[0][0].getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_copy_constructor)
{
  Circle c1({ 1,1 }, 14);
  ShapeMatrix sm1;
  sm1.addShape(c1);
  ShapeMatrix sm2(sm1);
  BOOST_CHECK(sm2.size() == 1);
  BOOST_CHECK_CLOSE(sm2[0][0].getArea(), c1.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_move_assignment)
{
  Circle c1({ 1,1 }, 14);
  ShapeMatrix sm1;
  sm1.addShape(c1);
  ShapeMatrix sm2;
  sm2 = std::move(sm1);

  BOOST_CHECK(sm1.size() == 0);
  BOOST_CHECK(sm2.size() == 1);
  BOOST_CHECK_CLOSE(sm2[0][0].getArea(), c1.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_move_constructor)
{
  Circle c1({ 1,1 }, 14);
  ShapeMatrix sm1;
  sm1.addShape(c1);
  ShapeMatrix sm2(std::move(sm1));

  BOOST_CHECK(sm1.size() == 0);
  BOOST_CHECK(sm2.size() == 1);
  BOOST_CHECK_CLOSE(sm2[0][0].getArea(), c1.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_operator_out_of_range)
{
  ShapeMatrix sm;
  sm.addShape(Circle({ 1,2 }, 3));
  BOOST_CHECK_THROW(sm[5][10], std::out_of_range);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_removeShape_out_of_range)
{
  ShapeMatrix sm;
  BOOST_CHECK_THROW(sm.removeShape(0, 0), std::out_of_range);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_intensive_crashtest)
{
  ShapeMatrix sm;
  for(int t = 0; t < 100; t++)
  {
    int add = std::rand() % 10;
    for(int a = 0; a < add; a++)
    {
      double radius = static_cast<double>(std::fabs((std::rand() % 30)) + 1);
      assert(radius > 0);

      Circle c({ static_cast<double>(std::rand() % 100), static_cast<double>(std::rand() % 100) }, radius);
      sm.addShape(c);
    }
    int rem = std::rand() % 5;
    for(int r = 0; r < rem; r++)
    {
      if(sm.size() > 0)
      {
        size_t i = std::rand() % sm.size();
        size_t j = std::rand() % sm[i].size();
        sm.removeShape(i, j);

        int balance = std::rand() % 50;
        if(balance % 3 == 0)
        {
          sm.balance();
        }
      }
    }
    for(size_t i = 0; i < sm.size(); i++)
    {
      for(size_t j = 0; j < sm[i].size(); j++)
      {
        double a = sm[i][j].getArea();
        assert(a > 0);
      }
    }

  }
}
BOOST_AUTO_TEST_CASE(shapeMatrix_compositeShape_decomposition_1)
{
  CompositeShape cs;
  cs.addShape(Circle({ 4,6 }, 4));
  cs.addShape(Rectangle({ 5,8 }, 4, 6));
  cs.addShape(Circle({ 15,15 }, 1));

  ShapeMatrix sm;
  sm.addCompositeShapeElements(cs);

  BOOST_CHECK_CLOSE(sm[0][0].getArea(), cs[0].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm[0][1].getArea(), cs[2].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm[1][0].getArea(), cs[1].getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_compositeShape_decomposition_2)
{
  CompositeShape cs;
  cs.addShape(Circle({ 0,0 }, 1));
  cs.addShape(Circle({ 0,0 }, 1));
  cs.addShape(Circle({ 5,5 }, 2));
  cs.addShape(Circle({ 5,5 }, 2));
  cs.addShape(Circle({ 10,10 }, 3));
  cs.addShape(Circle({ 10,10 }, 3));

  ShapeMatrix sm;
  sm.addCompositeShapeElements(cs);

  BOOST_CHECK(sm.size() == 2);
  BOOST_CHECK(sm[0].size() == 3);
  BOOST_CHECK(sm[1].size() == 3);

  BOOST_CHECK_CLOSE(sm[0][0].getArea(), cs[0].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm[0][1].getArea(), cs[2].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm[0][2].getArea(), cs[4].getArea(), EPSILON);

  BOOST_CHECK_CLOSE(sm[1][0].getArea(), cs[1].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm[1][1].getArea(), cs[3].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(sm[1][2].getArea(), cs[5].getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(shapeMatrix_compositeShape_decomposition_rotation)
{
  CompositeShape cs;
  cs.addShape(Rectangle({ 0,0 }, 6, 10));
  cs.addShape(Rectangle({ 8,0 }, 4, 8));

  ShapeMatrix sm;
  sm.addCompositeShapeElements(cs);
  BOOST_CHECK(sm.size() == 1);

  cs[0].rotate(degrees_t{ 90 });
  cs[1].rotate(degrees_t{ 90 });

  ShapeMatrix sm2;
  sm2.addCompositeShapeElements(cs);
  BOOST_CHECK(sm2.size() == 2);
}
BOOST_AUTO_TEST_SUITE_END()
