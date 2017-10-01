#include "Mapping.h"
#include "Image.h"
#include <vector>
#include <math.h>

// using
using namespace std;
using std::string;
using std::cout;
using std::cerr;

class Morpher{

public:
	Morpher(string kpFile){
		keyPointFilename = kpFile;
	}

	int morphImage(Image& inputImage, Image& outputImage);

protected:
	string keyPointFilename;
};
