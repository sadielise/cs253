// including
#include <istream>
#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include "Image.h"
#include <cmath>

// using
using namespace std;
using std::ifstream;
using std::string;
using std::cout;
using std::cerr;

// helper method to check for a comment and read to end of line if found
int Image::checkForComment(ifstream& input)
{

	if(input != NULL){
		if(input.get() == '#'){
			while(input.get() != '\n')
			;
			return 0;
		}
		else
			return -1;
	}

	return -1;
}

// helper method to check for P2 at the start of a .pgm file
int Image::checkForP2(ifstream& input)
{
	if(input.get() != 'P')
		return -1;	
	if(input.get() != '2')
		return -1;
	if(!isspace(input.peek())){
		input.clear();
		if(checkForComment(input) != 0){
			return -1;			
		}
	}

	return 0;
}

// helper method to read the next integer value and check for a comment 
int Image::getValue(ifstream& input)
{
	bool valueFound = false;
	int value;
	while(valueFound == false){
		input >> value;
		if(input.fail()){
			input.clear();
			if(checkForComment(input) != 0)
				return -1;
		}
		else
			valueFound = true;
	}

	return value;
}

// helper method to read pixel values and find min, max, and average
int Image::readPixels(ifstream& input)
{

	// variables
	int min;
	int max;
	double average;

	// get pixel values
	double numPixels = 0.0; // total number of pixels
	double addPixels = 0.0; // add up all of the pixel values
	int tempPixel; // temp for reading pixel

	// loop through the rest of the file
	while(!input.eof()){
		input >> tempPixel; // get next pixel	
		if(input.fail()){
			input.clear();
			if(input.get() == '#'){
				while(input.get() != '\n')
				;
			}
			else if(input.eof())
				break;
			else{
			    cerr << "ERROR: Invalid character in file." << endl;
				return -1;
			}
		}

		// if you find a valid pixel, test its value
		else{
			if(tempPixel < 0 || tempPixel > declaredMax || tempPixel > 255){
				cerr << "ERROR: Pixel value is negative, greater than Delcared Max, or greater than 255." << endl;
				return -1;
			}

			numPixels++;
			if(numPixels > (width*height)){
				cerr << "ERROR: Too many pixels." << endl;
				return -1;
			}

			// if the value is valid, get the min and max
			else{
				if(numPixels == 1){
					min = tempPixel;
					max = tempPixel;
				}
				else{
					if(tempPixel < min)
						min = tempPixel;
					else if(tempPixel > max)
						max = tempPixel;
				}
				//cout << "Pixel value: " << tempPixel << endl;
				// add pixel value to the running total
				addPixels += tempPixel;
				// add pixel value to the pixels vector
				addPixel(tempPixel);
			}
		}
	}	

	// make sure there are enough pixels
	if(numPixels < (width*height)){
		cerr << "ERROR: Not enough pixels." << endl;
		return -1;
	}

	// calculate the average
	average = (addPixels/numPixels);

	// set min, max, and average
	setMin(min);
	setMax(max);
	setAverage(average);

	return 0;

}

void Image::printPixels(vector<int>& pixels) const{

	for(unsigned int i = 0; i < pixels.size(); i++){
		cout << pixels[i] << endl;
	}

}

// method that reads image and sets key variables
int Image::readImage(string filename)
{

	// variables
	int width;
	int height;
	int declaredMax;

	//cout << "Made it to Image.\n" << endl;

	// convert filename to a c string
	char cstring[100];	
	strcpy(cstring, filename.c_str());

	// create file input stream
	ifstream istr;
	istr.open(cstring, ifstream::in);
	// check for error
	if(istr.fail()){
		cerr << "ERROR: Can't open file for reading." << endl;
		return -1;
	}

	// check for "P2" at beginning of file
	if(checkForP2(istr) != 0){
		cerr << "ERROR: File does not start with P2." << endl;
		return -1;
	}

	// get the width
	width = getValue(istr);
	if(width < 1){
		cerr << "ERROR: Invalid width." << endl;
		return -1;
	}
	else
		setWidth(width);

	//cout << "Width is: " << getWidth() << endl;

	// get the height
	height = getValue(istr);
	if(height < 0){
		cerr << "ERROR: Invalid height." << endl;
		return -1;
	}
	else
		setHeight(height);

	//cout << "Height is: " << getHeight() << endl;

	// get the declared max
	declaredMax = getValue(istr);
	if(declaredMax < 0 || declaredMax > 256){
		cerr << "ERROR: Invalid declared max." << endl;
		return -1;
	}
	else
		setDeclaredMax(declaredMax);

	//cout << "Declared Max is: " << getDeclaredMax() << endl;

	// get pixels
	int test = readPixels(istr);
	if(test < 0)
		return -1;

	// print min, average, and max (separated by whitespace)
	//cout << getMin() << " " << getAverage() << " " << getMax() << endl;

	// close file
	istr.close();
	
	return 0;
}

// method to rescale an image for better viewing
int Image::rescaleImage(){

	double numPixels = 0.0; // total number of pixels
	double addPixels = 0.0; // add up all of the new pixel values	

	// check for invalid image
	if(getMax() == getMin()){
		cerr << "ERROR: Invalid image. Max == Min." << endl;
		return -1;
	}

	for(unsigned int i = 0; i < getPixels().size(); i++){
		double newValue = (255 * ((double)getPixels()[i]- (double)getMin())) / ((double)getMax() - (double)getMin());
		newValue = round(newValue);
		getPixels()[i] = newValue;
		numPixels++;
		addPixels += newValue;
	}	

	// set new Image values
	setDeclaredMax(255);
	setMin(0);
	setMax(255);
	setAverage(addPixels/numPixels);	

	return 0;
}


// method to write Image to a .pgm file
int Image::writeImage(string filename){

	// convert filename to a c string
	char cstring[100];	
	strcpy(cstring, filename.c_str());

	// create file output stream
	ofstream ostr;
	ostr.open(cstring);
	// check for error
	if(ostr.fail()){
		cerr << "ERROR: Can't open file for writing." << endl;
		return -1;
	}

	// print "P2"
	ostr << "P2\n";

	// print width, height, declaredMax
	ostr << getWidth() << " " << getHeight() << " " << getDeclaredMax() << "\n" << "\n";

	// print pixels
	int index = 0;
	for(int i = 0; i < getHeight(); i++){
		for(int j = 0; j < getWidth(); j++){
			ostr << getPixels()[index] << " ";
			index++;
		}
		ostr << "\n";
	}

	ostr.close();

	return 0;
}

