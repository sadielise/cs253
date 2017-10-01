#ifndef MATRIX_H_INCLUDE
#define MATRIX_H_INCLUDE

#include<iostream>
#include<vector>
#include <tuple>
#include <string>

using namespace std;

class Matrix
{
	public:
	// This is the no argument constructor. It'll create a [1 x 1] matrix with element 0.
		Matrix ();		
	// The 2nd constructor will take 2 values: r: # of rows; c: # of columns. Create a [r x c] matrix with all random numbers.	
		Matrix (int r, int c);
		
	// The 3rd constructor is mostly same as 2nd one except it takes an additional argument, a number, to fill up the matrix.
		Matrix (int r, int c, double d);
		
	// The 4th constructor will take a tuple as matrix dimension and a string of double to create a matrix. 
		Matrix (tuple<int,int,string >);	
		
	// The destructor
		~Matrix();
		
		inline int getMatrixSize() const {return row*col;}
		inline tuple <int,int> getMatrixDim() const {return make_tuple(row, col);}

	// Return martix element
		inline int getVal(int r, int c) const {return matrix[r][c];}
	// Print method for the class	
		void printMatrix(ostream & out) const;	
		
	// Overload the '+=' operator	
		Matrix & operator+=(const Matrix &);
		
	// Overload the '==' operator
		bool operator==(const Matrix &);
		
	// Override the insertion operator(<<) as a friend function
		friend ostream & operator<< (ostream & out, const Matrix &);
		
	// Overload the '+' operator as a friend function
		friend Matrix operator+(const Matrix & , const Matrix & );
		
	// Check if two matrices can be multiplied
		bool mulPossible(const Matrix &);
		
	// Check if two matrices can be added
		bool addPossible(const Matrix &);	
		
	// Overload the '*' operator as a friend function
		friend Matrix operator*(const Matrix & , const Matrix & );		
		
		
	private:
		int row, col;
		vector< vector<double> > matrix;
};
#endif // MARTIX_H_INCLUDE
