#ifndef MAPPING_H
#define MAPPING_H

// including
#include "KeyPoint.h"
#include <vector>

class Mapping{

public:
	Mapping(KeyPoint& kp){
		keypoint = kp;
	}

	inline vector<int> getSourcePixel(){return sourcePixel;}
	inline vector<int> getDestPixel(){return destPixel;}
	void findPixels(vector<int>& pixel, int j);
	void getSumOfWeights(vector<int>& pixel, int j);

protected:
	KeyPoint keypoint;
	double sumOfWeights;
	double sumOfWeightsXS;
	double sumOfWeightsXD;
	double sumOfWeightsYS;
	double sumOfWeightsYD;
	vector<int> sourcePixel;
	vector<int> destPixel;

};

#endif
