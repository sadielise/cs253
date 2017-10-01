/// File LinkedList.h
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class LinkedList {
public:
  LinkedList(int init_value = 0);
  LinkedList(int init_value, LinkedList* init_ptr);
  LinkedList(const LinkedList& llist);
  ~LinkedList();

  LinkedList& operator = (LinkedList& llist);

  inline int Value() const {return value;}
  inline int& Value() {return value;}
  void Print() const;

protected:
  int value;
  LinkedList* ptr;
};

#endif // LINKED_LIST+H
