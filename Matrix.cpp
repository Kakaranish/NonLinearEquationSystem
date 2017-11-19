#include "Matrix.h"

void Matrix::clear() { // Filling the array with 0
	for (unsigned i = 0; i < size.y; i++)
		for (unsigned j = 0; j < size.x; j++)
			arr[i][j] = 0;
}

void Matrix::deallocate2DArray(double**& arr, unsigned size_y) { // Deallocating memory 
	for (unsigned i = 0; i < size_y; i++)
		delete[] arr[i];
	delete[] arr;
}

Matrix::Matrix(unsigned y_size, unsigned x_size) {
	
	isVector = false;
	if(x_size == 1 || y_size == 1)
		isVector = true;
	
	arr = new double*[y_size];
	for (unsigned i = 0; i < y_size; i++)
		arr[i] = new double[x_size];
	size = Vec2<unsigned>(x_size, y_size);
	clear();
}


Matrix::Matrix(Vec2<unsigned>size): size(size) {
	isVector = false;
	if(size.x == 1 || size.y == 1)
		isVector = true;
	
	arr = new double*[size.y];
	for (unsigned i = 0; i < size.y; i++)
		arr[i] = new double[size.x];
	clear();
}

Matrix::~Matrix() {
	if (!remFlag)
		return;
	deallocate2DArray(this->arr, size.y);
}

Matrix::Matrix(const Matrix& matrix) {
	arr = new double*[matrix.size.y];
	size = matrix.size;

	for (int i = 0; i < matrix.size.y; i++) {
		arr[i] = new double[matrix.size.x];
		for (int j = 0; j < matrix.size.x; j++)
			arr[i][j] = matrix.arr[i][j];
	}	
	isVector = matrix.isVector;
}

Matrix Matrix::multiply(Matrix const &B) {
	
	if (size.x != B.size.y) {
		std::cout << "Unable to multiply matrixes! Wrong dimensions!" << std::endl;
		exit(-1);
	}
	Matrix rMatrix(size.y, B.size.x);
	for (unsigned i = 0; i < size.y; i++) //iterate A matrix through columns
		for (unsigned j = 0; j < B.size.x; j++) { //iterate B matrix through rows
			double sum = 0;
			for (unsigned k = 0; k < size.x; k++)
				sum += (arr[i][k] * B.arr[k][j]);
			rMatrix(i, j) = sum;
		}

	rMatrix.blockDeallocation();
	//return rMatrix;
	return std::move(rMatrix);
}

Matrix Matrix::transpose() {
	Matrix tMatrix(size.x, size.y);
	tMatrix.blockDeallocation();

	for (unsigned i = 0; i < size.x; i++) 
		for (unsigned j = 0; j < size.y; j++)
			tMatrix(i,j) = arr[j][i];
	return std::move(tMatrix);
}

void Matrix::interchangeRows(unsigned r1, unsigned r2) {
	if (r1 >= size.y || r2 >= size.y) {
		std::cout << "Unable to interchange rows!" << std::endl;
		exit(-1);
	}
	if (r1 == r2)
		return;
	for (unsigned i = 0; i < size.x; i++)
		std::swap(arr[r1][i], arr[r2][i]);	
}

void Matrix::addRow(unsigned baseRow, unsigned addedRow, double multiplier) {
	for (unsigned i = 0; i < size.x; i++)
		arr[baseRow][i] += arr[addedRow][i] * multiplier;
}

double& Matrix::operator()(unsigned y, unsigned x) {
	return arr[y][x];
}

Matrix& Matrix::operator=(Matrix && B){
	for(unsigned i=0;i<size.y;i++)
		delete[] arr[i];
	delete[] arr;

	this->size = B.size;
	isVector = B.isVector;

	arr = new double*[size.y];
	for(unsigned i=0;i<size.y;i++){
		arr[i] = new double[size.x];
		for(unsigned j=0;j<size.x;j++)
			arr[i][j] = B.arr[i][j];
	}
	return *this;
}

double Matrix::getScalarProduct(const Matrix& matrix){
	if(!matrix.getIsVector() || !this->isVector)
		return -1;
	if(matrix.size != this->size)
		return -1;
	
	double sum = 0;
	if(size.x > 1)
		for(int i=0;i<size.x;i++)
			sum += arr[0][i] * matrix.getArrPointer()[0][i];
	else
		for(int i=0;i<size.y;i++)
			sum += arr[i][0] * matrix.getArrPointer()[i][0];

	return sum;
}

double Matrix::getVectorLength(){
	if(!isVector)
		return -1;
	
	double sum;
	if(size.x > 1){
		for(unsigned i=0;i<size.x;i++)
			sum += pow(arr[0][i],2);
	}else{
		for(unsigned i=0;i<size.y;i++)
			sum += pow(arr[i][0],2);
	}
	return sqrt(sum);
	
}
void Matrix::mulitiplyByScalar(double scalar){
	Matrix temp(*this);
	for(unsigned i=0;i<size.y;i++)
		for(unsigned j=0;j<size.x;j++)
			temp(i,j) = temp(i,j) * scalar;
	temp.blockDeallocation();
	*this = std::move(temp);
}

void Matrix::normalizeVector(){
	if(!isVector)
		return;
	this->mulitiplyByScalar(1.f/getVectorLength());
}

Matrix Matrix::findPerpendicularVector(){
	if(!isVector)
		Matrix(0,0);
	Matrix temp(this->size);
	double sum = 0;
	if(size.x > 1)
		for(unsigned i=0;i<size.x-1;i++){
			temp(0,i) = 1;
			sum += temp(0,i) * arr[0][i];
		}
			
	else
		for(unsigned i=0;i<size.y-1;i++){
			temp(i,0) = 1;
			sum += temp(i,0) * arr[i][0];
		}
	double last;
	if(size.x > 1){
		last = - (sum / arr[0][size.x-1]);
		temp(0, size.x - 1) = last;
	}
		
	else{
		last = -(sum / arr[size.y-1][0]);
		temp(size.y - 1, 0 ) = last;
	}

	temp.blockDeallocation();
	return std::move(temp);

}

Matrix Matrix::getMultipliedByScalar(double scalar){
	Matrix temp(*this);
	for(unsigned i=0;i<size.y;i++)
		for(unsigned j=0;j<size.x;j++)
			temp(i,j) = temp(i,j) * scalar;
	temp.blockDeallocation();
	return std::move(temp);
}
Matrix& Matrix::operator-=(const Matrix& matrix){
	if(this->size != matrix.size){
		perror("Different matrix dimensions!");
		exit(-1);
	}
	for(unsigned i=0;i<size.y;i++)
		for(unsigned j=0;j<size.x;j++)
			arr[i][j] -= matrix.arr[i][j];
	return *this;
}

std::ostream& operator<<(std::ostream& output, const Matrix& _m) {
	for (unsigned i = 0; i < _m.size.y; i++) {
		for (unsigned j = 0; j < _m.size.x; j++)
			output << std::setw(8) << _m.arr[i][j] << " ";
		output << std::endl;
	}
	return output;
}

bool Matrix::getIsVector() const{
	return isVector;
}



double** Matrix::getArrPointer() const{
	return arr;
}