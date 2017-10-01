#include "Morpher.h"
#include <vector>
#include <math.h>

// using
using namespace std;
using std::string;
using std::cout;
using std::cerr;
	
int Morpher::morphImage(Image& inputImage, Image& outputImage){
	
	// create a mapper
	Mapping mp(keyPointFilename);

	// go through all pixels in output image
	for(int y = 0; y < outputImage.getHeight(); y++){
		for(int x = 0; x < outputImage.getWidth(); x++){
			int pixelValue;
			vector<int> outputPixel;
			outputPixel.push_back(x);
			outputPixel.push_back(y);
			// get source pixel
			vector<int> sourcePixel = mp.findSourcePixel(outputPixel);
			// check bounds of source pixel
			if(sourcePixel[0] < 0 || sourcePixel[1] < 0 || sourcePixel[0] > outputImage.getWidth()-1 || sourcePixel[1] > outputImage.getHeight()-1){
				pixelValue = 0;
			}
			else{
				pixelValue = inputImage.getPixel(sourcePixel[0], sourcePixel[1]);
			}
			// set output pixel
			outputImage.addPixel(pixelValue);
		}
	}

	outputImage.writeImage();

	return 0;

}
