#include <iostream>
#include <gtest/gtest.h>
#include "matrix.h"
#include <tuple>

using namespace std;

namespace{

TEST(MatrixTest1, CheckIfMultipliedTrue){
	Matrix m(3,3);
	Matrix n(3,3);
	ASSERT_TRUE(m.mulPossible(n));	
}

TEST(MatrixTest2, CheckIfMultipliedFalse){
	Matrix m(2,3);
	Matrix n(4,4);
	ASSERT_FALSE(m.mulPossible(n));
}

TEST(MatrixTest3, CheckIfMultipliedCorrect){
	tuple<int,int,string> t (2,3,"1 2 3 4 5 6");
	Matrix m(t);
	tuple<int,int,string> s (3,2,"7 8 9 10 11 12");
	Matrix n(s);
	tuple<int,int,string> u (2,2,"58 64 139 154");
	Matrix o(u);
	Matrix p = m*n;
	ASSERT_TRUE(o==p);
}

TEST(MatrixTest4, CreateHeapData){
	Matrix* m = new Matrix(2,3);
	cout << *m;
}


}

int main(int argc, char* argv[])
{

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}

