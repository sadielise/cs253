// Author: Fereydoon
// Date: March 29, 2015

// Sphere class inherits from class threeDCircle.

#include <iostream>
#include <math.h>
using std::cout;

#include "sphere.h"   // Sphere class definition

// default constructor
Sphere::Sphere( int xValue, int yValue, int zValue, double radiusValue) 
  : threeDCircle( xValue, yValue, zValue, radiusValue )
{

} // end Sphere constructor

// override virtual function getArea: return Sphere area
double Sphere::getArea() const{
	return 4*3.14159*(pow(getRadius(),2));
}
// end function getArea

// override virtual function getVolume: return Sphere volume
double Sphere::getVolume() const{
	return ((4.0/3.0)*3.14159*(pow(getRadius(),3)));
}
// end function getVolume

// override virtual function getName: return name of Sphere
string Sphere::getName() const
{
   return "Sphere";

}  // end function getName

// override virtual function print: output Sphere object
void Sphere::print() const
{
   threeDCircle::print();  // code reuse

} // end function print

