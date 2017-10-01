#ifndef ANIMAL_H
#define ANIMAL_H

class Product {
public:
Product(double cost = 0) : price(cost), year_of_birth(0)
{cout << "Product Constructor" << endl;}
~Product() {cout << "Product Destructor" << endl;}
protected:
int price;
int year_of_birth;
};

class Animal {
public:
Animal(int year, bool printp = false) :
year_of_birth(year), print_p(printp)
{if (printp) cout << "Animal Constructor" << endl;}
~Animal()
{if (print_p) cout << "Animal Destructor" << endl;}
int Number() const {return year_of_birth;}
virtual bool WarmUp() const
{cout << "Unknown method" << endl; return false;}
protected:
int year_of_birth;
bool print_p;
};

class Mammal : public Animal {
public:
Mammal(int year, bool printp = false) : Animal(year,
printp)
{if (print_p) cout << "Mammal Constructor" << endl;}
~Mammal()
{if (print_p) cout << "Mammal Destructor" << endl;}
int Number() const {return year_of_birth + 1;}
bool WarmUp() const {cout << "Shiver" << endl; return
true;}
protected:
};

class Quagga : public Mammal {
public:
Quagga(int year1, int year2, bool printp = false)
: Mammal(year1, printp), year_of_death(year2)
{if (print_p) cout << "Quagga Constructor" << endl;}
~Quagga()
{if (print_p) cout << "Quagga Destructor" << endl;}
int Number() const {return year_of_death;}
protected:
int year_of_death;
};

class Fish : public Animal, public Product {
public:
Fish(int year, double price, double depth, bool printp =
false)
: Animal(year, printp), Product(price),
ocean_depth(depth)
{if (print_p) cout << "Fish Constructor" << endl;}
~Fish()
{if (print_p) cout << "Fish Destructor" << endl;}
virtual bool WarmUp() const
{cout << "Swim Up" << endl; return true;}
protected:
int ocean_depth;
};
#endif // ANIMAL_H
