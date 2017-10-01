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
		type = 0;
		width = 0;
		height = 0;
		declaredMax = 255;
		minimum = 0;
		maximum = 0;
		average = 0;
	}

	// getters and setters
	inline int getType(){return type;}
	inline void setType(int t){type = t;}
	inline int getWidth(){return width;}
	inline void setWidth(int w){width = w;}
	inline int getHeight(){return height;}
	inline void setHeight(int h){height = h;}
	inline int getDeclaredMax(){return declaredMax;}
	inline void setDeclaredMax(int d){declaredMax = d;}
	inline int getMin(){return minimum;}
	inline void setMin(int mi){minimum = mi;}
	inline int getMax(){return maximum;}
	inline void setMax(int ma){maximum = ma;}
	inline double getAverage(){return average;}
	inline void setAverage(double ave){average = ave;}
	inline vector<int> getPixels(){return pixels;}
	inline void addPixel(int p){pixels.push_back(p);}
	inline string getFilename(){return filename;}
	inline void setFilename(string f){filename = f;}

	// functions
	int getPixel(int x, int y);
	void setPixel(int x, int y, int pixel);
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
	int writeAsciiImage();
	int writeBinaryImage();
	int writeImage();

protected:
	int type;
	int width;
	int height;
	int declaredMax;
	int minimum;
	int maximum;
	double average;
	vector<int> pixels;	
	string filename;

};



