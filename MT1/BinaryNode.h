// BinaryNode.h

#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include <LadyBug.h>
#include <string>
using std::string;

class BinaryNode {
public:
  BinaryNode(LadyBug* lbptr) : bug(lbptr), left(NULL), right(NULL) {}
  ~BinaryNode();
  BinaryNode(const BinaryNode& bn);
  BinaryNode& operator = (const BinaryNode& bn);

  bool Insert(LadyBug* ptr);
  BinaryNode* Find(LadyBug* ptr);
  bool Remove(LadyBug* ptr);
  void Print() const;

protected:
  LadyBug* bug;
  BinaryNode* left;
  BinaryNode* right;
};
#endif // BINARY_NODE_H
