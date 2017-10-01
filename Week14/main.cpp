/* FILE main.cpp */
#include <Image.tpp>
#include <Window.tpp>
#include<iostream>
using std::cout;
using std::endl;
#include<sstream>
using std::istringstream;
int main(int argc, char* argv[])
{
if (argc != 2) return -1;
istringstream istr(argv[1]);
int index;
istr >> index;
if (istr.fail()) return -2;
switch(index) {
case 0: {
Image<int> img(3, 5, 0);
Window<int> win = img.GetWindow(0, 4, 2, 2);
for(int r=0; r < 2; r++) {
for(int c=0; c < 2; c++) {
win(r,c) = 1;
}
}
Image<int>::iterator end = img.end();
for(Image<int>::iterator iter = img.begin();
iter != end;
++iter) {
cout << *iter << " ";
}
cout << endl;
break;
}case 1: {
Image<int> img(3, 5, 0);
Window<int> win = img.GetWindow(2, 4, 2, 2);
for(int r=0; r < 2; r++) {
for(int c=0; c < 2; c++) {
win(r,c) = 1;
}
}
Image<int>::iterator end = img.end();
for(Image<int>::iterator iter = img.begin();
iter != end;
++iter) {
cout << *iter << " ";
}
cout << endl;
break;
}
case 2: {
Image<int> img;
Window<int> win = img.GetWindow(0, 0, 2, 2);
for(int r=0; r < 2; r++) {
for(int c=0; c < 2; c++) {
win(r,c) = 1;
}
}
Image<int>::iterator end = img.end();
for(Image<int>::iterator iter = img.begin();
iter != end;
++iter) {
cout << *iter << " ";
}
cout << endl;
}
}
}

