
// threeDCircle class contains x-y-z coordinate triple and radius.
// threeDCircle class inherits from class threeDPoint.

#ifndef THREEDCIRCLE_H
#define THREEDCIRCLE_H

#include "threeDpoint.h"  // threeDPoint class definition

class threeDCircle : public threeDPoint {

public:

   // default constructor
   threeDCircle( int = 0, int = 0, int = 0, double = 0.0 );  

   void setRadius( double );   // set radius
   double getRadius() const;   // return radius

   double getDiameter() const;       // return diameter
   double getCircumference() const;  // return circumference
   virtual double getArea() const;   // return area

   // return name of threeDshape ("Circle")
   virtual string getName() const;

   virtual void print() const;  // output Circle object

private: 
   double radius;  // threeDCircle's radius

}; // end class threeDCircle

#endif 

