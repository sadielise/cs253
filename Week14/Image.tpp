/* File Image.tpp */
#ifndef IMAGE_TPP_DEFINED
#define IMAGE_TPP_DEFINED
#include<ImageIterator.tpp>
#include<vector>
using std::vector;
template<typename PIXEL>
class Window;
template<typename PIXEL>
class Image {
public:
typedef ImageIterator<PIXEL> iterator;
Image() : rows(0), cols(0) {}
Image(unsigned int row_count, unsigned int col_count)
: data(NULL) { AllocateMemory(row_count, col_count); }
Image(unsigned int row_count, unsigned int col_count,
PIXEL init_value) : data(NULL)
{ AllocateMemory(row_count, col_count); Set(init_value); }
Image(const Image<PIXEL>& src) : data(NULL)
{ AllocateMemory(src.rows, src.cols); Copy(src); }
virtual ~Image() { DeAllocateMemory(); }
inline unsigned int Rows() const {return rows;}
inline unsigned int Cols() const {return cols;}
inline unsigned int Size() const {return size;}
virtual unsigned int EndOfRowIncrement() const {return 1;}
PIXEL& operator() (unsigned int row, unsigned int col)
{return row_ptrs[row][col];}
const PIXEL& operator() (unsigned int row, unsigned int col) const {return row_ptrs[row][col];}
bool Inside(unsigned int row, unsigned int col) const
{return ((row < rows) && (col < cols));}
PIXEL& at(unsigned int row, unsigned int col)
{ if (Inside(row, col)) return row_ptrs[row][col];
else throw std::exception();}
const PIXEL& at(unsigned int row, unsigned int col) const
{if (Inside(row, col)) return row_ptrs[row][col];
else throw std::exception();}/* Continuation (Page #2) of File Image.tpp */
bool empty() const {return (size == 0);}
iterator begin()
{ return ImageIterator<PIXEL>(data, cols, EndOfRowIncrement()); }
iterator end()
{ return ImageIterator<PIXEL>(data+size, cols, EndOfRowIncrement()); }
Window<PIXEL> GetWindow(unsigned int start_row,
unsigned int start_col,
unsigned int height,
unsigned int width);
void Set(PIXEL value);
protected:
void AllocateMemory(unsigned int row_count, unsigned int col_count);
void DeAllocateMemory();
template<typename OTHER_PIXEL>
void Copy(const Image<OTHER_PIXEL>& source_image);
int rows;
int cols;
int size;
PIXEL* data;
PIXEL** row_ptrs;
};
#include <Window.tpp>/* Continuation (Page #3) of Image.tpp */
template<typename PIXEL>
void Image<PIXEL>::AllocateMemory(unsigned int row_count, unsigned int
col_count)
{
if (data != NULL) DeAllocateMemory();
rows = row_count;
cols = col_count;
size = rows * cols;
data = new PIXEL[size];
row_ptrs = new PIXEL*[rows];
PIXEL* data_iter = data;
PIXEL** end = row_ptrs + rows;
for(PIXEL** row_iter = row_ptrs;
row_iter != end;
row_iter++, data_iter += cols) {
(*row_iter) = data_iter;
}
}
template<typename PIXEL>
void Image<PIXEL>::DeAllocateMemory()
{
rows = 0;
cols = 0;
delete [] data;
data = NULL;
delete [] row_ptrs;
}
template<typename PIXEL>
void Image<PIXEL>::Set(PIXEL value)
{
PIXEL* end = data + size;
for(PIXEL* ptr = data; ptr != end; ptr++) {
(*ptr) = value;
}
}/* Continuation (Page #4) of Image.tpp */
template<typename PIXEL>
template<typename OTHER_PIXEL>
void Image<PIXEL>::Copy(const Image<OTHER_PIXEL>& source_image)
{
OTHER_PIXEL* src_ptr = source_image.data;
PIXEL* end = data + size;
for(PIXEL* dest_ptr = data;
dest_ptr != end;
dest_ptr++, src_ptr++) {
(*dest_ptr) = static_cast<PIXEL>(*src_ptr);
}
}
template<typename PIXEL>
Window<PIXEL> Image<PIXEL>::GetWindow(unsigned int start_row,unsigned int start_col,unsigned int height,unsigned int width)
{
return Window<PIXEL>(*this, data, start_row,
start_col, height, width);
}
#endif // IMAGE_TPP_DEFINED

