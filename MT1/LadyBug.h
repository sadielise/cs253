// LadyBug.h 
#ifndef LADY_BUG_H
#define LADY_BUG_H

#include <iostream>
using std::cout;
using std::endl;

class LadyBug {
public:
  LadyBug() : spot_count(-1) {}
  LadyBug(int spots) { spot_count = spots; }
  ~LadyBug() {if (spot_count >= 0) for(int i=0; i < spot_count; i++) cout << "*";}
  
  inline int Spots() const {return 2*spot_count;}
  inline int Spots() {return spot_count;}
  
 protected:
  int spot_count;
};

#endif // LADY_BUG_H
