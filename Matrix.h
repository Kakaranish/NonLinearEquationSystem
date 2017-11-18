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

	Matrix multiply(Matrix const &B);
	Matrix transpose(); 
	void interchangeRows(unsigned r1, unsigned r2);
	void addRow(unsigned baseRow, unsigned addedRow, double multiplier);

	
	inline const Vec2<unsigned>& getSize()const { return size; }
	//Easy way to have acces to specific element of arr. Arr is still protected
	double& operator()(unsigned y, unsigned x); 
	friend std::ostream& operator<<(std::ostream& output, const Matrix& vec);
	void clear(); //Fill the matrix with zeros
};

