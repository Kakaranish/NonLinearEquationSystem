#include "Utility.h"

void computeLU(Matrix _A, Matrix& _L, Matrix& _U, Matrix& _P) {
	//_A - matrix we want to factorize to LU
	// As we can see this matrix is not passed as reference
	//, because we don't want to change original values 
	// while interchanging operations and pivoting.
	//_L - lower triangular matrix
	//_U - upper triangular matrix
	//_P - permutation matrix
	_A.blockDeallocation();

	//Assume _A matrix must be square matrix
	Vec2<unsigned> size = _A.getSize();
	if (size.x != size.y) {
		std::cout << "Can't compute LU factorization!" << std::endl;
		exit(-1);
	}

	//We have to be sure the arrays we want to save results in are empty
	_L.clear();
	_U.clear();
	_P.clear();

	//Setting default values in permuation matrix
	for (unsigned i = 0; i < size.y; i++)
		_P(i, i) = 1;

	//Lambda expression which find the biggest value in column
	auto findGreatestVal = [&](Matrix& tMatrix, Matrix& P, unsigned col)->void {
		std::pair<unsigned, double> max(col, tMatrix(col, col)); //para: nr_wiersza -> wartosc
		for (unsigned i = col; i < tMatrix.getSize().y; i++)
			if (tMatrix(i, col) > max.second) {
				max.first = i;
				max.second = tMatrix(i, col);
			}
		if (max.first != col) {
			tMatrix.interchangeRows(col, max.first);
			P.interchangeRows(col, max.first); 
			_L.interchangeRows(col, max.first);
			_U.interchangeRows(col, max.first);
		}
	};

	for (unsigned i = 0; i < size.x - 1; i++) { //in this case we iterate x 
		findGreatestVal(_A, _P, i); 
		_L(i, i) = 1;
		double multiplier;
		for (unsigned j = i + 1; j < size.y; j++) {// iterating y
			multiplier = _A(j, i) / _A(i, i);
			_A.addRow(j, i, -multiplier);
			_L(j, i) = multiplier;
		}
	}
	_L(size.y - 1, size.x - 1) = 1;

	for (int i = 0; i < size.y; i++)
		for (int j = size.y - 1; j >= i; j--)
			_U(i, j) = _A(i, j);
}