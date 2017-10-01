// File Quagga.h
#ifndef QUAGGA_H
#define QUAGGA_H
#include<iostream>
using std::cout;
using std::endl;

class Quagga {
public:
  Quagga(int init_age) {age = init_age;}
  Quagga(const Quagga& src) {age = src.age + 1;}

  inline int Age() const {return age;}
  void Print() {cout << age << " ";}

protected:
  int age;
};

#endif // QUAGGA_H
