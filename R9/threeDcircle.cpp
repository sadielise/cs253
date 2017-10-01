
// threeDCircle class inherits from class threeDPoint.

#include <iostream>  

using std::cout;

#include "threeDcircle.h"   // threeDCircle class definition

// default constructor
threeDCircle::threeDCircle( int xValue, int yValue, int zValue, double radiusValue ) // create a threeDCircle object in the plane z=zValue
   : threeDPoint( xValue, yValue, zValue )  // call base-class constructor
{
   setRadius( radiusValue );

} // end threeDCircle constructor

// set radius 
void threeDCircle::setRadius( double radiusValue )
{
   radius = ( radiusValue < 0.0 ? 0.0 : radiusValue );

} // end function setRadius

// return radius 
double threeDCircle::getRadius() const
{
   return radius;

} // end function getRadius

// compute diameter
double threeDCircle::getDiameter() const
{
   return 2 * getRadius();

} // end function getDiameter

// compute circumference
double threeDCircle::getCircumference() const
{
   return 3.14159 * getDiameter();

} // end function getCircumference

// override virtual function getArea: return area of threeDCircle
double threeDCircle::getArea() const
{
   return 3.14159 * getRadius() * getRadius();

} // end function getArea

// override virutual function getName: return name of threeDCircle
string threeDCircle::getName() const
{
   return "Circle";

}  // end function getName

// override virtual function print: output threeDCircle object
void threeDCircle::print() const
{
   cout << "center is ";
   threeDPoint::print();  // invoke Point's print function
   cout << "; radius is " << getRadius();

} // end function print

