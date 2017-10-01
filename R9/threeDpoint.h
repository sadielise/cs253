
// threeDPoint class definition represents an x-y-z coordinate triple.
// threeDPoint class inherits from class threeDShape.

#ifndef THREEDPOINT_H
#define THREEDPOINT_H

#include "threeDshape.h"  // threeDShape class definition

class threeDPoint : public threeDShape {

public:
   threeDPoint( int = 0, int = 0, int = 0 ); // default constructor

   void setX( int );  // set x in coordinate triple
   int getX() const;  // return x from coordinate triple
   
   void setY( int );  // set y in coordinate triple
   int getY() const;  // return y from coordinate triple

   void setZ( int );  // set z in coordinate triple
   int getZ() const;  // return Z from coordinate triple
   
   // return name of shape (i.e., "Point" )
   virtual string getName() const;

   virtual void print() const;  // output Point object

private: 
   int x;  // x part of coordinate triple
   int y;  // y part of coordinate triple
   int z;  // z part of coordinate triple

}; // end class threeDPoint

#endif

