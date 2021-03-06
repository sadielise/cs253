#ifndef MORPHER_H
#define MORPHER_H

// including
#include "Mapping.h"
#include "Image.h"
#include <vector>
#include <math.h>

// using
using namespace std;
using std::string;
using std::cout;
using std::cerr;

class Morpher{

public:
	Morpher(KeyPoint& kp){
		keypoint = kp;
	}

	int morphImage(Image& image1, Image& image2, int j);

protected:
	KeyPoint keypoint;
};

#endif
