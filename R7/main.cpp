// including
#include <iostream>
#include <fstream>
#include "Image.h"
#include <gtest/gtest.h>

// using
using std::cout;
using std::cerr;
using std::ifstream;


namespace{

TEST(ImageTest1, Handles4Args){
	Image* image = new Image();
	image->setWidth(5);
	int width = image->getWidth();
	ASSERT_EQ(width, 5);
}

TEST(ImageTest2, RescalesCorrectly){
	Image image;
	image.readImage("testImage.pgma");
	image.rescaleImage();
	vector<int> pix = image.getPixels();
	for(unsigned int i = 0; i < pix.size(); i++){
		ASSERT_LE(pix[i], 255);
		ASSERT_LE(pix[i], image.getDeclaredMax());
		ASSERT_GE(pix[i], 0);
	}
}

}
int main(int argc, char* argv[])
{

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
