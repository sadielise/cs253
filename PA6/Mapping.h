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
	vector<int> findSourcePixel(vector<int> pixel, int j);
	vector<int> findDestPixel(vector<int>pixel, int j);
	double getSumOfWeights(vector<int> pixel, int j);
	double getSumOfWeightsXS(vector<int> pixel, int j);
	double getSumOfWeightsXD(vector<int> pixel, int j);
	double getSumOfWeightsYS(vector<int> pixel, int j);
	double getSumOfWeightsYD(vector<int> pixel, int j);

protected:
	KeyPoint keypoint;

};

#endif
