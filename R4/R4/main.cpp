/// File main.cpp
#include <LinkedList.h>
#include <Quagga.h>
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

int Usage(char* argv0)
{
  cerr << "Usage:: call " << argv0 << " with no arguments" << endl;
  return -1;
}

void PrintQuagga(Quagga q)
{
  cout << q.Age() << " ";
}

int main(int argc, char* argv[])
{
  if (argc != 1) return Usage(argv[0]);

  LinkedList* lptr = new LinkedList(1);
  lptr = new LinkedList(2, lptr);
  lptr = new LinkedList(3, lptr);

  LinkedList foo(10, new LinkedList(9));
  foo = *lptr;
  cout << "Linked list output: ";
  foo.Print();
  delete lptr;

  Quagga q1(5);
  cout << "Quagga output: ";
  PrintQuagga(q1);
  q1.Print();

  return 0;
}
