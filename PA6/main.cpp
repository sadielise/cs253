// including
#include <iostream>
#include <fstream>
#include "ModifyImage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <gtest/gtest.h>
#include <vector>

// using
using namespace std;
using std::cout;
using std::cerr;
using std::ifstream;

// Google Tests
namespace{

// test a blank key point file
TEST(KeyPoint1, kp1){
	KeyPoint kp;
	int test = kp.readFile("kp1.txt");
	ASSERT_EQ(-1,test);	
}

// test a decimal in key point file
TEST(KeyPoint2, kp2){
	KeyPoint kp;
	int test = kp.readFile("kp2.txt");
	ASSERT_EQ(-1,test);
}	

// test a blank line in key point file
TEST(KeyPoint3, kp3){
	KeyPoint kp;
	ASSERT_EQ(0, kp.readFile("kp3.txt"));
}

// test unequal number of key points on two different lines
TEST(KeyPoint4, kp4){
	KeyPoint kp;
	int test = kp.readFile("kp4.txt");
	ASSERT_EQ(-1,test);
}

// test < 6 integers on a line
TEST(KeyPoint5, kp5){
	KeyPoint kp;
	int test = kp.readFile("kp5.txt");
	ASSERT_EQ(-1,test);
}

// test uneven number of integers on a line
TEST(KeyPoint6, kp6){
	KeyPoint kp;
	int test = kp.readFile("kp6.txt");
	ASSERT_EQ(-1,test);
}

// test key point vector for correct values
TEST(KeyPoint7, kp7){
	KeyPoint kp;
	ASSERT_EQ(0, kp.readFile("kp7.txt"));
	vector< vector<int> > test = kp.getKeyPoints();
	ASSERT_EQ(1,test[0][0]);
	ASSERT_EQ(2,test[0][1]);
	ASSERT_EQ(3,test[0][2]);
	ASSERT_EQ(4,test[0][3]);
	ASSERT_EQ(5,test[0][4]);
	ASSERT_EQ(6,test[0][5]);
	ASSERT_EQ(7,test[0][6]);
	ASSERT_EQ(8,test[0][7]);
	ASSERT_EQ(3,test[1][0]);
	ASSERT_EQ(6,test[1][1]);
	ASSERT_EQ(9,test[1][2]);
	ASSERT_EQ(12,test[1][3]);
	ASSERT_EQ(15,test[1][4]);
	ASSERT_EQ(18,test[1][5]);
	ASSERT_EQ(21,test[1][6]);
	ASSERT_EQ(24,test[1][7]);
}

// test key point vector for correct N value
TEST(KeyPoint8, kp8){
	KeyPoint kp;
	kp.readFile("kp7.txt");
	ASSERT_EQ(2, kp.getN());
}

// test if valid key point is key point
TEST(KeyPoint9, kp9){
	KeyPoint kp;
	kp.readFile("kp11.txt");
	vector<int> test;
	test.push_back(5);
	test.push_back(6);
	ASSERT_TRUE(kp.isKeyPoint(test, 2));
}

// test if invalid key point throws error
TEST(KeyPoint10, kp10){
	KeyPoint kp;
	kp.readFile("kp7.txt");
	vector<int> test;
	test.push_back(3);
	test.push_back(4);
	ASSERT_FALSE(kp.isKeyPoint(test, 2));
}

// test if key point returns correct source point
TEST(KeyPoint11, kp11){
	KeyPoint kp;
	kp.readFile("kp7.txt");
	vector<int> test;
	test.push_back(5);
	test.push_back(6);
	ASSERT_EQ(1,kp.findSource(test, 2)[0]);
	ASSERT_EQ(2,kp.findSource(test, 2)[1]);
}

// test if key point returns correct destination point
TEST(KeyPoint12, kp12){
	KeyPoint kp;
	kp.readFile("kp7.txt");
	vector<int> test;
	test.push_back(9);
	test.push_back(12);
	ASSERT_EQ(21,kp.findDest(test, 1)[0]);
	ASSERT_EQ(24,kp.findDest(test, 1)[1]);
}


// test if duplicate key point returns error
TEST(KeyPoint13, kp13){
	KeyPoint kp;
	ASSERT_EQ(-1, kp.readFile("kp11.txt"));
}

}


int main(int argc, char* argv[])
{
/*
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
*/

	// check number of args
	if (argc != 4){
		cerr << "ERROR: Incorrect number of arguments." << endl;
		return -1;
	}

	// read first image
	Image image1;
	int test1 = image1.readImage(argv[1]);
	if(test1 < 0){
		return -1;
	}

	// read second image
	Image image2;
	int test2 = image2.readImage(argv[2]);
	if(test2 < 0){
		return -1;
	}

	// read key point file
	KeyPoint kp;
	int test3 = kp.readFile(argv[3]);
	if(test3 < 0){
		return -1;
	}

	// create image modifier and run linear morph
	ModifyImage mi;
	int test4 = mi.linearMorph(image1, image2, kp);
	if(test4 < 0){
		return -1;
	}

	return 0;

}
