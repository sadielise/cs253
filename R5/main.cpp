#include <iostream>

class Foo
{
    int bar;
  public:
    Foo()
      : bar(42)
    { }

    int getBar() { return bar; }
};

void allocate(Foo** ptr)
{
    *ptr = new Foo;
}

int main()
{
    Foo* ptr = NULL;
    allocate(&ptr);
	//delete &ptr;
	delete ptr;

    //std::cout << ptr->getBar() << std::endl;
}
