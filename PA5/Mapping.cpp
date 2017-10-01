#include "Mapping.h"
#include <vector>
#include <math.h>

// using
using namespace std;
using std::string;
using std::cout;
using std::cerr;


vector<int> Mapping::findSourcePixel(vector<int> pixel){
	vector<int> temp;

	// check if pixel is a key point
	if(kp.isKeyPoint(pixel) == true){
		return kp.findSource(pixel);
	}

	// if not a key point, use math to find the source
	else{
		double sumWeights = getSumOfWeights(pixel);
		//cout << "sumWeights: " << sumWeights << endl;
		double sumWeightsX = getSumOfWeightsX(pixel);
		//cout << "sumWeightsX: " << sumWeightsX << endl;
		double sumWeightsY = getSumOfWeightsY(pixel);
		//cout << "sumWeightsY: " << sumWeightsY << endl;
		double tempDeltaX = (sumWeightsX/sumWeights);
		//cout << "tempDeltaX: " << tempDeltaX << endl;
		double tempDeltaY = (sumWeightsY/sumWeights);
		//cout << "tempDeltaY: " << tempDeltaY << endl;
		int deltaX = round(tempDeltaX);
		int deltaY = round(tempDeltaY);
		int sourceX = pixel[0] - deltaX;
		int sourceY = pixel[1] - deltaY;
		temp.push_back(sourceX);
		temp.push_back(sourceY);
	}

	return temp;
}


double Mapping::getSumOfWeights(vector<int> pixel){
	double sum = 0.0;
	vector< vector<int> > keyPoints = kp.getKeyPoints();
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		double xDiff = pixel[0] - keyPoints[i][2];
		double yDiff = pixel[1] - keyPoints[i][3];
		//cout << "xDiff: " << xDiff << endl;
		//cout << "yDiff: " << yDiff << endl;
		double temp = (1/((pow(xDiff,2)) + (pow(yDiff,2))));
		//cout << "temp: " << temp << endl;
		sum += temp;
	}
	return sum;
}

double Mapping::getSumOfWeightsX(vector<int> pixel){
	double sum = 0.0;
	vector< vector<int> > weights = kp.getWeights();
	vector< vector<int> > keyPoints = kp.getKeyPoints();
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		double xDiff = pixel[0] - keyPoints[i][2];
		double yDiff = pixel[1] - keyPoints[i][3];
		double weight = (1/((pow(xDiff,2)) + (pow(yDiff,2))));
		double xWeight = weights[i][0];
		sum += (weight * xWeight);
	}
	return sum;
}

double Mapping::getSumOfWeightsY(vector<int> pixel){
	double sum = 0.0;
	vector< vector<int> > weights = kp.getWeights();
	vector< vector<int> > keyPoints = kp.getKeyPoints();
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		double xDiff = pixel[0] - keyPoints[i][2];
		double yDiff = pixel[1] - keyPoints[i][3];
		double weight = (1/((pow(xDiff,2)) + (pow(yDiff,2))));
		double yWeight = weights[i][1];
		sum += (weight * yWeight);
	}
	return sum;
}

