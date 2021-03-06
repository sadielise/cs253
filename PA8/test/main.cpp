// including
#include <iostream>
#include <fstream>
#include "Image.h"
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

int main(int argc, char* argv[])
{
	// check number of args
	if (argc != 3){
		cerr << "ERROR: Incorrect number of arguments." << endl;
		return -1;
	}

	// read first image
	Image image1;
	int test1 = image1.readImage(argv[1]);
	if(test1 < 0){
		return -1;
	}

	cout << image1.getMinPixel() << endl;
	cout << image1.getMedianPixel() << endl;
	cout << image1.getEvenPixels() << endl;
	cout << image1.getUniquePixels() << endl;

	// sort pixels
	image1.sortDescending();

	// create and write image
	Image image2(image1.getWidth(), image1.getHeight(), 2);
	image2.setFilename(argv[2]);
	image2.setPixels(image1.getPixels());
	image2.writeImage();

	return 0;

}
