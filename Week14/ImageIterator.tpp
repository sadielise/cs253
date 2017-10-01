/* File ImageIterator.tpp */
#ifndef IMAGE_ITERATOR_TPP_DEFINE
#define IMAGE_ITERATOR_TPP_DEFINE
#include<cstring>
#include<iostream>
using std::cout;
using std::endl;
template<typename PIXEL>
class ImageIterator {
public:
ImageIterator(PIXEL* start, unsigned int columns, unsigned int
eof_incr)
: ptr(start), cols(columns), end_of_row_increment(eof_incr), ctr(0) {}
~ImageIterator() {ptr = NULL;}
PIXEL& operator * () {return *ptr;}
ImageIterator<PIXEL>& operator ++ ();
bool operator == (const ImageIterator<PIXEL>& other)
{return (ptr == other.ptr);}
bool operator != (const ImageIterator<PIXEL>& other)
{return (ptr != other.ptr);}
protected:
PIXEL* ptr;
unsigned int cols;
unsigned int end_of_row_increment;
unsigned int ctr;
};
template<typename PIXEL>
ImageIterator<PIXEL>& ImageIterator<PIXEL>::operator ++ ()
{
if ((ctr % cols) != 0) {
ptr++;
ctr++;
}
else {
ptr += end_of_row_increment;
ctr = 0;
}
return *this;
}
#endif // IMAGE_ITERATOR_TPP_DEFINE
