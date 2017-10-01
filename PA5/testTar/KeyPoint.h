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
	inline vector< vector<int> > getWeights(){return weights;}

	vector<int> findSource(vector<int> pixel);
	void printKeyPoints();
	void printWeights();
	bool isKeyPoint(vector<int> pixel);
	int readFile(string filename);

protected:
    vector< vector<int> > keyPoints;
	vector< vector<int> > weights;

};
