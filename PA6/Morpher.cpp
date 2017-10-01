#include "Morpher.h"
#include <vector>
#include <math.h>
#include <string>
#include <sstream>

// using
using namespace std;
using std::string;
using std::cout;
using std::cerr;
	
int Morpher::morphImage(Image& image1, Image& image2, int j){
	
	// create a mapper
	Mapping mp(keypoint);

	// create an output image w/ same width and height as input images
	Image imageJ;
	imageJ.setWidth(image1.getWidth());
	imageJ.setHeight(image1.getHeight());
	imageJ.setType(2);
	// get filename
	int temp = j;
	std::stringstream stream;
	stream << temp;
	string str = stream.str();
	string filename = str + ".pgm";
	imageJ.setFilename(filename);

	// go through all pixels in output image
	for(int y = 0; y < imageJ.getHeight(); y++){
		for(int x = 0; x < imageJ.getWidth(); x++){

			// create a temp pixel from current x and y values
			vector<int> tempPixel;
			tempPixel.push_back(x);
			tempPixel.push_back(y);

			// find pixel from image1 to outputImage
			double sourcePixelValue;
			// get source pixel from image1 using tempPixel and j
			vector<int> sourcePixel = mp.findSourcePixel(tempPixel, j);
			// check bounds of source pixel
			if(sourcePixel[0] < 0 || sourcePixel[1] < 0 || sourcePixel[0] > imageJ.getWidth()-1 || sourcePixel[1] > imageJ.getHeight()-1){
				sourcePixelValue = 0;
			}
			else{
				sourcePixelValue = (double)image1.getPixel(sourcePixel[0], sourcePixel[1]);
			}

			// find pixel from outputImage to image2
			double destPixelValue;
			// get destination pixel from image2 using tempPixel and j
			vector<int> destPixel = mp.findDestPixel(tempPixel, j);
			// check bounds of dest pixel
			if(destPixel[0] < 0 || destPixel[1] < 0 || destPixel[0] > imageJ.getWidth()-1 || destPixel[1] > imageJ.getHeight()-1){
				destPixelValue = 0;
			}
			else{
				destPixelValue = (double)image2.getPixel(destPixel[0], destPixel[1]);
			}			

			// set output pixel in imageJ
			double N = (double)keypoint.getN();
			double outputPixelValueTemp = ((((N-(double)j+(double)1)/(N+(double)1))*sourcePixelValue)+(((double)j/(N+(double)1))*destPixelValue));
			int outputPixelValue = round(outputPixelValueTemp);
			imageJ.addPixel(outputPixelValue);
			
		}
	}

	imageJ.writeImage();

	return 0;

}
