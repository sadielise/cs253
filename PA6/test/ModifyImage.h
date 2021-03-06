#ifndef MODIFYIMAGE_H
#define MODIFYIMAGE_H

// including
#include <istream>
#include <fstream>
#include <iostream>
#include <string.h>
#include "Morpher.h"

// using
using namespace std;
using std::istream;
using std::string;
using std::cout;
using std::cerr;

class ModifyImage
{

public:	

	// constructor and overloads
	ModifyImage(){
		
	}

	// functions
	int linearMorph(Image& image1, Image& image2, KeyPoint& kp);
	int linearScale(Image& image1, Image& image2, int N);
	int linearScaling(Image& image1, Image& image2, int j, int N);
	int rescaleImage(Image& image);

protected:

};

#endif

