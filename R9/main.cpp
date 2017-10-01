// R9 main

// main for creating shape, point, circle, sphere hierarchy of inheritance,
// and for using polymorphism.

// Inheritance hierarchy: threeDShape(abstract class) --> threeDPoint --> threeDCircle --> Sphere

#include <iostream>

using std::cout;
using std::endl;
using std::fixed;

#include <iomanip>
#include <gtest/gtest.h>

using std::setprecision;

#include <vector>

using std::vector;

#include "threeDshape.h"     // threeDShape class definition
#include "threeDpoint.h"     // threeDPoint class definition 
#include "threeDcircle.h"    // threeDCircle class definition 
#include "sphere.h"  // Sphere class definition

namespace{

TEST(Volume, volSphere){
	Sphere s(1,2,3,5.0);
	ASSERT_EQ(523.598,s.getVolume());
}

TEST(Area, areaSphere){
	Sphere s(1,2,3,5.0);
	ASSERT_EQ(314.159,s.getArea());
}

}

void virtualByPointer( const threeDShape * );  
void virtualByReference( const threeDShape & );

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/*
int main()
{


   // set floating-point number format
   cout << fixed << setprecision( 2 );

   threeDPoint point( 3, 5, 0 );                  // create a threeDPoint
   threeDCircle circle( 15, 20, 0, 5.3 );           // create a threeDCircle
   Sphere sphere( 100, 100, 0, 7.7 );  // create a Sphere

   cout << point.getName() << ": ";    // static binding
   point.print();                      // static binding
   cout << '\n';

   cout << circle.getName() << ": ";   // static binding
   circle.print();                     // static binding
   cout << '\n';

   cout << sphere.getName() << ": "; // static binding
   sphere.print();                   // static binding
   cout << "\n\n";

   // create vector of three base-class 3Dpointers
   vector< threeDShape * > threeDshapeVector( 3 );  

   // access threeDshapeVector[0] at derived-class threeDPoint object
   threeDshapeVector[ 0 ] = &point;

   // access threeDshapeVector[1] at derived-class threeDCircle object
   threeDshapeVector[ 1 ] = &circle;

   // accsess threeDshapeVector[2] at derived-class Sphere object
   threeDshapeVector[ 2 ] = &sphere;

   // print the threeDshape name, attributes, area and volume 
   // of each object using dynamic binding
   cout << "\nVirtual function calls "
        << "base-class pointers:\n\n";

   for ( unsigned int i = 0; i < threeDshapeVector.size(); i++ ) 
      virtualByPointer( threeDshapeVector[ i ] );

   // print the threeDshape name, attributes, area and volume 
   // of each object using dynamic binding
   cout << "\nVirtual function calls "
        << "base-class references:\n\n";

   for ( unsigned int j = 0; j < threeDshapeVector.size()-1; j++ ) 
      virtualByReference( *threeDshapeVector[ j ] );

   return 0;

} // end main

*/

// make virtual function calls off a base-class pointer
// using dynamic binding
void virtualByPointer( const threeDShape *baseClassPtr )
{
   cout << baseClassPtr->getName() << ": ";

   baseClassPtr->print();

   cout << "\narea is " << baseClassPtr->getArea()
        << "\nvolume is " << baseClassPtr->getVolume() 
        << "\n\n";

} // end function virtualByPointer

// make virtual function calls off a base-class reference
// using dynamic binding
void virtualByReference( const threeDShape &baseClassRef )
{
   cout << baseClassRef.getName() << ": ";

   baseClassRef.print();

   cout << "\narea is " << baseClassRef.getArea()
        << "\nvolume is " << baseClassRef.getVolume() << "\n\n";

} // end function virtualByReference

