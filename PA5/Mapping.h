#include "KeyPoint.h"
#include <vector>

class Mapping{

public:
	Mapping(string kpFile){
		kp.readFile(kpFile);
	}
	vector<int> findSourcePixel(vector<int> pixel);
	double getSumOfWeights(vector<int> pixel);
	double getSumOfWeightsX(vector<int> pixel);
	double getSumOfWeightsY(vector<int> pixel);

protected:
	KeyPoint kp;

};
