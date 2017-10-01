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

// prints source weight vector
void KeyPoint::printSourceWeights(){
	for(unsigned int i = 0; i < sourceWeights.size(); i++){
		for(unsigned int j = 0; j < (sourceWeights[0].size()/2); j++){
			cout << sourceWeights[i][2*j] << "," << sourceWeights[i][2*j+1] << endl;
		}
	}
}

// print dest weight vector
void KeyPoint::printDestWeights(){
	for(unsigned int i = 0; i < destWeights.size(); i++){
		for(unsigned int j = 0; j < (destWeights[0].size()/2); j++){
			cout << destWeights[i][2*j] << "," << destWeights[i][2*j+1] << endl;
		}
	}
}

// returns row index of key point pixel if key point exists, else returns NULL
int KeyPoint::isKeyPoint(vector<int>& pixel, int j){

	// loop through key point vector and return row number if found
	for(unsigned int i = 0; i < keyPoints.size(); i++){
		if((pixel[0] == keyPoints[i][2*j]) && (pixel[1] == keyPoints[i][2*j+1])){
			return i;
		}
	}	
	return -1;
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
	int lineLength = 0;
	while(!istr.eof()){
		string line;
		getline(istr, line);
		// check for empty file
		if(line.empty()){
			if(lineNumber == 0){
				cerr << "ERROR: Key point file is empty." << endl;
				return -1;
			}
			else{
				return 0;
			}
		}


		// read each line individually
		stringstream ss;
		ss << line;
		if(ss.fail()){
			cerr << "ERROR: Unable to read line in key point file." << endl;
			return -1;
		}
		// temp vector read values into
		vector<int> tempVector;

		// if this is the first line, read values and keep track of length
		if(lineNumber == 0){
			// read in all values, making sure they are integers
			while(!ss.eof()){
				double temp;
				ss >> temp;
/*				if(ss.fail() || (floor(temp) != temp)){
					cerr << "ERROR: Invalid value in key point file." << endl;
					cerr << "Line number: " << lineNumber << endl;
					return -1;
				}*/

				int value = (int)temp;
				tempVector.push_back(value);
				lineLength++;				
			}		
			
			// make sure that the length is at least 6 (source, intermediate, destination)
			// and divisible by 2
/*			if((lineLength < 6) || ((lineLength % 2) != 0)){
				cerr << "ERROR: First line of key point file has invalid number of integers." << endl;
				return -1;
			}*/
		
		}

		// otherwise, read in line and compare with length of first line
		else{
			for(int i = 0; i < lineLength; i++){
				int value;
				ss >> value;
/*				if(ss.fail()){
					cerr << "ERROR: Invalid value in key point file." << endl;
					return -1;
				}*/

				tempVector.push_back(value);
			}
		
/*			// check for additional/invalid characters
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
			}*/

		}

		// compute source and destination weights of key points
		vector<int> tempSourceWeights;
		vector<int> tempDestWeights;
		for(int i = 1; i <= ((lineLength-4)/2); i++){
/*			if(lineNumber > 0){
				vector<int> tempPixel;
				tempPixel.push_back(tempVector[2*i]);
				tempPixel.push_back(tempVector[2*i+1]);
				if(isKeyPoint(tempPixel, i) != -1){
					cerr << "ERROR: Duplicate key point." << endl;
					return -1;
				}
			}
*/

			tempSourceWeights.push_back(tempVector[2*i] - tempVector[0]);
			tempSourceWeights.push_back(tempVector[2*i+1] - tempVector[1]);
			tempDestWeights.push_back(tempVector[2*i] - tempVector[lineLength-2]);
			tempDestWeights.push_back(tempVector[2*i+1] - tempVector[lineLength-1]);
		}
		// add weight to weights vectors
		sourceWeights.push_back(tempSourceWeights);
		destWeights.push_back(tempDestWeights);

		// add key point to keyPoints vector
		keyPoints.push_back(tempVector);

		lineNumber++;
	}
	return 0;
}
