
// Shape class member-function definitions.
#include <iostream>  

using std::cout;

#include "threeDshape.h"  // threeDShape class definition

// return area of shape; 0.0 by default, for point it would be zero
double threeDShape::getArea() const
{
   return 0.0;

}  // end function getArea

// return volume of shape; 0.0 by default, for point it would be zero
double threeDShape::getVolume() const
{
   return 0.0;

}  // end function getVolume

