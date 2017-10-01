#include "Mapping.h"
#include <vector>
#include <math.h>

// using
using namespace std;
using std::string;
using std::cout;
using std::cerr;


vector<int> Mapping::findSourcePixel(vector<int> pixel, int j){

	// temp pixel to be returned
	vector<int> temp;

	// check if pixel is a key point
	if(keypoint.isKeyPoint(pixel, j) == true){
		temp = keypoint.findSource(pixel, j);
	}

	// if not a key point, use math to find the source pixel
	else{
		double sumWeights = getSumOfWeights(pixel, j);
		//cout << "sumWeights: " << sumWeights << endl;
		double sumWeightsX = getSumOfWeightsXS(pixel, j);
		//cout << "sumWeightsX: " << sumWeightsX << endl;
		double sumWeightsY = getSumOfWeightsYS(pixel, j);
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

vector<int> Mapping::findDestPixel(vector<int> pixel, int j){

	// temp pixel to be returned
	vector<int> temp;

	// check if pixel is a key point
	if(keypoint.isKeyPoint(pixel, j) == true){
		temp = keypoint.findDest(pixel, j);
	}

	// if not a key point, use math to find the destination pixel
	else{
		double sumWeights = getSumOfWeights(pixel, j);
		//cout << "sumWeightsD: " << sumWeights << endl;
		double sumWeightsX = getSumOfWeightsXD(pixel, j);
		//cout << "sumWeightsXD: " << sumWeightsX << endl;
		double sumWeightsY = getSumOfWeightsYD(pixel, j);
		//cout << "sumWeightsYD: " << sumWeightsY << endl;
		double tempDeltaX = (sumWeightsX/sumWeights);
		//cout << "tempDeltaXD: " << tempDeltaX << endl;
		double tempDeltaY = (sumWeightsY/sumWeights);
		//cout << "tempDeltaYD: " << tempDeltaY << endl;
		int deltaX = round(tempDeltaX);
		int deltaY = round(tempDeltaY);
		int sourceX = pixel[0] - deltaX;
		int sourceY = pixel[1] - deltaY;
		temp.push_back(sourceX);
		temp.push_back(sourceY);
	}

	return temp;
}

double Mapping::getSumOfWeights(vector<int> pixel, int j){
	double sum = 0.0;
	vector< vector<int> > keyPoints = keypoint.getKeyPoints();
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		double xDiff = pixel[0] - keyPoints[i][2*j];
		double yDiff = pixel[1] - keyPoints[i][2*j+1];
		//cout << "xDiff: " << xDiff << endl;
		//cout << "yDiff: " << yDiff << endl;
		double temp = (1/((pow(xDiff,2)) + (pow(yDiff,2))));
		sum += temp;
	}
	return sum;
}

double Mapping::getSumOfWeightsXS(vector<int> pixel, int j){
	double sum = 0.0;
	vector< vector<int> > sourceWeights = keypoint.getSourceWeights();
	vector< vector<int> > keyPoints = keypoint.getKeyPoints();
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		double xDiff = pixel[0] - keyPoints[i][2*j];
		double yDiff = pixel[1] - keyPoints[i][2*j+1];
		double weight = (1/((pow(xDiff,2)) + (pow(yDiff,2))));
		double xWeight = sourceWeights[i][2*(j-1)];
		sum += (weight * xWeight);
	}
	return sum;
}

double Mapping::getSumOfWeightsXD(vector<int> pixel, int j){
	double sum = 0.0;
	vector< vector<int> > destWeights = keypoint.getDestWeights();
	vector< vector<int> > keyPoints = keypoint.getKeyPoints();
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		double xDiff = pixel[0] - keyPoints[i][2*j];
		double yDiff = pixel[1] - keyPoints[i][2*j+1];
		double weight = (1/((pow(xDiff,2)) + (pow(yDiff,2))));
		double xWeight = destWeights[i][2*(j-1)];
		sum += (weight * xWeight);
	}
	return sum;
}

double Mapping::getSumOfWeightsYS(vector<int> pixel, int j){
	double sum = 0.0;
	vector< vector<int> > sourceWeights = keypoint.getSourceWeights();
	vector< vector<int> > keyPoints = keypoint.getKeyPoints();
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		double xDiff = pixel[0] - keyPoints[i][2*j];
		double yDiff = pixel[1] - keyPoints[i][2*j+1];
		double weight = (1/((pow(xDiff,2)) + (pow(yDiff,2))));
		double yWeight = sourceWeights[i][2*(j-1)+1];
		sum += (weight * yWeight);
	}
	return sum;
}

double Mapping::getSumOfWeightsYD(vector<int> pixel, int j){
	double sum = 0.0;
	vector< vector<int> > destWeights = keypoint.getDestWeights();
	vector< vector<int> > keyPoints = keypoint.getKeyPoints();
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		double xDiff = pixel[0] - keyPoints[i][2*j];
		double yDiff = pixel[1] - keyPoints[i][2*j+1];
		double weight = (1/((pow(xDiff,2)) + (pow(yDiff,2))));
		double yWeight = destWeights[i][2*(j-1)+1];
		sum += (weight * yWeight);
	}
	return sum;
}

