/* File Window.tpp */
#ifndef WINDOW_TPP_DEFINED
#define WINDOW_TPP_DEFINED
#include<Image.tpp>
template<typename PIXEL>
class Window : public Image<PIXEL> {
public:
typedef ImageIterator<PIXEL> iterator;
Window(Image<PIXEL>& src, PIXEL* data_ptr,
unsigned int start_row, unsigned int start_col,
unsigned int height, unsigned int width);
virtual ~Window<PIXEL>() { this->data = NULL; }
Window<PIXEL>& operator = (const Window<PIXEL>& src);
virtual unsigned int EndOfRowIncrement() const
{return end_of_row_increment;}
protected:
unsigned int end_of_row_increment;
};
template<typename PIXEL>
Window<PIXEL>::Window(Image<PIXEL>& src, PIXEL* data_ptr,
unsigned int start_row, unsigned int start_col,
unsigned int height, unsigned int width)
{
this->rows = height;
this->cols = width;
this->size = height * width;
end_of_row_increment = src.Cols() - width + 1;
this->data = data_ptr + (src.Cols() * start_row) + start_col;
this->row_ptrs = new PIXEL*[height];
PIXEL* data_iter = this->data;
PIXEL** end_iter = this->row_ptrs + height;
for(PIXEL** row_iter = this->row_ptrs;
row_iter != end_iter;
row_iter++, data_iter += src.Cols()) {
(*row_iter) = data_iter;
}
}
/* Continuation of File Window.tpp */
template<typename PIXEL>
Window<PIXEL>& Window<PIXEL>::operator = (const Window<PIXEL>& src)
{
this->rows = src.rows;
this->cols = src.cols;
this->size = src.size;
end_of_row_increment = src.end_of_row_increment;
this->data = src.data;
this->row_ptrs = new PIXEL*[this->rows];
PIXEL* data_iter = this->data;
PIXEL** end_iter = this->row_ptrs + this->rows;
for(PIXEL** row_iter = this->row_ptrs;
row_iter != end_iter;
row_iter++, data_iter += (this->cols + end_of_row_increment)) {
(*this->row_ptrs) = data_iter;
}
}
#endif //
WINDOW_TPP_DEFINED
