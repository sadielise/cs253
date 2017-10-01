// including
#include <fstream>
#include <istream>
#include <iostream>
#include <string.h>
#include "ReadPGM.h"

// using
using namespace std;
using std::ifstream;
using std::string;
using std::cout;
using std::cerr;

int ReadPGM::readFile(string filename)
{

	//cout << "Made it to ReadPGM.\n" << endl;

	// variables for reading in values
	int width, height, declaredMax;

	// convert filename to a c string
	char cstring[100];	
	strcpy(cstring, filename.c_str());

	// create file input stream
	std::ifstream istr;
	istr.open(cstring, ifstream::in);
	// check for error
	if(istr.fail()){
		cerr << "ERROR: Can't open file for reading." << endl;
		return -1;
	}

	// check for "P2" at beginning of file
	if(istr.get() != 'P'){
		cerr << "ERROR: File does not start with P2." << endl;
		return -1;	
	}
	if(istr.get() != '2'){
		cerr << "ERROR: File does not start with P2." << endl;
		return -1;
	}
	if(!isspace(istr.peek())){
		if(istr.get() == '#') {
			while(istr.get() != '\n')
			;
		}
		else{	
			cerr << "ERROR: Incorrect format after P2." << endl;
			return -1;			
		}
	}


	// get the width
	bool widthFound = false;
	while(widthFound == false){
		istr >> width;
		if(istr.fail()){
			istr.clear();
			if(istr.get() == '#'){
				while(istr.get() != '\n')
				;
			}
			else{
				cerr << "ERROR: Width not found." << endl;
				return -1;
			}
		}
		else{
			if(width < 1){
				cerr << "ERROR: Width must be positive" << endl;
				return -1;
			}
			else
				widthFound = true;	
		}
	}

	//cout << "Width is: " << width << endl;

	// get the height
	bool heightFound = false;
	while(heightFound == false){
		istr >> height;
		if(istr.fail()){
			istr.clear();
			if(istr.get() == '#'){
				while(istr.get() != '\n')
				;
			}
			else{
				cerr << "ERROR: Height not found." << endl;
				return -1;
			}
		}
		else{
			if(height < 1){
				cerr << "ERROR: Height must be positive" << endl;
				return -1;
			}
			else
				heightFound = true;
		}
	}

	//cout << "Height is: " << height << endl;

	// get the declared max
	bool declaredMaxFound = false;
	while(declaredMaxFound == false){
		istr >> declaredMax;		
		if(istr.fail()){
			istr.clear();
			if(istr.get() == '#'){
				while(istr.get() != '\n')
				;
			}
			else{
			    cerr << "ERROR: Declared Max not found." << endl;
				return -1;
			}
		}
		else{
			if(declaredMax < 0 || declaredMax > 256){
				cerr << "ERROR: Declared Max must be between 0 and 256 (inclusive)." << endl;
				return -1;
			}
			else
				declaredMaxFound = true;
		}
	}

	//cout << "Declared Max is: " << declaredMax << endl;

	// get pixel values
	int numPixels = 0; // total number of pixels
	int addPixels = 0; // add up all of the pixel values
	int tempPixel; // temp for reading pixel
	int min, max; // variables for min and max values found

	// loop through the rest of the file
	while(!istr.eof()){
		istr >> tempPixel; // get next int	
		if(istr.fail()){
			istr.clear();
			if(istr.get() == '#'){
				while(istr.get() != '\n')
				;
			}
			else if(istr.eof())
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

			numPixels = numPixels + 1;
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
			}
		}
	}	

	// make sure there are enough pixels
	if(numPixels < (width*height)){
		cerr << "ERROR: Not enough pixels." << endl;
		return -1;
	}

	// convert addPixels and numPixels to doubles
	double addPixelsD = addPixels;
	double numPixelsD = numPixels;

	// calculate the average
	double average = (addPixelsD/numPixelsD);

	// print min, average, and max (separated by whitespace)
	cout << min << " " << average << " " << max << endl;
	
	return 0;
}
