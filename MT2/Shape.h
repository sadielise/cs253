#ifndef SHAPE_H
#define SHAPE_H
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;

class Vertex {

public:
	//vertex constructor
	Vertex(int X, int Y) : x(X), y(Y) {cout << "Vertex Constructor:" << x << "," << y << endl; vertex_ctr++;}
	~Vertex() {cout << "Vertex Destructor:" << x << "," << y << endl; vertex_ctr--;}

	//vertex copy constructor
	Vertex(const Vertex& v) : x(v.x), y(v.y) {cout << "Vertex Copy Constructor:" << x << "," << y << endl; vertex_ctr++;}
	//returns constant reference to x
	const int& X() const {return x;}
	//returns returns reference to y
	int& Y() {return y;}
	//returns value of vertex_ctr
	int Ctr() const {cout << "vertex" << endl; return vertex_ctr;}
	//there is only one value for vertex_ctr b/c it's static
	static int vertex_ctr;

protected:
	int x;
	int y;
};

class Shape {

public:
	//shape constructor, increments shape_ctr
	Shape() {cout << "Shape Constructor" << endl; shape_ctr++;}
	//shape destructor, decrements shape_ctr
	~Shape() {cout << "Shape Destructor" << endl; shape_ctr--;}

	//pure virtual function for finding Area
	virtual double Area() const = 0;
	//returns 9
	double Perimeter() const {return 9;}
	//returns shape_ctr
	int Ctr() const {cout << "shape" << endl; return shape_ctr;}
	//returns pointer to Shape
	Shape* ThisShape() {return this;}

protected:
	//there is only one value for shape_ctr b/c it's static
	static int shape_ctr;
};
	

// polygon class, inherits Shape
class Polygon : public Shape {

public:
	//polygon constructor
	Polygon() {cout << "Polygon Constructor" << endl; shape_ctr--;}
	 //Polygon() {cout << shape_ctr << endl; shape_ctr--;}
	~Polygon() {cout << "Polygon Destructor" << endl; shape_ctr++;}
	 //~Polygon() {cout << shape_ctr << endl; shape_ctr++;}
	//Polygon(const Polygon& p) {cout << "Polygon Copy Constructor" << endl;}

	bool operator== (const Polygon& rhs) {cout << "this is equal!" << endl; return true;}
	
	//implementing pure virtual function from shape
	virtual double Area() const {return vertices.size() * vertices.size();}
	//returns shape_ctr from Shape class, overloading from Shape
	virtual double Perimeter() {return Shape::shape_ctr;}
	//add vertex to vertices vector
	void Add(Vertex v) {vertices.push_back(v);}
	//returns constant reference to a Vertex at index i in vertices
	const Vertex& vertex(int i) {return vertices.at(i);}

protected:
	vector<Vertex> vertices;
};

// circle class, inherits Shape
class Circle : public Shape {

public:
	Circle() {cout << "Circle Constructor" << endl;}
	~Circle() {cout<< "Circle Destructor" << endl;}
	Circle(const Circle& c) {cout << "Circle Copy Constructor" << endl;}
	virtual double Area() const {return 9.87;}
	virtual double Perimeter() const {return 6.28;}

protected:
};

class Color {

public:
	Color() {cout << "Color Constructor" << endl;}
	~Color() {cout << "Color Destructor" << endl;}
	int Value() const {return value;}
	Color* ThisColor() {return this;}
	
protected:
	int value;
};

// ColorCircle class, inherits Circle and Color
class ColorCircle : public Circle, public Color {

public:
	ColorCircle() {cout << "ColorCircle Constructor" << endl;}
	~ColorCircle() {cout << "ColorCircle Destructor" << endl;}
};

// ColorPolygon class, inherits Polygon, public Color
class ColorPolygon : public Polygon, public Color {

public: 
	ColorPolygon() {cout << "ColorPolygon Constructor" << endl;}
	ColorPolygon(const ColorPolygon& cp) {cout << "ColorPolygon Copy Constructor" << endl;}
	~ColorPolygon() {cout << "ColorPolygon Destructor" << endl;}
};


std::ostream& operator<< (std::ostream& os, const Polygon& p) {os << "polygon"; return os;}
bool operator== (const Polygon& lhs, const Polygon& rhs) {cout << "equal" << endl; return true;}

#endif // SHAPE_H
