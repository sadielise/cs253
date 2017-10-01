#ifndef IMAGE_TPP
#define IMAGE_TPP

#include<cstddef>
#include<memory>
#include<iostream>
using std::shared_ptr;
using std::cout;
using std::endl;

template<typename PIXEL>
class Window {
public:
  Window() : width(0), height(0), size(0), rows(NULL) {}
  Window(PIXEL** row_ptrs, unsigned int _width, unsigned int _height) : width(_width), height(_height), size(width*height), rows(row_ptrs) {}
  ~Window() {delete [] rows; rows = NULL;}

  // simple acessors
  int Width() const {return width;}
  int Height() const {return height;}
  int Size() const {return size;}
  bool empty() const {return size == 0;}

  // 2D random access
  inline const PIXEL& operator () (unsigned int x, unsigned int y) const {return rows[y][x];}
  inline PIXEL& operator () (unsigned int x, unsigned int y) {return rows[y][x];}
  inline const PIXEL& at (unsigned int x, unsigned int y) const {if ((x >= width) || (y >= height)) throw std::exception(); return rows[y][x];}
  inline PIXEL& at (unsigned int x, unsigned int y) {if ((x >= width) || (y >= height)) throw std::exception(); return rows[y][x];}

protected:
  unsigned int width;
  unsigned int height;
  unsigned int size;
  PIXEL** rows;
};

template<typename PIXEL>
class Image : public Window<PIXEL> {
public:
  Image() {allocateMemory(0,0);}
  Image(unsigned int width, unsigned int height) {allocateMemory(width, height);}
  Image(unsigned int width, unsigned int height, const PIXEL& value) {allocateMemory(width, height); fill(value);}
  Image(const Image<PIXEL>& img) {cout << "copy constructor" << endl; allocateMemory(img.Width(), img.Height()); copyMemory(img);}
  ~Image() {deallocateMemory();}
  Image<PIXEL>& operator = (const Image& img) {deallocateMemory(); allocateMemory(img.Width(), img.Height()); copyMemory(img); return *this;}

  // 1D random access
  const PIXEL& operator [] (unsigned int index) const {cout << "const" << endl; return data[index];}
  PIXEL& operator [] (unsigned int index) {cout << "not const" << endl; return data[index];}
  const PIXEL& at(unsigned int index) const {cout << "const" << endl; if (index >= this->size) throw std::exception(); return data[index];}
  PIXEL& at (unsigned int index) {cout << "not const" << endl; if (index >= this->size) throw std::exception(); return data[index];}

  // 2D Window Access
  static shared_ptr<Window<PIXEL> > SubWindow(shared_ptr<Image<PIXEL> > img_ptr, int start_x, int start_y, int width, int height);

  // STL methods
  void swap(Image<PIXEL>& other_image);

protected:
  void allocateMemory(unsigned int w, unsigned int h);
  void deallocateMemory();
  void copyMemory(const Image<PIXEL>& img);
  void fill(const PIXEL& value);

  PIXEL* data;
};

/// Allocate internal memory for image; does not deallocate previous memory
template<typename PIXEL>
void Image<PIXEL>::allocateMemory(unsigned int w, unsigned int h)
{
  this->width = w;
  this->height = h;
  this->size = w * h;
  if (this->empty()) {
    data = NULL;
    this->rows = NULL;
  }
  else {
    data = new PIXEL[this->size];
    this->rows = new PIXEL*[this->height];
    
    PIXEL** rows_ptr = this->rows;
    PIXEL* data_ptr = data;
    PIXEL* end = data + this->size;
    for(; data_ptr < end; rows_ptr++, data_ptr += this->width) {
      *rows_ptr = data_ptr;
    }
  }
}

template<typename PIXEL>
void Image<PIXEL>::deallocateMemory()
{
  this->width = 0;
  this->height = 0;
  this->size = 0;
  delete [] this->rows;
  this->rows = NULL;
  delete [] data;
  data = NULL;
}

// assumes size match
template<typename PIXEL>
void Image<PIXEL>::copyMemory(const Image<PIXEL>& img) 
{
  PIXEL* ptr1 = data;
  PIXEL* ptr2 = img.data;
  PIXEL* end = data + this->size;
  for(; ptr1 < end; ptr1++, ptr2++) {
    *ptr1 = *ptr2;
  }
}

template<typename PIXEL>
void Image<PIXEL>::fill(const PIXEL& value) 
{
  PIXEL* data_ptr = data;
  PIXEL* end = data + this->size;
  for(; data_ptr < end; data_ptr ++) {
    *data_ptr = value;
  }
}

template<typename PIXEL>
void Image<PIXEL>::swap(Image& other_img)
{
  int temp_width = this->width;
  int temp_height = this->height;
  int temp_size = this->size;
  PIXEL* temp_data = data;
  PIXEL ** temp_rows = this->rows;
  this->width = other_img.Width();
  this->height = other_img.Height();
  this->size = other_img.Size();
  data = other_img.data;
  this->rows = other_img.rows;
  other_img.width = temp_width;
  other_img.height = temp_height;
  other_img.size = temp_size;
  other_img.data = temp_data;
  other_img.rows = temp_rows;
}

template<typename PIXEL>
shared_ptr<Window<PIXEL> > Image<PIXEL>::SubWindow(shared_ptr<Image<PIXEL> > img_ptr, int start_x, int start_y, int width, int height)
{
  PIXEL** row_ptr = new PIXEL*[height];
  for(unsigned int i=0; i < height; i++) {
    row_ptr[i] = img_ptr->Window<PIXEL>::rows[start_y+i]+start_x;
  }
  ::Window<PIXEL>* ptr = new ::Window<PIXEL>(row_ptr, width, height);
  shared_ptr<::Window<PIXEL> > window_ptr(img_ptr, ptr);
  delete ptr;
  return window_ptr;
}
#endif // IMAGE_TPP
