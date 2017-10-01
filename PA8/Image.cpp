// including
#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Image.h"
#include <cmath>
#include <sstream>
#include <algorithm>

// using
using namespace std;
using std::ifstream;
using std::string;
using std::cout;
using std::cerr;
using std::min_element;
using std::sort;
using std::unique;
using std::distance;
using std::greater;

// method to find minimum pixel value in image
int Image::getMinPixel(){

	int min = *min_element(pixels.begin(),pixels.end());
	return min;
}

// method to find median pixel value in image
int Image::getMedianPixel(){
	
	int median = 0;
	sort(pixels.begin(), pixels.end());

	if(pixels.size()%2 == 0){	
		median = pixels[(pixels.size()/2)-1];
	}

	else{
		median = pixels[(pixels.size()/2)];
	}		

	return median;
	
}

// method to count number of even pixels in an image
int Image::getEvenPixels(){

	int count = 0;
	for(unsigned int i = 0; i < pixels.size(); i++){
		if((pixels[i]%2) == 0)			
			count++;
	}
	return count;
}

// method to count number of unique pixels in an image
int Image::getUniquePixels(){

	vector<int> tempPixels = pixels;
	vector<int>::iterator iterate = unique(tempPixels.begin(), tempPixels.end());
	tempPixels.resize(distance(tempPixels.begin(), iterate));
	return tempPixels.size();
}

// method to sort pixels in descending order
void Image::sortDescending(){

	sort(pixels.begin(), pixels.end(), greater<int>());

}

// method to get pixel at index from pixel vector
int Image::getPixel(int x, int y){

	// check x
	if(x < 0 || (x > getWidth()-1)){
		cerr << "ERROR: X value is outside of image." << endl;
		return -1;
	}

	// check y
	if(y < 0 || (y > getHeight()-1)){
		cerr << "ERROR: Y value is outside of image." << endl;
		return -1;
	}

	return pixels[y*getWidth() + x];

}

// method to set pixel at index in pixel vector
void Image::setPixel(int x, int y, int pixel){

	// check x
	if(x < 0 || (x > getWidth()-1)){
		cerr << "ERROR: X value is outside of image." << endl;
	}

	// check y
	if(y < 0 || (y > getHeight()-1)){
		cerr << "ERROR: Y value is outside of image." << endl;
	}


	pixels[y*getWidth() + x] = pixel;

}

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

// helper method to check for magic number at the start of a .pgm file
int Image::checkMagicNumber(ifstream& input)
{
	// check for P
	unsigned char letter = input.get();
	if(letter != 'P') return -1;
	
	// check for 2
	unsigned char number = input.get();
	if(number == '2'){
		if(!isspace(input.peek())){
			input.clear();
			if(checkForComment(input) != 0){
				return -1;			
			}
		}
		type = 2;
		return 2;
	}

	// otherwise, check for 5
	else if(number == '5'){
		type = 5;
		return 5;
	}
	else return -1;

}

// helper method to read the next 4 bytes and put into an integer
int Image::getFourBytes(ifstream& input)
{

	unsigned char one;
	input.read((char *)&one, 1);
	if(input.fail()){
		return -1;
	}

	unsigned char two;
	input.read((char*) &two, 1);
	if(input.fail()){
		return -1;
	}

	unsigned char three;
	input.read((char*) &three, 1);
	if(input.fail()){
		return -1;
	}

	unsigned char four;
	input.read((char*) &four, 1);
	if(input.fail()){
		return -1;
	}

	unsigned int oneShift = (unsigned int)one << 24;
	unsigned int twoShift = (unsigned int)two << 16;
	unsigned int threeShift = (unsigned int)three << 8;
	unsigned int fourShift = (unsigned int)four;

	unsigned int newValue = oneShift | twoShift | threeShift | fourShift;

	return newValue;
	
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

// helper method to read pixel values from binary file
int Image::readBinaryPixels(ifstream &input)
{

	double numPixels = getWidth() * getHeight(); // total number of pixels
	//double addPixels = 0.0; // add up all of the pixel values
	unsigned char tempPixel; // temp for reading pixel

	// check file size
	input.seekg(0, ios::end);
	int size = input.tellg();
	if(size != (14 + numPixels)){
		cerr << "ERROR: Number of binary pixels is incorrect." << endl;
		return -1;
	}

	// move back to beginning of pixels
	input.seekg((-1 * numPixels), ios::cur);
	// cout << input.tellg() << endl;
	for(int i = 0; i < numPixels; i++){
		input.read((char*) &tempPixel, 1);
		int temp = (int)tempPixel;
		// check pixel value
		if(temp < 0 || temp > getDeclaredMax() || temp > 255){
			cerr << "ERROR: Binary pixel value is negative, greater than Declared Max, or greater than 255." << endl;
			return -1;
		}

		else{
			if(i == 0){
				setMin(temp);
				setMax(temp);
			}
			else{
				if(temp < getMin())
					setMin(temp);
				else if(temp > getMax())
					setMax(temp);
				}
			//cout << "Pixel value: " << tempPixel << endl;
			// add pixel value to the running total
			//addPixels += tempPixel;
			// add pixel value to the pixels vector
			addPixel(tempPixel);
			}
	}


	return 0;
}

// helper method to read pixel values and find min, max, and average
int Image::readPixels(ifstream& input)
{

	// get pixel values
	double numPixels = 0.0; // total number of pixels
	//double addPixels = 0.0; // add up all of the pixel values
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
/*
				if(numPixels == 1){
					setMin(tempPixel);
					setMax(tempPixel);
				}
				else{
					if(tempPixel < getMin())
						setMin(tempPixel);
					else if(tempPixel > getMax())
						setMax(tempPixel);
				}
				//cout << "Pixel value: " << tempPixel << endl;
				// add pixel value to the running total
				addPixels += tempPixel;
*/
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
	//average = (addPixels/numPixels);

	return 0;

}

void Image::printPixels(vector<int>& pixels) const
{

	for(unsigned int i = 0; i < pixels.size(); i++){
		cout << pixels[i] << endl;
	}

}

// method that reads binary image and sets key variables
int Image::readBinaryImage(ifstream& bistr)
{
	// read magic number
	unsigned char p, five;
	bistr.read((char*) &p, 1);
	if(bistr.fail()){
		cerr << "ERROR: P could not be read in binary" << endl;
		return -1;
	}
	bistr.read((char*) &five, 1);
	if(bistr.fail()){
		cerr << "ERROR: 5 could not be read in binary" << endl;
		return -1;
	}

	
	// read width, height, and declaredMax
	unsigned int w = getFourBytes(bistr);
	if(w < 0){
		cerr << "ERROR: Invalid binary width." << endl;
		return -1;
	}
	else setWidth(w);

	unsigned int h = getFourBytes(bistr);
	if(h < 0){
		cerr << "ERROR: Invalid binary height." << endl;
		return -1;
	}
	else setHeight(h);

	unsigned int dm = getFourBytes(bistr);
	if(dm < 0){
		cerr << "ERROR: Invalid binary declared maximum." << endl;
		return -1;
	}
	else setDeclaredMax(dm);

	// reserve space in pixel vector
	pixels.reserve(width*height);

	// read pixels
	int test = readBinaryPixels(bistr);
	if(test < 0)
		return -1;

	bistr.close();
	

	return 0;

}

// method that reads ASCII image and sets key variables
int Image::readAsciiImage(ifstream& istr)
{

	// get the width
	int w = getValue(istr);
	if(w < 0){
		cerr << "ERROR: Invalid width." << endl;
		return -1;
	}
	else
		setWidth(w);

	// get the height
	int h = getValue(istr);
	if(h < 0){
		cerr << "ERROR: Invalid height." << endl;
		return -1;
	}
	else
		setHeight(h);

	// get the declared max
	int dm = getValue(istr);
	if(dm < 0 || dm > 256){
		cerr << "ERROR: Invalid declared max." << endl;
		return -1;
	}
	else
		setDeclaredMax(dm);

	// reserve space in vector
	pixels.reserve(width*height);

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

// method that reads image and send to Binary or Ascii reading method
int Image::readImage(string filename)
{

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

	int readCheck = 0;

	// check for magic number at beginning of file
	int magic = checkMagicNumber(istr);
	// if ASCII, send to readAsciiImage
	if(magic == 2){
		readCheck = readAsciiImage(istr);
	}
	// if binary, reopen file as binary and send to readBinaryImage
	else if(magic == 5){
		istr.close();
		ifstream bistr;
		bistr.open(cstring, ios::binary);
		if(bistr.fail()){
			cerr << "ERROR: Can't open binary file for reading." << endl;
			return -1;
		}
		else{
			readCheck = readBinaryImage(bistr);
		}
	}
	// otherwise, throw error
	else{			
		cerr << "ERROR: File does not start with P2 or P5." << endl;
		return -1;
	}
	
	return readCheck;
}

// method to write ASCII Image to a .pgma file
int Image::writeAsciiImage(){

	// convert filename to a c string
	char cstring[100];	
	strcpy(cstring, filename.c_str());

	// create file output stream
	ofstream ostr;
	ostr.open(cstring);
	// check for error
	if(ostr.fail()){
		cerr << "ERROR: Can't open file for writing ASCII Image." << endl;
		return -1;
	}

	// print "P2"
	ostr << "P2 ";

	// print width, height, declaredMax
	ostr << width << " " << height << " " << declaredMax << "\n";

	// print pixels
	int index = 0;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			ostr <<  pixels[index] << " ";
			index++;
		}
		ostr << "\n";
	}

	ostr.close();

	return 0;
}

// method to write a binary image to a file
int Image::writeBinaryImage()
{
	// convert filename to a c string
	char cstring[100];	
	strcpy(cstring, filename.c_str());

	// create file output stream
	ofstream ostr;
	ostr.open(cstring, ios::binary);
	// check for error
	if(ostr.fail()){
		cerr << "ERROR: Can't open file for writing binary image." << endl;
		return -1;
	}

	// print header
	unsigned char p = 'P';
	unsigned char five = '5';
	ostr.write((char*) &p, 1);
	ostr.write((char*) &five, 1);

	// masks
	int mask1 = 255 << 24;
	int mask2 = 255 << 16;
	int mask3 = 255 << 8;
	int mask4 = 255;

	// print width
	int w = width;
	int shiftedW1 = (w & mask1) >> 24;
	ostr.write((char*) &shiftedW1, 1);

	int shiftedW2 = (w & mask2) >> 16;
	ostr.write((char*) &shiftedW2, 1);

	int shiftedW3 = (w & mask3) >> 8;
	ostr.write((char*) &shiftedW3, 1);

	int shiftedW4 = w & mask4;
	ostr.write((char*) &shiftedW4, 1);
	
	// print height
	int h = height;
	int shiftedH1 = (h & mask1) >> 24;
	ostr.write((char*) &shiftedH1, 1);

	int shiftedH2 = (h & mask2) >> 16;
	ostr.write((char*) &shiftedH2, 1);

	int shiftedH3 = (h & mask3) >> 8;
	ostr.write((char*) &shiftedH3, 1);

	int shiftedH4 = (h & mask4);
	ostr.write((char*) &shiftedH4, 1);

	// print declared max
	int dm = declaredMax;
	int shiftedD1 = (dm & mask1) >> 24;
	ostr.write((char*) &shiftedD1, 1);

	int shiftedD2 = (dm & mask2) >> 16;
	ostr.write((char*) &shiftedD2, 1);

	int shiftedD3 = (dm & mask3) >> 8;
	ostr.write((char*) &shiftedD3, 1);
	
	int shiftedD4 = (dm & mask4);
	ostr.write((char*) &shiftedD4, 1);

	// print pixels
	for(unsigned int i = 0; i < pixels.size(); i++){
		unsigned char pixel = (unsigned char)pixels.at(i);
		ostr.write((char*) &pixel, 1);
	}

	ostr.close();
	
	return 0;

}

int Image::writeImage()
{

	int writeCheck = 0;
	
	if(type == 2){
		writeCheck = writeAsciiImage();
	}
	else if(type == 5){
		writeCheck = writeBinaryImage();
	}

	return writeCheck;

}

