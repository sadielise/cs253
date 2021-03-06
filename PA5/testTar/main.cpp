// including
#include <iostream>
#include <fstream>
#include "Morpher.h"
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
	int test = kp.readFile("kp3.txt");
	ASSERT_EQ(0,test);
}

// test 2 key points with the same destination
TEST(KeyPoint4, kp4){
	KeyPoint kp;
	int test = kp.readFile("kp4.txt");
	ASSERT_EQ(-1,test);
}

// test > 4 integers on a line
TEST(KeyPoint5, kp5){
	KeyPoint kp;
	int test = kp.readFile("kp5.txt");
	ASSERT_EQ(-1,test);
}

// test < 4 integers on a line
TEST(KeyPoint6, kp6){
	KeyPoint kp;
	int test = kp.readFile("kp6.txt");
	ASSERT_EQ(-1,test);
}

// test key point vector for correct values
TEST(KeyPoint7, kp7){
	KeyPoint kp;
	kp.readFile("kp7.txt");
	vector< vector<int> > test = kp.getKeyPoints();
	ASSERT_EQ(1,test[0][0]);
	ASSERT_EQ(2,test[0][1]);
	ASSERT_EQ(3,test[0][2]);
	ASSERT_EQ(4,test[0][3]);
	ASSERT_EQ(5,test[1][0]);
	ASSERT_EQ(7,test[1][1]);
	ASSERT_EQ(9,test[1][2]);
	ASSERT_EQ(12,test[1][3]);
}

// test key point vector for correct weights
TEST(KeyPoint8, kp8){
	KeyPoint kp;
	kp.readFile("kp7.txt");
	ASSERT_EQ(2,kp.getWeights()[0][0]);
	ASSERT_EQ(2,kp.getWeights()[0][1]);
	ASSERT_EQ(4,kp.getWeights()[1][0]);
	ASSERT_EQ(5,kp.getWeights()[1][1]);	
}

// test if valid key point is key point
TEST(KeyPoint9, kp9){
	KeyPoint kp;
	kp.readFile("kp7.txt");
	vector<int> test;
	test.push_back(9);
	test.push_back(12);
	ASSERT_TRUE(kp.isKeyPoint(test));
}

// test if invalid key point throws error
TEST(KeyPoint10, kp10){
	KeyPoint kp;
	kp.readFile("kp7.txt");
	vector<int> test;
	test.push_back(5);
	test.push_back(7);
	ASSERT_FALSE(kp.isKeyPoint(test));
}

// test if key point returns correct source point
TEST(KeyPoint11, kp11){
	KeyPoint kp;
	kp.readFile("kp7.txt");
	vector<int> test;
	test.push_back(9);
	test.push_back(12);
	ASSERT_EQ(5,kp.findSource(test)[0]);
	ASSERT_EQ(7,kp.findSource(test)[1]);
}

// test if Mapping returns key point source point
TEST(Mapping1, map1){
	Mapping mp("kp7.txt");
	vector<int> test;
	test.push_back(3);
	test.push_back(4);
	ASSERT_EQ(1,mp.findSourcePixel(test)[0]);
	ASSERT_EQ(2,mp.findSourcePixel(test)[1]);
}

// test if Mapping returns correct source point w/ 2 key points
TEST(Mapping2, map2){
	Mapping mp("kp8.txt");
	vector<int> test;
	test.push_back(6);
	test.push_back(7);
	ASSERT_EQ(3,mp.findSourcePixel(test)[0]);
	ASSERT_EQ(6,mp.findSourcePixel(test)[1]);
}

// test if Mapping returns correct source point w/ 2 key points that don't move
TEST(Mapping3, map3){
	Mapping mp("kp9.txt");
	vector<int> test;
	test.push_back(6);
	test.push_back(7);
	ASSERT_EQ(6,mp.findSourcePixel(test)[0]);
	ASSERT_EQ(7,mp.findSourcePixel(test)[1]);
}

// test if Mapping returns correct source point w/ key point that shifts right by 1
TEST(Mapping4, map4){
	Mapping mp("kp10.txt");
	vector<int> test;
	test.push_back(3);
	test.push_back(3);
	ASSERT_EQ(2,mp.findSourcePixel(test)[0]);
	ASSERT_EQ(3,mp.findSourcePixel(test)[1]);
}

// test if Mapping returns correct source point that is off of the image
TEST(Mapping5, map5){
	Mapping mp("kp10.txt");
	vector<int> test;
	test.push_back(0);
	test.push_back(2);
	ASSERT_EQ(-1,mp.findSourcePixel(test)[0]);
	ASSERT_EQ(2,mp.findSourcePixel(test)[1]);
}

// test Morpher with 2x2 ASCII image and 1 key point that doesn't move
TEST(Morpher1, morph1){
	Image image1;
	image1.readImage("image1.pgm");

	Image image2;
	// check file extension
	string filename = "image1.pgma";
	if(filename.substr((filename.length()-5),(filename.length()-1)) == ".pgma"){
		image2.setType(2);
		image2.setFilename(filename);
	}
	else if(filename.substr((filename.length()-4),(filename.length()-1)) == ".pgm"){
		image2.setType(5);
		image2.setFilename(filename);
	}
	else{
		cerr << "ERROR: Output file name is incorrect." << endl;
	}

	// set width and height
	image2.setWidth(image1.getWidth());
	image2.setHeight(image1.getHeight());

	// create morpher
	Morpher mp("morph1.txt");
	mp.morphImage(image1, image2);

	ASSERT_EQ(3,image2.getPixel(0,0));
	ASSERT_EQ(4,image2.getPixel(1,0));
	ASSERT_EQ(5,image2.getPixel(0,1));
	ASSERT_EQ(6,image2.getPixel(1,1));
}

// test Morpher with 2x2 ASCII image and 1 key points that shifts down by 1
TEST(Morpher2, morph1){
	Image image1;
	image1.readImage("image1.pgm");

	Image image2;
	// check file extension
	string filename = "image2.pgma";
	if(filename.substr((filename.length()-5),(filename.length()-1)) == ".pgma"){
		image2.setType(2);
		image2.setFilename(filename);
	}
	else if(filename.substr((filename.length()-4),(filename.length()-1)) == ".pgm"){
		image2.setType(5);
		image2.setFilename(filename);
	}
	else{
		cerr << "ERROR: Output file name is incorrect." << endl;
	}

	// set width and height
	image2.setWidth(image1.getWidth());
	image2.setHeight(image1.getHeight());

	// create morpher
	Morpher mp("morph2.txt");
	mp.morphImage(image1, image2);

	ASSERT_EQ(0,image2.getPixel(0,0));
	ASSERT_EQ(0,image2.getPixel(1,0));
	ASSERT_EQ(3,image2.getPixel(0,1));
	ASSERT_EQ(4,image2.getPixel(1,1));
}

// test Morpher with 2x2 ASCII image where every point is a key p and the image rotates clockwise
TEST(Morpher3, morph3){
	Image image1;
	image1.readImage("image1.pgm");

	Image image2;
	// check file extension
	string filename = "image3.pgma";
	if(filename.substr((filename.length()-5),(filename.length()-1)) == ".pgma"){
		image2.setType(2);
		image2.setFilename(filename);
	}
	else if(filename.substr((filename.length()-4),(filename.length()-1)) == ".pgm"){
		image2.setType(5);
		image2.setFilename(filename);
	}
	else{
		cerr << "ERROR: Output file name is incorrect." << endl;
	}

	// set width and height
	image2.setWidth(image1.getWidth());
	image2.setHeight(image1.getHeight());

	// create morpher
	Morpher mp("morph3.txt");
	mp.morphImage(image1, image2);

	ASSERT_EQ(5,image2.getPixel(0,0));
	ASSERT_EQ(3,image2.getPixel(1,0));
	ASSERT_EQ(6,image2.getPixel(0,1));
	ASSERT_EQ(4,image2.getPixel(1,1));
}

// test read of image that isn't binary or ASCII
TEST(Morpher4, morph4){
	Image image1;
	ASSERT_EQ(-1,image1.readImage("image2.pgm"));
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

	// create read image
	Image image1;
	// read image
	int read1 = image1.readImage(argv[1]);
	// check for error
	if(read1 < 0)
		return -1;

	// create write image
	Image image2;
	// check file extension
	string filename = argv[3];
	if(filename.substr((filename.length()-5),(filename.length()-1)) == ".pgma"){
		image2.setType(2);
		image2.setFilename(argv[3]);
	}
	else if(filename.substr((filename.length()-4),(filename.length()-1)) == ".pgm"){
		image2.setType(5);
		image2.setFilename(argv[3]);
	}
	else{
		cerr << "ERROR: Output file name is incorrect." << endl;
		return -1;
	}
	// set width and height
	image2.setWidth(image1.getWidth());
	image2.setHeight(image1.getHeight());

	// create morpher and morph image
	Morpher mp(argv[2]);
	mp.morphImage(image1, image2);

	return 0;

}
