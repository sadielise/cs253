// including
#include <istream>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <cmath>

// using
using namespace std;
using std::istream;
using std::string;
using std::cout;
using std::cerr;

class Image
{
private:

public:	

	// constructor
	Image(){
	}

	// getters and setters
	int getType();
	void setType(int t);
	int getWidth();
	void setWidth(int w);
	int getHeight();
	void setHeight(int h);
	int getDeclaredMax();
	void setDeclaredMax(int d);
	int getMin();
	void setMin(int mi);
	int getMax();
	void setMax(int ma);
	double getAverage();
	void setAverage(double ave);
	vector<int>& getPixels();
	void addPixel(int p);

	// functions
	int checkForComment(ifstream& input);
	int checkMagicNumber(ifstream& input);
	int getFourBytes(ifstream& input);
	int getValue(ifstream& input);
	int readBinaryPixels(ifstream &input);
	int readPixels(ifstream& input);
	void printPixels(vector<int>& pixels) const;
	int readBinaryImage(ifstream& bistr);
	int readAsciiImage(ifstream& istr);
	int readImage(string filename);
	int rescaleImage();
	int writeAsciiImage(string filename);
	int writeBinaryImage(string filename);
	int writeImage(string filename);

};



