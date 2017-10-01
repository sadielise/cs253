/// File LinkedList.cpp
#include <LinkedList.h>
#include <iostream>
using std::cout;

LinkedList::LinkedList(int init_value)
{
  value = init_value;
  ptr = NULL;
}

LinkedList::LinkedList(int init_value, LinkedList* lptr)
{
  value = init_value;
  ptr = lptr;
}

LinkedList::LinkedList(const LinkedList& llist)
{
  value = llist.value;
  if (llist.ptr == NULL) ptr = NULL;
  else ptr = new LinkedList(*llist.ptr);
}

LinkedList::~LinkedList()
{
  delete ptr;
  ptr = NULL;
}

LinkedList& LinkedList::operator= (LinkedList& llist)
{
  value = llist.value;
  if (llist.ptr == NULL) ptr = NULL;
  else ptr = new LinkedList(*llist.ptr);
  return *this;
}

void LinkedList::Print() const
{
  cout << value << " ";
  if (ptr == NULL) cout << endl;
  else ptr->Print();
}
