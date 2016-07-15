#ifndef _MATRIX_
#define _MATRIX_
#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

class matrix
{
private:
	int row;                     //æÿ’Û––
	int column;                  //æÿ’Û¡–
	double** data;   
public:
	matrix();
	matrix(int r, int c);
	matrix(int r, int c, double** d,bool dynamic=true);
	matrix(const matrix& m);
	~matrix();

	friend matrix operator*(const double x, const matrix& m);
	matrix operator*(const matrix& m);
	matrix operator+(const matrix& m);
	matrix operator-(const matrix& m); 
	void operator=(const matrix& m);
	const double* operator[](int i);
	friend matrix operator-(const matrix& m);
	friend ostream& operator<<(ostream& os, const matrix& m);         

	matrix T(const matrix& m);                   //æÿ’Û◊™÷√
	bool zeroMatrix();                           // «∑ÒŒ™¡„æÿ’Û
	unsigned int rank();                         //æÿ’Ûµƒ÷»
	matrix rowEchelonForm();					 //Ω◊Ã›–Œæÿ’Û
	matrix standardForm();                       //æÿ’Û±Í◊º–Œ
	void swapRow(int m, int n);      //Ωªªªæÿ’Û––
	void swapColumn(int m, int n);   //Ωªªªæÿ’Û¡–
};

matrix::matrix()
{
	row = 0;
	column = 0;
	data = 0;
}

matrix::matrix(int r, int c)
{
	if(r==0 || c==0)
		throw "Rows and columns can not be zero";
	row = r;
	column = c;
	data = new double*[r];
	for(int i=0; i<r; i++)
	{
		data[i] = new double[c];
	}
}

matrix::matrix(int r, int c, double** d, bool dynamic)
{
	if(r==0 || c==0)
		throw "Rows and columns can not be zero";
	row = r;
	column = c;
	if(d==0)
		throw "Pointer can not be NULL";
	data = new double*[row];
	for(int i=0; i<row; i++)
    {
		data[i] = new double[column];
		if(dynamic)
			for(int j=0; j<column; j++)
			{
					data[i][j] = d[i][j];
			}
		else
			for(int j=0; j<column; j++)
			{
					data[i][j] = *((double*)d+i*c+j);
			}
	}
}

matrix::matrix(const matrix& m)
{
	row = m.row;
	column = m.column;
	
	data = new double*[row];
	for(int i=0; i<row; i++)
    {
		data[i] = new double[column];
		for(int j=0; j<column; j++)
			data[i][j] = m.data[i][j];
	}
}   	  
    
matrix::~matrix()
{
	if(data != 0)
	{
		for(int i=0; i<row; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}
}

matrix operator*(const double x, const matrix& m)
{
	double** temp = new double*[m.row];
	for(int i=0; i<m.row; i++)
	{	
		temp[i] = new double[m.column];
		for(int j=0; j<m.column; j++)
			temp[i][j] = m.data[i][j]*x;
	}
	return matrix(m.row,m.column,temp,true);
}
 

matrix matrix::operator*(const matrix& m)
{
	if(column != m.row)
		throw "Matrix dimensions inconsistent";
	double** temp = new double*[row];
	for(int i=0; i<row; i++)
	{
		temp[i] = new double[m.column];
		for(int j=0; j<m.column; j++)
		{
			temp[i][j] = 0.0;
			for(int k=0; k<column; k++)
				temp[i][j] += data[i][k]*m.data[k][j];
		}
	}
	return matrix(row,m.column,temp,true);
}

matrix matrix::operator+(const matrix& m)
{
	if(row!=m.row || column!=m.column)
		throw "Matrix dimensions inconsistent";
	double** temp = new double*[row];
        for(int i=0; i<row; i++)
        {	
        	temp[i] = new double[column];
        	for(int j=0; j<column; j++)
      			temp[i][j] = data[i][j]+m.data[i][j];
       	}
        return matrix(row,column,temp,true);
}                                                                

matrix matrix::operator-(const matrix& m)
{
	if(row!=m.row || column!=m.column)
		throw "Matrix dimensions inconsistent";
   	double** temp = new double*[row];
    for(int i=0; i<row; i++)
    {	
       	temp[i] = new double[column];
       	for(int j=0; j<column; j++)
     		temp[i][j] = data[i][j]-m.data[i][j];
   	}
    return matrix(row,column,temp,true);                  
}                                                          

matrix operator-(const matrix& m)
{
   	double** temp = new double*[m.row];
    for(int i=0; i<m.row; i++)
    {	
       	temp[i] = new double[m.column];
       	for(int j=0; j<m.column; j++)
     		temp[i][j] = -m.data[i][j];
   	}
    return matrix(m.row,m.column,temp,true);   	
}


void matrix::operator=(const matrix& m)
{
	if(data != 0)
	{
		for(int i=0; i<row; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}
	row = m.row;
	column = m.column;
	data = new double*[row];
	for(int i=0; i<row; i++)
	{
		data[i] = new double[column];
		for(int j=0; j<column; j++)
			data[i][j] = m.data[i][j];
	}
}


ostream& operator<<(ostream& os, const matrix& m)
{
	for(int i=0; i<m.row; i++)
	{
		for(int j=0; j<m.column-1; j++)
			os<<m.data[i][j]<<'\t';
		os<<m.data[i][m.column-1]<<std::endl;
	}
	return os;
}


matrix matrix::T(const matrix& m)
{
	double** temp = new double*[m.column];
        for(int i=0; i<column; i++)
        {	
        	temp[i] = new double[row];
        	for(int j=0; j<row; j++)
      			temp[i][j] = data[j][i];
       	}
        return matrix(column,row,temp,true);
}

bool matrix::zeroMatrix()
{
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<column; j++)
		{
			if(data[i][j] != 0.0)
				return false;
		}
	}
	return true;
}


matrix matrix::rowEchelonForm()
{
	int sign = 1;
	int nonZero;
	double factor;
	int currC = -1;
	matrix m = *this;

	for(int i=0; i<m.row-1; i++)
	{
		if(currC<m.column-1)
			currC++;
		nonZero = m.row;
		for(int j=i; j<m.row; j++)
		{
			if(m.data[j][currC] != 0)
			{
				nonZero = j;
				break;
			}
		}
		if(nonZero == m.row)
			continue;
		else if(nonZero>i && nonZero<m.row)
		{
			m.swapRow(nonZero,i);
			sign = -sign;
		}

		for(int k=i+1; k<m.row; k++)
		{
			factor = m.data[k][i]/m.data[i][i];
			for(int l=i; l<m.column; l++)
				m.data[k][l] = m.data[k][l]-m.data[i][l]*factor;
		}
	}
	return m;
}


void matrix::swapRow(int m, int n)
{
	double temp;
	for(int i=0; i<column; i++)
	{
		temp = data[m][i];
		data[m][i] = data[n][i];
		data[n][i] = temp;
	}
}

void matrix::swapColumn(int m, int n)
{
	double temp;
	for(int i=0; i<row; i++)
	{
		temp = data[i][m];
		data[i][m] = data[i][n];
		data[i][n] = temp;
	}
}

const double* matrix::operator[](int m)
{
	return data[m];
}


matrix matrix::standardForm()
{
	matrix m;

	return m;
}

unsigned int matrix::rank()
{
	if(zeroMatrix())
		return 0;
	matrix m = rowEchelonForm();
	bool allZero;
	int i;
	for(i=0; i<m.row; i++)
	{
		allZero = true;
		for(int j=0; j<m.column; j++)
			if(m.data[i][j] != 0.0)
			{
				allZero = false;
				break;
			}
		if(allZero == true)
			break;
	}
	return i;
}



#endif
   
