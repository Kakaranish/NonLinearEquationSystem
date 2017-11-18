#include "Libs.h"
#include "Matrix.h"
#include "Utility.h"


Matrix* loadMatrix(std::string filename) {
	std::fstream file;
	file.open(filename, std::fstream::in | std::fstream::out);

	if (!file.is_open()) {
		std::cout << "Unable to load matrix from file!" << std::endl;
		exit(-1);
	}

	int i = 0, j, n=0;
	std::vector<double> numbers;
	std::stringstream ss;
	Matrix *A = nullptr;

	for (std::string nextLine; std::getline(file, nextLine);i++, j=0) {
		ss.str(std::string());
		ss.clear();
		ss << nextLine;
		std::string nextNumber;

		while (std::getline(ss, nextNumber, ' ')) {
			if (!i) {
				n++;
				numbers.push_back(std::stod(nextNumber));
			}
			else {
				(*A)(i, j) = std::stod(nextNumber);
				j++;
			}
		}
		if (!i) {
			A = new Matrix(n, n);
			std::cout << numbers.size() << std::endl;
			for (j = 0; j < n; j++)
				(*A)(0, j) = numbers[j];
		}
	}
	file.close();
	return A;
}

int main(int argc, char * argv[]) {
	srand(static_cast<int>(time(NULL)));
	int n;

	std::cout << "**************************************" << std::endl;
	std::cout << "*** PROGRAM WYKONAL STANISLAW GRUZ ***" << std::endl;
	std::cout << "**************************************" << std::endl;
	std::cout << "1) Jesli wymiar macierzy jest <= 0, wowczas zostaniesz poproszony o podanie nazwy pliku z macierza!" << std::endl;
	std::cout << "2) Jesli wymiar macierzy >0, podawaj kolejne wiersze w postaci:" << std::endl;
	std::cout << "1 2 3 4 i na koncu po podaniu wiersza wciskamy ENTER!" << std::endl;

	std::cout << "Podaj wymiar macierzy: ";
	std::cin >> n;

	if (std::cin.fail())
		exit(-1);

	std::cout << std::endl << std::endl;

	Matrix* A = nullptr;
	if (n <= 0) {
		A = loadMatrix("matrix.txt");
		n = A->getSize().x;
	}
	else {
		A = new Matrix(n,n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				std::cin >> (*A)(i, j);
	}
	
	Matrix L(n, n), U(n, n), P(n, n);
	computeLU(*A, L, U, P);

	std::cout << "A = " << std::endl;
	std::cout << *A << std::endl;
	
	std::cout << "L = " << std::endl;
	std::cout << L << std::endl;

	std::cout << "U = " << std::endl;
	std::cout << U << std::endl;

	std::cout << "P = " << std::endl;
	std::cout << P << std::endl;
	
	std::cout << "Sprawdzenie: " << std::endl;
	std::cout << "PA = " << std::endl << P.multiply(*A) << std::endl;
	std::cout << "LU = " << std::endl << L.multiply(U) << std::endl;

	_getch();
	return 0;
}


/*
Matrix B(n, n);
B(0, 0) = 4;
B(0, 1) = 1;
B(0, 2) = 0;

B(1, 0) = 5;
B(1, 1) = 4;
B(1, 2) = 1;

B(2, 0) = 0;
B(2, 1) = 1;
B(2, 2) = 4;
*/

//Test
/*
Matrix A(4, 4), L(n, n), U(n, n), P(n, n);
A(0, 0) = 2;
A(0, 1) = 1;
A(0, 2) = 1;
A(0, 3) = 0;

A(1, 0) = 4;
A(1, 1) = 3;
A(1, 2) = 3;
A(1, 3) = 1;

A(2, 0) = 8;
A(2, 1) = 7;
A(2, 2) = 9;
A(2, 3) = 5;

A(3, 0) = 6;
A(3, 1) = 7;
A(3, 2) = 9;
A(3, 3) = 8;
*/