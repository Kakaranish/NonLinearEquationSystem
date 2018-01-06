#pragma once
#include "Libs.h"
#include <type_traits>
#include "Vec2.h"
#include <iomanip>
#include <random>


class MatrixSize {
private:
	unsigned rowsNum, colNum;
public:
	MatrixSize() : rowsNum(0), colNum(0) {}
	MatrixSize(unsigned rNum, unsigned cNum): rowsNum(rNum), colNum(cNum){}
	unsigned getRowsNum() const { return rowsNum; }
	unsigned getColNum() const { return colNum; }

	//Overloading operators
	bool operator==(const MatrixSize& m_o) {
		return (this->colNum == m_o.colNum && this->rowsNum == m_o.rowsNum) ? true : false;
	}
	bool operator!=(const MatrixSize& m_o) {
		return (this->colNum == m_o.colNum && this->rowsNum == m_o.rowsNum) ? false : true;
	}
	bool operator!=(const MatrixSize& m_o) const {
		return (this->colNum == m_o.colNum && this->rowsNum == m_o.rowsNum) ? false : true;
	}

};
class MatrixException : public std::runtime_error {
private:
	std::string message;
public:
	MatrixException(std::string message) : message(message),std::runtime_error(message){}
	const char* what() const override { return message.c_str(); }
};

class Matrix {

protected:
	double **arr;
	MatrixSize size;
private:
	static void deallocate2DArray(double** arr, unsigned size_y); //Dealocating double** arr
public:
	//Constructors and destructor
	Matrix(unsigned rowNum, unsigned colNum); 
	Matrix(MatrixSize); //this constructor is equivalent to the above
	Matrix(const Matrix&);
	Matrix(Matrix&&) noexcept;
	~Matrix();

	//Operations on matrices
	void mulitiplyByScalar(double scalar);
	Matrix getMultipliedByScalar(double scalar);
	Matrix getMultipliedByMatrix(Matrix const &B);
	Matrix getTransposed(); 
	void interchangeRows(unsigned r1, unsigned r2);
	void addRow(unsigned baseRow, unsigned addedRow, double multiplier);
	

	//Vector functions
	bool isVector() const;
	bool isVerticalVector() const;
	double getVectorLength();
	void normalizeVector();
	//Matrix getNormalizedVector(); //TODO
	double getScalarProduct(const Matrix& matrix);
	Matrix findPerpendicularVector();


	
	//Overloading operators
	double& operator()(unsigned row, unsigned col); //Accessor to specific element of arr
	Matrix& operator=(Matrix && B);
	Matrix& operator-=(const Matrix& matrix);
	friend std::ostream& operator<<(std::ostream& output, const Matrix& vec);
	
	
	//Misc functions
	bool isInitialized();
	void init(); //Fill the matrix with zeros
	void initRandomValues(int intervalBeg, int intervalEnd);
	MatrixSize getSize() const { return size; }
	void setArrToNullptr() { arr = nullptr; }
	double** getArrPtr() const { return arr; }
};

