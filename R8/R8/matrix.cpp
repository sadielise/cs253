#include<cstdlib>
#include"matrix.h"
#include<sstream>

using namespace std;

//Implementation of 1st constructor. 
Matrix::Matrix ()
{
	row = 1; col = 1;
	matrix.push_back( vector<double>());
	matrix[0].push_back(0);
}

//Implementation of 2nd constructor. 
Matrix::Matrix (int r, int c)
{
	row = r; col = c;
	for (int i=0; i<r; ++i)
	{
		matrix.push_back( vector<double>());
		for (int j=0; j<c; ++j)
			matrix[i].push_back(rand() % 100);
	}		
}

// Implementation of 3rd constructor.
Matrix::Matrix (int r, int c, double d)
{
	row = r; col = c;
	for (int i=0; i<r; ++i)
	{
		matrix.push_back( vector<double>());
		for (int j=0; j<c; ++j)
			matrix[i].push_back(d);
	}		
}

// Implementation of 4th constructor
Matrix::Matrix ( tuple<int, int , string > t)
{		
	row = get<0>(t);
	col = get<1>(t);
	stringstream ss(get<2>(t));
	int counter=0;	
	vector<double> nos;
	for (double d; ss >> d;)		
		nos.push_back(d);	
		
	for (int r=0; r< row; ++r)
	{
		matrix.push_back( vector<double>());
		for (int c=0; c< col; ++c)
		{
			matrix[r].push_back(nos[ counter ]);
			++counter;
		}	
	}	
}

// Implementation of the destructor
Matrix::~Matrix()
{
	cout << "Matrix is being deleted" << endl;
}

//printMatrix() method
void Matrix::printMatrix(ostream & out = cout) const
{
	for (int i=0; i<row; ++i)
	{
		for (int j=0; j<col; j++)
			out << matrix[i][j] << "\t";
		out << '\n';
	}	
}

//Overload the '+=' operator
Matrix & Matrix::operator+=(const Matrix & rhs)
{
	for (int r=0;r<row; ++r)
	{
		for (int c=0;c<col; ++c)
			matrix[r][c] = matrix[r][c] + rhs.matrix[r][c];
	}
	return *this;
}

//Overload the '+' operator
Matrix operator+(const Matrix & lhs, const Matrix & rhs)
{
	Matrix temp = lhs;
	for (int r=0;r<lhs.row; ++r)
	{
		for (int c=0;c<lhs.col; ++c)
			temp.matrix[r][c] = lhs.matrix[r][c] + rhs.matrix[r][c];
	}
	return temp;
}

bool Matrix:: operator==(const Matrix & rhs)
{
	if( (row != rhs.row) || (col != rhs.col) )
		return false;	
	for(int r=0; r<row; ++r)
	{
		for(int c=0; c<col; ++c)
		{			
			if(matrix[r][c] != rhs.matrix[r][c])
				return false;
		}
	}
	return true;		
}

// Check for matrix multiplication
bool Matrix::mulPossible(const Matrix & rhs)
{		
	// Make sure matrix dimensions are compatible for multiplication	
	if( col != rhs.row )	
		return false;	
	else
		return true;
}

// Check for matrix addition
bool Matrix::addPossible(const Matrix & rhs)
{		
	// Make sure matrix dimensions are compatible for addition	
	if( ( row != rhs.row ) || ( col != rhs.col ) )	
		return false;	
	else
		return true;
}

//Overload the '*' operator
Matrix operator*(const Matrix & lhs, const Matrix & rhs)
{
	tuple<int,int> lhs_dim = lhs.getMatrixDim();
	tuple<int,int> rhs_dim = rhs.getMatrixDim();	
	Matrix temp( get<0>(lhs_dim), get<1>(rhs_dim), 0);
	
	for (int r = 0; r < get<0>(lhs_dim); ++r)
	{
		for (int c = 0; c < get<1>(rhs_dim); ++c)
		{			
			for (int r1 = 0; r1 < get<0>(rhs_dim); ++r1)			
				temp.matrix[r][c] = temp.matrix[r][c] + ( lhs.matrix[r][r1] * rhs.matrix[r1][c] );							
		}
	}
	return temp;
}

// Override the insertion operator(<<)
ostream & operator<< (ostream & out, const Matrix & m)
{
	m.printMatrix( out );
	return out;
}

