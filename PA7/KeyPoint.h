#ifndef KEYPOINT_H
#define KEYPOINT_H

// including
#include <istream>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>

// using
using namespace std;
using std::ifstream;
using std::string;
using std::cout;
using std::cerr;

class KeyPoint{

public:

	KeyPoint(){

	}

	inline vector< vector<int> > getKeyPoints(){return keyPoints;}
	inline vector<int> getKeyPointsAt(int i){return keyPoints[i];}
	inline int getKeyPointsAt(int i, int j){return keyPoints[i][j];}
	inline int getKeyPointsSize(){return keyPoints.size();}
	inline vector< vector<int> > getSourceWeights(){return sourceWeights;}
	inline vector<int> getSourceWeightsAt(int i){return sourceWeights[i];}
	inline int getSourceWeightsAt(int i, int j){return sourceWeights[i][j];}
	inline vector< vector<int> > getDestWeights(){return destWeights;}
	inline vector<int> getDestWeightsAt(int i){return destWeights[i];}
	inline int getDestWeightsAt(int i, int j){return destWeights[i][j];}
	inline int getN(){return ((keyPoints[0].size()/2)-2);}

	void printKeyPoints();
	void printSourceWeights();
	void printDestWeights();
	int isKeyPoint(vector<int>& pixel, int j);
	int readFile(string filename);

protected:
    vector< vector<int> > keyPoints;
	vector< vector<int> > sourceWeights;
	vector< vector<int> > destWeights;

};

#endif
