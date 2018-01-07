#include <iostream>
#include <conio.h>
#include "Utility.h"
#include "Matrix.h"
#include "VectorOfFunctions.h"
#include <vector>
#include <functional>

/*
{ 2y^2+x^2 = 2
{ (x-1)^2 +(y-1/2)^2=1/4

*/

int main(int argc, char * argv[]) {

	

	
	_getch();
	return 0;
}

/*
	std::function<double(std::vector<double>)> f1 = [](std::vector<double> list) {
		double result = 0;
	
		for (auto& x : list)
			result += x;
		return result;
	};

	std::function<double(std::vector<double>)> f2 = [](std::vector<double> list) {
		double result = 0;

		for (auto& x : list)
			result += 2*x;
		return result;
	};


	VectorOfFunctions mF({ func_pair(2,f1),func_pair(2,f2) });
	
	std::vector<double> x = mF.getDefaultArgsVector();
	for (int i = 0; i <x.size(); i++)
		std::cout << x.at(i) << std::endl;
	
	std::cout << mF.computeValuesVector(mF.getDefaultArgsVector()) << std::endl;

*/


/*
//Gaussian Elimination Test
Matrix A(3, 3);
A(0, 0) = -1;
A(0, 1) = 2;
A(0, 2) = 1;
A(1, 0) = 1;
A(1, 1) = -3;
A(1, 2) = -2;
A(2, 0) = 3;
A(2, 1) = -1;
A(2, 2) = -1;


Matrix B(3, 1);
B(0, 0) = -1;
B(1, 0) = -1;
B(2, 0) = 4;

Matrix X(3, 1);

try {
bool hasResult = gauss(A, X, B);
if (hasResult)
std::cout << "Wektor rozwiazan: " << std::endl;
std::cout << X << std::endl;
}
catch (std::exception e) {
std::cout << e.what();
}

*/