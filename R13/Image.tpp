#ifndef IMAGE_TPP_DEFINED
#define IMAGE_TPP_DEFINED

#include <Exception.h>
#include <algorithm>  // fill
#include <cstring>    // memcpy
#include <complex>

#include<Pixel.tpp>

// for debugging
#include<iostream>
using std::cout;
using std::endl;

namespace csucv {

  /*! \class Image
   * \brief Class for holding/accessing image data, and passing image among libraries with different image formats
   *
   * Every computer vision and image processing library has its own image class, and they are generally incompatible. 
   * For example, the OpenCV Mat class is not templated and are stored in row major order. Armadillo matrices are
   * templated are stored in column major order. This class is meant to serve as a unifying image class. It holds
   * and provides acccess to image data and acts like an STL container, for anyone writing a vision algorithm it is 
   * straight C++. But it has conversion methods to make the equivalent OpenCV Mat object or Armadillo matrix class, 
   * and for converting these classes back to CSUCV format. 
   *
   * Image pixels may be one of five scalar types: bool, byte, int, float or double. They may also be std::complex<double>,
   * or any pixel type defined in Pixel.hpp. Actually, they can be any data type at all, but these are the types that we
   * will write our test code for, and in that sense they are the supported types. The only restriction on pixel types 
   * is that they must have only default copy constructors and destructors, so that the image class may move blocks of 
   * them as bytes using memcpy. If you intend to convert images across pixel types, then you need to define the appropriate
   * casting operators among pixel types.
   */
  template<typename PIXELTYPE>
  class Image {
  public:
    /* Typedefs for container compatibility */
    typedef PIXELTYPE* iterator;                  ///< iterator type definition for STL container compatibility
    typedef const PIXELTYPE* const_iterator;      ///< const_iterator type definition for STL container compatibility
    typedef PIXELTYPE value_type;                 ///< value_type type definition for STL container compatibility
    typedef PIXELTYPE& reference;                 ///< reference type definition for STL container compatibility
    typedef const PIXELTYPE& const_reference;     ///< const_reference type definition for STL container compatibility
    typedef unsigned int size_type;               ///< size_type type definition for STL container compatibility
    typedef unsigned int difference_type;         ///< difference_type type definition for STL container compatibility

    /* Constructors, Assignment & Destructors */
    /// Create width by height image with uninitialized pixel values. Without arguments, produces 0x0 empty image.
    Image(size_type width=0, size_type height=0) { allocate_memory(width, height); }
    /// Create width by height image with pixels initialized to value
    Image(size_type width, size_type height, PIXELTYPE value) { allocate_memory(width, height); std::fill(begin(), end(), value); }
    /// Copy constructor for source images with matching pixel types.
    Image(const Image<PIXELTYPE>& src) { allocate_memory(src.width(), src.height()); std::memcpy(data_ptr, src.data_ptr, byte_size()); }
    /// Copy constructor for source images with different pixel types.
    template<typename SRCTYPE> Image(const Image<SRCTYPE>& src) {allocate_memory(src.width(), src.height()); copy(src);}
    /// Deallocates all memory, nulls internal pointers and zeros sizes.
    ~Image() { deallocate_memory(); }
    /// Assignment operator (matching pixel types). Necessary to avoid default assignment operator.
    Image<PIXELTYPE>& operator= (const Image<PIXELTYPE>& src) {copy(src); return *this; }
    /// Assignment operator (across pixel types)
    template<typename SRCTYPE> Image<PIXELTYPE>& operator= (const Image<SRCTYPE>& src) {copy(src); return *this; }

    /// copy data between images of the same type. May resize destination image. Uses memcpy (no pixel constructors called).
    void copy(const Image<PIXELTYPE>& src) {resize(src.width(), src.height()); std::memcpy(data_ptr, src.data_ptr, byte_size());}
    /// copy data between images of different type. May resize destination image. Every pixel is casted.
    template<typename SRCTYPE> void copy(const Image<SRCTYPE>& img);
    /// Resize image. Tests first to see if resizing is necessary. Values after resize are undefined.
    void resize(size_type width, size_type height);

    /* simple properties */
    inline size_type width() const {return cols;}                                   ///< width of image (# of columns)
    inline size_type height() const {return rows;}                                  ///< height of image (# of rows)
    inline size_type size() const {return (rows * cols);}                           ///< number of pixels in image
    inline size_type byte_size() const {return (size() * sizeof(PIXELTYPE));}       ///< number of bytes in image
    inline size_type byte_stride() const {return (width()*sizeof(PIXELTYPE)); }     ///< number of bytes per row (width = # of PIXELTYPE)
    inline bool empty() const {return (size() == 0);}                               ///< whether or not image is empty

     /* random access */
    /// Unprotected random access (mutator)
    inline PIXELTYPE& operator () (size_type row, size_type col) {return *(*(row_ptr+row)+col); }
    /// Unprotected random access (accessor)
    inline const PIXELTYPE& operator () (size_type row, size_type col) const {return *(*(row_ptr+row)+col); }
    /// Protected random access (mutator)
    inline PIXELTYPE& at(size_type row, size_type col);
    /// Protected random access (accessor)
    inline const PIXELTYPE& at(size_type row, size_type col) const;

   /* sequential access */
    inline iterator begin() {return data_ptr;}                                   ///< return mutator iterator
    inline const_iterator begin() const {return data_ptr;}                       ///< return accessor iterator
    inline iterator end() {return (data_ptr + size());}                          ///< return mutator end iterator
    inline const_iterator end() const {return (data_ptr + size());}              ///< return accessor end iterator

  protected:
    /* Memory Management */
    /// Allocate internal memory, initializing all pointers and sizes
    void allocate_memory(size_type width, size_type height);
    /// Deallocate internal memory, and null out all pointers and sizes
    void deallocate_memory();
 
    size_type rows;                               ///< Number of rows in image
    size_type cols;                               ///< Number of columns in image
    PIXELTYPE* data_ptr;                          ///< ptr to row major block of image data 
    PIXELTYPE** row_ptr;                          ///< ptr to array of pointers to beginning of each image row
  };
   
  template<typename PIXELTYPE>
  void Image<PIXELTYPE>::allocate_memory(size_type width, size_type height)
  {
    data_ptr = new PIXELTYPE[width*height];
    row_ptr = new PIXELTYPE*[height];
    
    PIXELTYPE* temp_data_ptr = data_ptr;
    PIXELTYPE** temp_row_ptr = row_ptr;
    for(unsigned int row_ctr = 0; row_ctr < height; row_ctr++, temp_data_ptr += width) {
      (*temp_row_ptr++) = temp_data_ptr;
    }
    
    rows = height;
    cols = width;
  }
  
  template<typename PIXELTYPE>
  void Image<PIXELTYPE>::deallocate_memory()
  {
    delete [] data_ptr;
    data_ptr = NULL;
    delete [] row_ptr;
    row_ptr = NULL;
    rows = 0;
    cols = 0;
  }

  /* often, all the images in a set will be the same size (e.g. a video). Therefore
  / we can save a lot of time by not resizing them unless we have to. */
  template<typename PIXELTYPE>
  void Image<PIXELTYPE>::resize(size_type new_width, size_type new_height)
  {
    if ((width() != new_width) || (height() != new_height)) {
      deallocate_memory();
      allocate_memory(new_width, new_height);
    }
  }

  template<typename PIXELTYPE>
  PIXELTYPE& Image<PIXELTYPE>::at(size_type row, size_type col)
  {
    if (row >= rows) throw BoundsException("Image (row dimension)", row, rows);
    if (col >= cols) throw BoundsException("Image (col dimension)", col, cols);
    return (*this)(row,col);
  }
  
  template<typename PIXELTYPE>
  const PIXELTYPE& Image<PIXELTYPE>::at(size_type row, size_type col) const
  {
    if (row >= rows) throw BoundsException("Image (row dimension)", row, rows);
    if (col >= cols) throw BoundsException("Image (col dimension)", col, cols);
    return (*this)(row,col);
  }
  
  /*This is for converting an image from one pixel type to another. Note that if the
    source and destination types are the same, then the other version of copy will be
    called. */
  template<typename PIXELTYPE>
  template<typename SRCTYPE>
  void Image<PIXELTYPE>::copy(const Image<SRCTYPE>& src)
  {
    resize(src.width(), src.height());

    Image<PIXELTYPE>::iterator dest_iter = begin();
    const SRCTYPE* src_iter = src.begin();
    const SRCTYPE* end_iter = src.end();
    for(; src_iter != end_iter; src_iter++, dest_iter++) {
      (*dest_iter) = static_cast<PIXELTYPE>(*src_iter);
    }
  }

  typedef Image<double> Matrix;
} // namespace csucv
#endif // IMAGE_TPP_DEFINED
