#pragma once
#include "Libs.h"
#include <type_traits>
#include "Vec2.h"
#include <iomanip>

class Matrix {
protected:
	double** arr; //In this array are stored values of matrix
	Vec2<unsigned> size;
	/* size.y - quantity of lines
	size.x - quantity of columns	*/
private:
	bool remFlag = true; 
	bool isVector;
	/*
	If we've used std::move on any Matrix object
	it's necessary to block deallocation of arr, when destructor is calling, 
	*/
	static void deallocate2DArray(double**& arr, unsigned size_y); //Dealocating double** arr
public:
	Matrix(unsigned y_size, unsigned x_size); 
	Matrix(Vec2<unsigned>size); //this constructor is equivalent to the above
	Matrix(const Matrix& mat);
	~Matrix();
	//Turning off deallocating of arr at the end of life of object
	inline void blockDeallocation() { remFlag = false; } 

	void mulitiplyByScalar(double scalar);
	Matrix getMultipliedByScalar(double scalar);
	Matrix multiply(Matrix const &B);
	Matrix transpose(); 
	void interchangeRows(unsigned r1, unsigned r2);
	void addRow(unsigned baseRow, unsigned addedRow, double multiplier);
	
	
	double getVectorLength(); //if matrix has dimension 
	void normalizeVector();
	double getScalarProduct(const Matrix& matrix);
	Matrix findPerpendicularVector();



	inline const Vec2<unsigned>& getSize()const { return size; }
	//Easy way to have acces to specific element of arr. Arr is still protected
	double& operator()(unsigned y, unsigned x); 
	Matrix& operator=(Matrix && B);
	Matrix& operator-=(const Matrix& matrix);
	//Matrix& operator=(Matrix B);
	friend std::ostream& operator<<(std::ostream& output, const Matrix& vec);
	void clear(); //Fill the matrix with zeros
	bool getIsVector() const;
	double** getArrPointer() const;
};

