
// threeDShape abstract-base-class definition.
#ifndef THREEDSHAPE_H
#define THREEDSHAPE_H

#include <string>  // C++ standard string class

using std::string;

class threeDShape {

public:
   
   // virtual function that returns threeDshape area
   virtual double getArea() const;

   // virtual function that returns threeDshape volume
   virtual double getVolume() const;

   // pure virtual functions; they're overridden in the derived classes threeDPoint, threeDCircle, Sphere
   virtual string getName() const = 0; // return threeDshape name
   virtual void print() const = 0;     // output threeDshape

}; // end class threeDShape

#endif

