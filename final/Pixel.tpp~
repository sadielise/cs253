#ifndef PIXEL_TPP
#define PIXEL_TPP
#include <algorithm>

typedef unsigned char byte;

class Pixel {
public:
  virtual operator byte() const {return 0;}
  virtual operator int() const {return 0;}
  virtual operator double() const = 0;
};

template<typename TYPE>
class RGB : public Pixel {
public:
  RGB() : red(static_cast<TYPE>(0)), green(static_cast<TYPE>(0)), blue(static_cast<TYPE>(0)) {}
  RGB(const TYPE& r, const TYPE& g, const TYPE& b) : red(r), green(g), blue(b) {}

  // accessors
  const TYPE& Red() const {return red;}
  const TYPE& Green() const {return green;}
  const TYPE& Blue() const {return blue;}

  // mutators
  TYPE& Red() {return red;}
  TYPE& Green() {return green;}
  TYPE& Blue() {return blue;}

  // type converters
  virtual operator byte() const {return std::min(255, std::max(0, ((red + green) / 2)));}
  virtual operator int() const {return (red+green)/2;}
  virtual operator double() const {return (red+green)/2.0;}

protected:
  TYPE red;
  TYPE green;
  TYPE blue;
};

class HSV : public Pixel {
public:
  HSV() : hue(0.0), saturation(0.0), value(0.0) {}
  HSV(double h, double s, double v) : hue(h), saturation(s), value(v) {}

  // accessors
  double Hue() const {return hue;}
  double Saturation() const {return saturation;}
  double Value() const {return value;}

  // mutators
  double& Hue() {return hue;}
  double& Saturation() {return saturation;}
  double& Value() {return value;}

  // type converters
  virtual operator byte() const {return std::min(255.0, std::max(0.0, value));}
  virtual operator int() const {return value;}
  virtual operator double() const {return value;}

protected:
  double hue;
  double saturation;
  double value;
};

#endif // PIXEL_TPP
