#include <BinaryNode.h>
#include <LadyBug.h>
#include <iostream>

using std::cout;

int main(int argc, char* argv[])
{

	LadyBug* lb = new LadyBug(5);
	LadyBug* lb1 = new LadyBug(2);
	LadyBug* lb2 = new LadyBug(6);
	LadyBug* lb3 = new LadyBug(7);

	BinaryNode* bn = new BinaryNode(lb);
	bn->Insert(lb1);
	bn->Insert(lb2);
	bn->Insert(lb3);
	bn->Print();
	//bn->Remove(lb1);
	cout << endl;
	delete bn;

	return 0;
}
