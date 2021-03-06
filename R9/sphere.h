// Recitation: Inheritance & Polymorphism
// Author: Fereydoon
// Date: March 22, 2015

// Sphere class inherits from class threeDCircle.

#ifndef SPHERE_H
#define SPHERE_H

#include "threeDcircle.h"  // threeDCircle class definition


class Sphere : public threeDCircle {

public:

   // default constructor
   Sphere( int = 0, int = 0, int = 0, double = 0.0 ); 
   
   virtual double getArea() const;
   virtual double getVolume() const;

   // return ("Sphere")
   virtual string getName() const;

   virtual void print() const;  // output Sphere

}; // end class Sphere

#endif
