#include<Pixel.tpp>
#include<Image.tpp>
using namespace csucv;

// created just to show off Image and Pixel templates
int main(int argc, char* argv[])
{
  Image<RGB<byte> > color_image(4, 4, RGB<byte>(1,2,3));
  Image<double> intensity_image = color_image;
  cout << intensity_image.at(0,0) << endl;
  if (intensity_image.at(0,0) == 2.5) return 0;
  else return -1;
}
