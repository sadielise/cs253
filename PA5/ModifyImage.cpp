// including
#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "ModifyImage.h"

// using
using namespace std;
using std::ifstream;
using std::string;
using std::cout;
using std::cerr;

// linear scaling calling method
int ModifyImage::linearScale(Image& image1, Image& image2, int N)
{
	unsigned int k = N+1;
	for(unsigned int i = 0; i <= k; i++){
		int scale = linearScaling(image1, image2, i, N);
		if(scale < 0){
			cerr << "ERROR: Image could not be linearly rescaled." << endl;
			return -1;
		}
	}

	return 0;
}

// linear scaling method
int ModifyImage::linearScaling(Image& image1, Image& image2, int j, int N)
{

	// create output image
	Image tempImage;

	// make sure width and height are the same
	if(image1.getWidth() != image2.getWidth()){
		cerr << "ERROR: Width of images is not equal." << endl;
		return -1;
	}

	if(image1.getHeight() != image2.getHeight()){
		cerr << "ERROR: Height of images is not equal." << endl;
		return -1;
	}

	// loop through pixels and rescale
	for(unsigned int i = 0; i < image1.getPixels().size(); i++){
		int tempA = image1.getPixels()[i];
		int tempB = image2.getPixels()[i];
		if(j==0){
			tempImage.addPixel(tempA);
		}
		else{	
			double pixel = (double)tempA + ((double)j/(double)(N+1))*((double)tempB-(double)tempA);
			pixel = round(pixel);
			tempImage.addPixel(pixel);
		}
	}	

	// set variables in tempImage
	tempImage.setType(image1.getType());
	tempImage.setWidth(image1.getWidth());
	tempImage.setHeight(image1.getHeight());
	tempImage.setDeclaredMax(255);

	// get filename
	int temp = j;
	std::stringstream stream;
	stream << temp;
	string str = stream.str();
	string filename = str + ".pgm";
	tempImage.setFilename(filename);

	// output new image
	int write = tempImage.writeImage();
	if(write < 0) return -1;

	return 0;
}

// method to rescale an image for better viewing
int ModifyImage::rescaleImage(Image& image){

	double numPixels = 0.0; // total number of pixels
	double addPixels = 0.0; // add up all of the new pixel values	

	// check for invalid image
	if(image.getMax() == image.getMin()){
		cerr << "ERROR: Invalid image. Max == Min." << endl;
		return -1;
	}

	for(unsigned int i = 0; i < image.getPixels().size(); i++){
		double newValue = (255 * ((double)image.getPixels()[i]- (double)image.getMin())) / ((double)image.getMax() - (double)image.getMin());
		newValue = round(newValue);
		image.getPixels()[i] = newValue;
		numPixels++;
		addPixels += newValue;
	}	

	// set new Image values
	image.setDeclaredMax(255);
	image.setMin(0);
	image.setMax(255);
	image.setAverage(addPixels/numPixels);	

	return 0;
}

