#ifndef PIXEL_TPP_DEFINED
#define PIXEL_TPP_DEFINED

#include <Exception.h>
#include <algorithm>
using std::min;
using std::max;
#include <cstring>
using std::memcpy;

namespace csucv {

/*! \file Pixel.tpp
 * \brief Templates & headers for non-scalar pixel types
 *
 * This file contains headers and/or template definitions for non-scalar pixel types. In general,
 * pixels are data types that can be put into images. All scalars are
 * pixels, but the actively supported scalar types are bool, byte, int, float and double. In addition,
 * std::complex is a pixel type. This file defines pixel types beyond the scalars and complex, with the
 * expectation that most of these will be defined in terms of color spaces.
 * 
 * There is no formal interface for pixels. We couldn't enforce it on scalars or std::complex. More importantly,
 * the most important restriction on pixels cannot be expressed in C++ and can only be implemented by 
 * convention: PIXELS CANNOT HAVE NON-DEFAULT COPY CONSTRUCTORS OR DESTRUCTORS. This allows us to move
 * blocks of pixels using the memcpy comman. The implication is that pixels cannot contain pointers,
 * and reference counting cannot be used on pixels. Also, pixels must have default (no argument) constructors,
 * so that we can create uninitialized images.
 * 
 * Pixels should also define the () operator and the at(int) method, to allow their individual values to
 * be accessed. It is also a good idea to define an enumerated type for access, for example at(RGB::red).
 */

/*! \typedef byte : a synonym for unsigned char (used commonly because of unsigned 8-bit camera values) */
typedef unsigned char byte;

/*! \class RGB
 * \brief A pixel class for RGB (red, green, blue) color values.
 *
 * A simple pixel class for RGB (red, green, blue) color values. Includes indexing methods for accessing
 * individual red, green and blue values (RGB<type>::red, green, blue is an enumerated top for accessing
 * values by name). Also includes conversion routines for converting color values to intensities.
 */
template<typename VALUETYPE>
class RGB {
public:
  /*! \enum Enumerated type for accessing colors by name */
  enum Color {red = 0, green, blue};

  /* Constructors */
  /// Default constructor (no values)
  RGB() {data[0]=static_cast<VALUETYPE>(0); data[1]=static_cast<VALUETYPE>(0); data[2]=static_cast<VALUETYPE>(0);}
  /// Scalar constructor: convert from intensity to three equal color values
  RGB(VALUETYPE intensity) {data[0] = intensity; data[1] = intensity; data[2] = intensity;}
  /// Constructor from three individual values (red, green & blue). Types should match RGB instantiation type.
  RGB(VALUETYPE red, VALUETYPE green, VALUETYPE blue) {data[0] = red; data[1] = green; data[2] = blue;}
  /// Constructor given a pointer to three values. Types should match RGB instantiation type.
  RGB(VALUETYPE* ptr) {data[0] = (*ptr++); data[1] = (*ptr++); data[2] = (*ptr);}
  /// Copy constructor with matching data type. Just blast bytes using memcpy.
  RGB(const RGB<VALUETYPE>& src) { memcpy(data, src.data, 3*sizeof(VALUETYPE)); }
  /// Copy constructor between different color data types. Call cast operator on all three values.
  template<typename SRCTYPE>
  RGB(const RGB<SRCTYPE>& src) {data[0] = static_cast<SRCTYPE>(src[0]); data[1] = static_cast<SRCTYPE>(src[1]); data[2] = static_cast<SRCTYPE>(src[2]);}
  
  /* Indexing (Accessors and Mutators) */
  /// Unprotected read/write access
  VALUETYPE& operator[] (int index) {return data[index];}
  /// Unprotected read-only access
  const VALUETYPE& operator[] (int index) const {return data[index];}
  /// Protected read/write access with unsigned int index
  VALUETYPE& at(unsigned int index) {if (index < 3) return data[index]; else throw BoundsException("RGB", index, 3);}
  /// Protected read-only access with unsigned int index
  const VALUETYPE& at(unsigned int index) const {if (index < 3) return data[index]; else throw BoundsException("RGB", index, 3);}
  /// Protected read/write access
  VALUETYPE& at(int index) {if ((index >= 0) && (index < 3)) return data[index]; else throw BoundsException("RGB", index, 3);}
  /// Protected read-only access
  const VALUETYPE& at(int index) const {if ((index >= 0) && (index < 3)) return data[index]; else throw BoundsException("RGB", index, 3);}

  /* Type conversions (some will overflow when VALUETYPE = byte; see special cases below) */
  /// Conversion to intensity byte value
  inline operator byte() const {return byte(max<VALUETYPE>(0, min<VALUETYPE>(255, ((data[0]+data[1])/2))));}
  /// Conversion to intensityint value
  inline operator int() const {return int((data[0]+data[1])/2);}
  /// Conversion to intensity float value
  inline operator float() const {return ((float(data[0])+float(data[1]))/float(2.0));}
  /// Conversion to intensity double value
  inline operator double() const {return ((double(data[0])+double(data[1]))/2.0);}
  
private:
  /// The (in-line) memory where color values are stored.
  VALUETYPE data[3];
};

/* Special case constructors */
template<>
template<typename SRCTYPE>
RGB<byte>::RGB (const RGB<SRCTYPE>& src) 
{ 
  data[0] = byte(max<int>(0, min<int>(255, src[0])));
  data[1] = byte(max<int>(0, min<int>(255, src[1])));
  data[2] = byte(max<int>(0, min<int>(255, src[2])));
}

/* Special cases of conversion operators */
template<>
inline RGB<byte>::operator byte() const {return (min<byte>(255, ((int(data[0])+int(data[1]))/2)));}
template<>
inline RGB<byte>::operator int() const {return int((int(data[0])+int(data[1]))/2);}

} // namespace csucv

#endif // PIXEL_TPP_DEFINED
