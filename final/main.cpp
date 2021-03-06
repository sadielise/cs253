// including
#include <iostream>
#include <fstream>
#include<Pixel.tpp>
#include<Image.tpp>
#include<memory>
using std::shared_ptr;

// using
using namespace std;
using std::cout;
using std::cerr;
using std::ifstream;

int main(int argc, char* argv[])
{
	
/*	Image<int>* i = new Image<int>(2,2);
	shared_ptr<Image<int> > image_ptr (i);
	//shared_ptr<Image<int> > image_ptr1 (new Image<int>(2,2));
	shared_ptr<Window<int> > wd_ptr = i->SubWindow(image_ptr, 1, 1, 2, 2);
	//shared_ptr<Window<int> > wd_ptr1 = i->SubWindow(image_ptr1, 1, 1, 2, 2);	*/
	
	RGB<> rgb(1.3,2.4,3.5);
	cout << rgb.Green() << endl;

	HSV hsv(1,2,3);
	cout << hsv.Hue() << endl;


	return 0;

}
