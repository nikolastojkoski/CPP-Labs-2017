#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <math.h>
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "CompositeShape.hpp"

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(compositeShape_tests)
BOOST_AUTO_TEST_CASE(compositeShape_matching_shape)
{
  Circle c({ 11,4 }, 8);
  CompositeShape cs;
  cs.addShape(c);
  BOOST_CHECK_CLOSE(cs.getArea(), c.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs.getFrameRect().height, c.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(cs.getFrameRect().width, c.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(cs.getFrameRect().pos.x, 11, EPSILON);
  BOOST_CHECK_CLOSE(cs.getFrameRect().pos.y, 4, EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_getArea_1)
{
  Circle c({ 61, 18 }, 7.23);
  Triangle t({ -61.5, 2 }, { 71, 0 }, { 14.4, 3.14 });
  Rectangle r({ 1, 5 }, 10, 12);

  CompositeShape cs;
  cs.addShape(c);
  cs.addShape(t);
  cs.addShape(r);
  BOOST_CHECK_CLOSE(cs.getArea(), c.getArea() + t.getArea() + r.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_getArea_2)
{
  Circle c1({ -91, 127.4 }, 2);
  Triangle t1({ -9, 27 }, { 1,-1 }, { 15,81 });
  CompositeShape cs1;
  cs1.addShape(c1);
  cs1.addShape(t1);

  Rectangle r1({ 13,18 }, 8, 5);
  Rectangle r2({ 1, 5 }, 10, 12);
  Triangle t2({ -11, 2.7 }, { -5, -21 }, { 8.44, 91.666 });
  CompositeShape cs2;
  cs2.addShape(r1);
  cs2.addShape(r2);
  cs2.addShape(t2);

  CompositeShape cs3;
  cs3.addShape(cs1);
  cs3.addShape(cs2);
  BOOST_CHECK_CLOSE(cs3.getArea(), cs1.getArea() + cs2.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs3.getArea(), c1.getArea() + t1.getArea() + r1.getArea()
    + r2.getArea() + t2.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_getArea_3)
{
  Circle c({ -191, 127.4 }, 22);
  Rectangle r({ 13,128 }, 84, 35);
  Triangle t({ -11, -12.7 }, { -5, -121 }, { 48.44, 291.666 });
  CompositeShape cs;
  cs.addShape(c);
  cs.addShape(r);
  cs.addShape(t);
  BOOST_CHECK_CLOSE(c.getArea(), cs[0].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(r.getArea(), cs[1].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(t.getArea(), cs[2].getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_getArea_4)
{
  Circle c({ -191, 127.4 }, 22);
  Rectangle r({ 13,128 }, 84, 35);
  CompositeShape cs1;
  cs1.addShape(c);
  cs1.addShape(r);

  Triangle t({ -11, -12.7 }, { -5, -121 }, { 48.44, 291.666 });
  CompositeShape cs2;
  cs2.addShape(cs1);
  cs2.addShape(t);
  
  BOOST_CHECK_CLOSE(cs1.getArea(), cs2[0].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(t.getArea(), cs2[1].getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_move_dxy)
{
  CompositeShape cs;
  cs.addShape(Triangle({ -9, 27 }, { 1,-1 }, { 15,81 }));
  cs.addShape(Circle({ 7,19 }, 6));
  const double width_before = cs.getFrameRect().width;
  const double height_before = cs.getFrameRect().height;
  const double area_before = cs.getArea();
  cs.move(-3.316, 1.257);
  BOOST_CHECK_CLOSE(width_before, cs.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(height_before, cs.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(area_before, cs.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_move_point)
{
  CompositeShape cs;
  cs.addShape(Triangle({ -11, 2.7 }, { -5, -21 }, { 8.44, 91.666 }));
  const double width_before = cs.getFrameRect().width;
  const double height_before = cs.getFrameRect().height;
  const double area_before = cs.getArea();
  cs.move({ 45.8, -3.38 });
  BOOST_CHECK_CLOSE(width_before, cs.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(height_before, cs.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(area_before, cs.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_assignment)
{
  CompositeShape cs1;
  cs1.addShape(Circle({ -91, 127.4 }, 2));
  CompositeShape cs2;
  cs2.addShape(Rectangle({ 13,18 }, 8, 5));
  cs2 = cs1;
  BOOST_CHECK_CLOSE(cs1.getArea(), cs2.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs1.getFrameRect().height, cs2.getFrameRect().height, EPSILON);
  BOOST_CHECK_CLOSE(cs1.getFrameRect().width, cs2.getFrameRect().width, EPSILON);
  BOOST_CHECK_CLOSE(cs1.getFrameRect().pos.x, cs2.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(cs1.getFrameRect().pos.y, cs2.getFrameRect().pos.y, EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_self_assignment)
{
  CompositeShape cs1;
  cs1.addShape(Circle({ -91, 127.4 }, 2));
  CompositeShape cs2;
  cs2.addShape(cs1[0]);
  cs2 = cs2;
  BOOST_CHECK(cs2.size() == cs1.size());
  BOOST_CHECK_CLOSE(cs1.getArea(), cs2.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_multiple_assignment)
{
  CompositeShape cs1;
  cs1.addShape(Circle({ -91, 127.4 }, 2));
  CompositeShape cs2;
  cs2.addShape(Rectangle({ -1, 5 }, 4, 8));
  CompositeShape cs3;
  cs3.addShape(Triangle({ 1,5 }, { 8,1 }, { 2,7 }));
  
  cs1 = cs2 = cs3;

  BOOST_CHECK(cs1.size() == 1);
  BOOST_CHECK(cs2.size() == 1);
  BOOST_CHECK(cs3.size() == 1);
  BOOST_CHECK_CLOSE(cs1.getArea(), cs2.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs1.getArea(), cs3.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_complex_assignment)
{
  CompositeShape cs1;
  cs1.addShape(Circle({ -91, 127.4 }, 2));
  CompositeShape cs2;
  cs2.addShape(Rectangle({ -1, 5 }, 4, 8));
  CompositeShape cs3;
  cs3.addShape(cs1);

  cs1 = cs2 = cs3;
  
  BOOST_CHECK(cs1.size() == 1);
  BOOST_CHECK(cs2.size() == 1);
  BOOST_CHECK(cs3.size() == 1);
  BOOST_CHECK_CLOSE(cs1.getArea(), cs2.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs1.getArea(), cs3.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_move_constructor)
{
  Circle c({ 1,2 }, 3);
  CompositeShape cs1;
  cs1.addShape(c);
  CompositeShape cs2(std::move(cs1));
  BOOST_CHECK(cs1.size() == 0);
  BOOST_CHECK_CLOSE(cs2.getArea(), c.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_move_operator)
{
  Circle c({ 1,2 }, 3);
  Rectangle r({ 1,1 }, 4, 3);
  CompositeShape cs1;
  cs1.addShape(c);
  CompositeShape cs2;
  cs2.addShape(r);
  
  cs2 = std::move(cs1);

  BOOST_CHECK(cs1.size() == 0);
  BOOST_CHECK_CLOSE(cs2.getArea(), c.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_copy_shape)
{
  Rectangle r({ 11.89, -54.1 }, 61.1, 84.8);
  CompositeShape cs;
  cs.addShape(r);

  r.move(-74, 61);
  BOOST_CHECK(std::fabs(r.getFrameRect().pos.x - cs.getFrameRect().pos.x) > EPSILON);
  BOOST_CHECK(std::fabs(r.getFrameRect().pos.y - cs.getFrameRect().pos.y) > EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_scale)
{
  Rectangle r1( {0.5, 0.5}, 1, 1 );
  Rectangle r2( { 3, 3}, 2, 2 );
  CompositeShape cs1;
  cs1.addShape(r1);
  cs1.addShape(r2);

  cs1.scale(0.5);
  BOOST_CHECK_CLOSE(cs1.getFrameRect().pos.x, 2, EPSILON);
  BOOST_CHECK_CLOSE(cs1.getFrameRect().pos.y, 2, EPSILON);
  BOOST_CHECK_CLOSE(cs1.getFrameRect().width, 2, EPSILON);
  BOOST_CHECK_CLOSE(cs1.getFrameRect().height, 2, EPSILON);

  BOOST_CHECK_CLOSE(cs1[0].getFrameRect().pos.x, 1.25, EPSILON);
  BOOST_CHECK_CLOSE(cs1[0].getFrameRect().pos.y, 1.25, EPSILON);
  BOOST_CHECK_CLOSE(cs1[0].getFrameRect().width, 0.5, EPSILON);
  BOOST_CHECK_CLOSE(cs1[0].getFrameRect().height, 0.5, EPSILON);

  BOOST_CHECK_CLOSE(cs1[1].getFrameRect().pos.x, 2.5, EPSILON);
  BOOST_CHECK_CLOSE(cs1[1].getFrameRect().pos.y, 2.5, EPSILON);
  BOOST_CHECK_CLOSE(cs1[1].getFrameRect().width, 1, EPSILON);
  BOOST_CHECK_CLOSE(cs1[1].getFrameRect().height, 1, EPSILON);

}
BOOST_AUTO_TEST_CASE(compositeShape_scale_area_1)
{
  CompositeShape cs;
  cs.addShape(Circle({ 13,18 }, 8));
  cs.addShape(Triangle({ -14.21, 8.99 }, { 121.12, 66.55 }, { 1.23, -3.21 }));
  cs.addShape(Triangle({ -11, 2.7 }, { -5, -21 }, { 8.44, 91.666 }));
  const double area_before = cs.getArea();
  const double k = 0.77;
  cs.scale(k);
  BOOST_CHECK_CLOSE(area_before * k * k, cs.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_scale_area_2)
{
  Circle c({ 13,18 }, 8);
  Triangle t({ -14.21, 8.99 }, { 121.12, 66.55 }, { 1.23, -3.21 });

  CompositeShape cs;
  cs.addShape(c);
  cs.addShape(t);

  const double k = 1.337;
  cs.scale(k);
  c.scale(k);
  t.scale(k);
  BOOST_CHECK_CLOSE(c.getArea() + t.getArea(), cs.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_scale_area_3)
{
  CompositeShape cs1;
  cs1.addShape(Circle({ -91, 127.4 }, 2));
  cs1.addShape(Triangle({ -9, 27 }, { 1,-1 }, { 15,81 }));

  CompositeShape cs2;
  cs2.addShape(Rectangle({ 13,18 }, 8, 5));
  cs2.addShape(Rectangle({ 1, 5 }, 10, 12));
  cs2.addShape(Triangle({ -11, 2.7 }, { -5, -21 }, { 8.44, 91.666 }));

  CompositeShape cs3(cs1);
  cs3.addShape(cs2);

  const double k = 2.017;
  cs1.scale(k);
  cs2.scale(k);
  cs3.scale(k);

  CompositeShape cs4(cs1);
  cs4.addShape(cs2);

  BOOST_CHECK_CLOSE(cs3.getArea(), cs1.getArea() + cs2.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs4.getArea(), cs3.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_scale_center)
{
  CompositeShape cs;
  cs.addShape(Circle({ 13,18 }, 8));
  cs.addShape(Triangle({ -14.21, 8.99 }, { 121.12, 66.55 }, { 1.23, -3.21 }));
  cs.addShape(Triangle({ -11, 2.7 }, { -5, -21 }, { 8.44, 91.666 }));
  const point_t center_before = cs.getFrameRect().pos;
  const double k = 1.37;
  cs.scale(k);
  BOOST_CHECK_CLOSE(center_before.x, cs.getFrameRect().pos.x, EPSILON);
  BOOST_CHECK_CLOSE(center_before.y, cs.getFrameRect().pos.y, EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_remove_test_1)
{
  Triangle t1({ -14.21, 8.99 }, { 121.12, 66.55 }, { 1.23, -3.21 });
  Triangle t2({ -11, 2.7 }, { -5, -21 }, { 8.44, 91.666 });
  CompositeShape cs1;
  cs1.addShape(t1);
  cs1.addShape(t2);

  BOOST_CHECK_CLOSE(cs1[0].getArea(), t1.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs1[1].getArea(), t2.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs1.getArea(), t1.getArea() + t2.getArea(), EPSILON);

  cs1.removeShape(1);

  BOOST_CHECK(cs1.size() == 1);
  BOOST_CHECK_CLOSE(cs1[0].getArea(), t1.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs1.getArea(), t1.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_remove_test_2)
{
  Triangle t1({ -14.21, 8.99 }, { 121.12, 66.55 }, { 1.23, -3.21 });
  Triangle t2({ -11, 2.7 }, { -5, -21 }, { 8.44, 91.666 });
  CompositeShape cs1;
  cs1.addShape(t1);
  cs1.addShape(t2);

  BOOST_CHECK_CLOSE(cs1[0].getArea(), t1.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs1[1].getArea(), t2.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs1.getArea(), t1.getArea() + t2.getArea(), EPSILON);

  cs1.removeShape(0);

  BOOST_CHECK(cs1.size() == 1);
  BOOST_CHECK_CLOSE(cs1[0].getArea(), t2.getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs1.getArea(), t2.getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_invalid_scale_1)
{
  CompositeShape cs;
  cs.addShape(Circle({ 1, 2 }, 3));
  BOOST_CHECK_THROW(cs.scale(0), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(compositeShape_invalid_scale_2)
{
  CompositeShape cs;
  cs.addShape(Circle({ 1, 2 }, 3));
  BOOST_CHECK_THROW(cs.scale(-2), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(compositeShape_operator_out_of_range)
{
  CompositeShape cs;
  cs.addShape(Circle({ 1,2 }, 3));
  BOOST_CHECK_THROW(cs[5], std::out_of_range);
}
BOOST_AUTO_TEST_CASE(compositeShape_removeShape_out_of_range)
{
  CompositeShape cs;
  cs.addShape(Circle({ 1,2 }, 3));
  BOOST_CHECK_THROW(cs.removeShape(3), std::out_of_range);
}
BOOST_AUTO_TEST_CASE(compositeShape_empty_getArea)
{
  CompositeShape cs;
  BOOST_CHECK_CLOSE(cs.getArea(), 0, EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_empty_getFrameRect)
{
  CompositeShape cs;
  BOOST_CHECK_CLOSE(cs.getFrameRect().height, 0, EPSILON);
  BOOST_CHECK_CLOSE(cs.getFrameRect().width, 0, EPSILON);
  BOOST_CHECK_CLOSE(cs.getFrameRect().pos.x, 0, EPSILON);
  BOOST_CHECK_CLOSE(cs.getFrameRect().pos.y, 0, EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_copy_constructor)
{
  CompositeShape cs1;
  cs1.addShape(Circle({ 1,2 }, 3));
  cs1.addShape(Rectangle({ 4,5 }, 6, 7));

  CompositeShape cs2(cs1);

  BOOST_CHECK(cs2.size() == cs1.size());
  BOOST_CHECK_CLOSE(cs2[0].getArea(), cs1[0].getArea(), EPSILON);
  BOOST_CHECK_CLOSE(cs2[1].getArea(), cs1[1].getArea(), EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_const_copy_1)
{
  Circle c({ 5,10 }, 15);
  const double initialArea = c.getArea();

  CompositeShape cs;
  cs.addShape(c);

  cs.scale(3);

  BOOST_CHECK_CLOSE(c.getArea(), initialArea, EPSILON);
}
BOOST_AUTO_TEST_CASE(compositeShape_const_copy_2)
{
  Circle c({ 5,10 }, 15);
  const double initialArea = c.getArea();

  CompositeShape cs;
  cs.addShape(c);

  cs[0].scale(3);

  BOOST_CHECK_CLOSE(c.getArea(), initialArea, EPSILON);
}
BOOST_AUTO_TEST_SUITE_END()
