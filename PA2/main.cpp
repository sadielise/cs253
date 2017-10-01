// including
#include <iostream>
#include <fstream>
#include "Image.h"

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

	// check file opening  
	ifstream istr(argv[1]);
	if (istr.fail()){
		cerr << "ERROR: File could not be opened." << endl;
		return -1;
	}

	// create image
	Image pgm;
	// read image
	int read = pgm.readImage(argv[1]);
	// check for error
	if(read < 0){
		return -1;
	}

	// rescale image
	int rescale = pgm.rescaleImage();
	// check for error
	if(rescale < 0){
		return -1;
	}

	// create output file
	ofstream ostr(argv[2]);
	if(ostr.fail()){
		cerr << "ERROR: File could not be created." << endl;
		return -1;
	}
	
	// write image
	int write = pgm.writeImage(argv[2]);
	if(write < 0){
		return -1;
	}
		
	return 0;

}
