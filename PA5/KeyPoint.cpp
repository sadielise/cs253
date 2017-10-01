// including
#include "KeyPoint.h"
#include <istream>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include <math.h>

// using
using namespace std;
using std::ifstream;
using std::string;
using std::cout;
using std::cerr;

// returns source pixel for a key point pixel
vector<int> KeyPoint::findSource(vector<int> pixel){
	vector<int> temp;
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		if((pixel[0] == keyPoints[i][2]) && (pixel[1] == keyPoints[i][3])){
			temp.push_back(keyPoints[i][0]);
			temp.push_back(keyPoints[i][1]);
			return temp;
		}
	}
	return temp;
}

// prints key point vector
void KeyPoint::printKeyPoints(){
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		cout << "Line " << i << ": ";
		for(unsigned int j = 0; j < keyPoints[i].size(); j++){
			cout << keyPoints[i][j] << " ";
		}
		cout << endl;
	}
}

// prints weight vector
void KeyPoint::printWeights(){
	for(unsigned int i = 0; i < weights.size(); i++){
		cout << weights[i][0] << "," << weights[i][1] << endl;
	}
}

// test if a key point is valid
bool KeyPoint::isKeyPoint(vector<int> pixel){
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		if((pixel[0] == keyPoints[i][2]) && (pixel[1] == keyPoints[i][3])){
			return true;
		}
	}	
	return false;
}

// reads key point file, populates key point vector and weight vector
int KeyPoint::readFile(string filename)
{
	// convert filename to a c string
	char cstring[100];	
	strcpy(cstring, filename.c_str());

	// create file input stream
	ifstream istr;
	istr.open(cstring, ifstream::in);
	// check for error
	if(istr.fail()){
		cerr << "ERROR: Can't open key point file for reading." << endl;
		return -1;
	}

	// read values
	int lineNumber = 0;
	while(!istr.eof()){
		string line;
		getline(istr, line);
		if(line.empty()){
			if(lineNumber == 0){
				cerr << "ERROR: Key point file is empty." << endl;
				return -1;
			}
			else{
				return 0;
			}
		}

		stringstream ss;
		ss << line;
		if(ss.fail()){
			cerr << "ERROR: Unable to read line in key point file. File may be empty." << endl;
			return -1;
		}
		vector<int> tempVector;
		for(unsigned int i = 0; i < 4; i++){
			int value;
			ss >> value;
			if(ss.fail()){
				cerr << "ERROR: Invalid value in key point file." << endl;
				return -1;
			}
			tempVector.push_back(value);
		}

		// check for additional/invalid characters
		int test;
		ss >> test;
		if(!ss.fail()){
			cerr << "ERROR: Too many integers in key point file." << endl;
			return -1;
		}
		else if(ss.fail()){
			if(!ss.eof()){
				cerr << "ERROR: Invalid character in key point file." << endl;
				return -1;
			}
		}

		// check to see if key point destination has already been used
		if(keyPoints.size() != 0){
			vector<int> temp;
			temp.push_back(tempVector[2]);
			temp.push_back(tempVector[3]);
			if(isKeyPoint(temp)){
				cerr << "ERROR: Duplicate key point." << endl;
				return -1;
			}
		}

		// add key point to keyPoints vector
		keyPoints.push_back(tempVector);

		// compute weight of key point
		vector<int> weight;
		weight.push_back(tempVector[2] - tempVector[0]);
		weight.push_back(tempVector[3] - tempVector[1]);
		// add weight to weights vector
		weights.push_back(weight);

		lineNumber++;
	}

	return 0;

}
