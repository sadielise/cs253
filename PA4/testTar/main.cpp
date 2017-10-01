// including
#include <iostream>
#include <fstream>
#include "ModifyImage.h"
#include <stdio.h>
#include <stdlib.h>

// using
using namespace std;
using std::cout;
using std::cerr;
using std::ifstream;

int main(int argc, char* argv[])
{
	// check number of args
	if (argc != 4){
		cerr << "ERROR: Incorrect number of arguments." << endl;
		return -1;
	}

	// create first image
	Image* image1 = new Image();
	// read image
	int read1 = image1->readImage(argv[1]);
	// check for error
	if(read1 < 0){
		return -1;
	}

	// create second image
	Image* image2 = new Image();
	// read image
	int read2 = image2->readImage(argv[2]);
	// check for error
	if(read2 < 0){
		return -1;
	}

	// read integer
	int N;
	if(*argv[3] == '0'){
		N = 0;
	}
	else{
		char* temp = argv[3];
		N = atoi(temp);
		if(N < 1){
			cerr << "ERROR: Third argument is not a valid integer." << endl;
			return -1;
		}
	}

	// create image modifier
	ModifyImage modify;
	// call linear scale
	int scale = modify.linearScale(image1, image2, N);
	// check for error
	if(scale < 0){
		return -1;
	}		

	return 0;

}
