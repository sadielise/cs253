// BinaryNode.cpp (page 1)
#include <BinaryNode.h>

BinaryNode::~BinaryNode()
{
  if(left){
	delete left;
	left = NULL;
  }
  if(right){
    delete right;
    right = NULL;
  }
  if(bug){
	delete bug;
	bug = NULL;
  }
}

BinaryNode::BinaryNode(const BinaryNode& bn)
{

	bug = new LadyBug(bn.bug->Spots());
	left = new BinaryNode(bn.left->bug);
	right = new BinaryNode(bn.right->bug);

}

BinaryNode& BinaryNode::operator = (const BinaryNode& bn)
{
	delete bug;
	delete left;
	delete right;
	bug = new LadyBug(bn.bug->Spots());
	left = new BinaryNode(bn.left->bug);
	right = new BinaryNode(bn.right->bug);
	return *this;	
}

bool BinaryNode::Insert(LadyBug* new_bug)
{
  if (new_bug->Spots() > bug->Spots()) {
    if (right == NULL) {
      right = new BinaryNode(new_bug);
      return true;
    }
    else return right->Insert(new_bug);
  }
  if (new_bug->Spots() < bug->Spots()) {
    if (left == NULL) {
      left = new BinaryNode(new_bug);
      return true;
    }
    else return left->Insert(new_bug);
  }
  return false;
}

BinaryNode* BinaryNode::Find(LadyBug* new_bug)
{
  if (new_bug->Spots() > bug->Spots()) {
    if (right == NULL) return NULL;
    else return right->Find(new_bug);
  }
  if (new_bug->Spots() < bug->Spots()) {
    if (left == NULL) return NULL;
    else return left->Find(new_bug);
  }
  return this;
}

// BinaryNode.cpp (page 2)

bool BinaryNode::Remove(LadyBug* old_bug)
{
  BinaryNode* node = Find(old_bug);
  if (node == NULL) return false;
  delete node;
  node = NULL;
  return true;
}

void BinaryNode::Print() const
{
  if (left != NULL) left->Print();
  cout << bug->Spots() << endl;
  if (right != NULL) right->Print();
}
