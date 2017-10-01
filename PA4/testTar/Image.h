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

public:	

	// constructor and overloads
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
	vector<int> getPixels();
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
	int writeAsciiImage(Image* image, string filename);
	int writeBinaryImage(Image* image, string filename);
	int writeImage(Image* image, string filename, int type);

protected:
	int type;
	int width;
	int height;
	int declaredMax;
	int minimum;
	int maximum;
	double average;
	vector<int> pixels;	

};



