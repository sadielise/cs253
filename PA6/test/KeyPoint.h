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
	inline vector< vector<int> > getSourceWeights(){return sourceWeights;}
	inline vector< vector<int> > getDestWeights(){return destWeights;}
	inline int getN(){return ((keyPoints[0].size()/2)-2);}

	vector<int> findSource(vector<int> pixel, int j);
	vector<int> findDest(vector<int> pixel, int j);
	void printKeyPoints();
	void printSourceWeights();
	void printDestWeights();
	bool isKeyPoint(vector<int> pixel, int j);
	int readFile(string filename);

protected:
    vector< vector<int> > keyPoints;
	vector< vector<int> > sourceWeights;
	vector< vector<int> > destWeights;

};

#endif
