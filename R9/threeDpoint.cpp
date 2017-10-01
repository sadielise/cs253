
// threeDPoint class member-function definitions.
// threeDPoint class inherits from class threeDShape.

#include <iostream>

using std::cout;

#include "threeDpoint.h"   // threeDPoint class definition

// default constructor
threeDPoint::threeDPoint( int xValue, int yValue, int zValue )
   : x( xValue ), y( yValue ), z( zValue )
{
   // empty body 

} // end threeDPoint constructor

// set x in coordinate triple
void threeDPoint::setX( int xValue )
{
   x = xValue;

} // end function setX

// return x from coordinate triple
int threeDPoint::getX() const
{
   return x;

} // end function getX

// set y in coordinate triple
void threeDPoint::setY( int yValue )
{
   y = yValue;

} // end function setY

// return y from coordinate triple
int threeDPoint::getY() const
{
   return y;

} // end function getY

// set z in coordinate triple
void threeDPoint::setZ( int zValue )
{
   z = zValue; // no need for validation

} // end function setZ

// return z from coordinate triple
int threeDPoint::getZ() const
{
   return z;

} // end function getZ

// override pure virtual function getName: return name of threeDPoint
string threeDPoint::getName() const
{
   return "Point";

}  // end function getName

// override pure virtual function print: output threeDPoint object
void threeDPoint::print() const
{
   cout << '[' << getX() << ", " << getY() << ", " << getZ() << ']';

} // end function print

