#include <iostream>
#include <conio.h>
#include "Utility.h"
#include "Matrix.h"
#include "VectorOfFunctions.h"
#include <vector>
#include <functional>



int main(int argc, char * argv[]) {

	function_t f1 = [](std::vector<double> vec) {
		return pow(vec.at(0),2) + 2*pow(vec.at(1),2) - 2;
	};
	function_t f2 = [](std::vector<double> vec) {
		return pow(vec.at(0) - 1.f, 2) + pow(vec.at(1) - 1.f / 2, 2) - 1.f / 4;
	};

	std::initializer_list<pair_t> initList = { pair_t(2,f1),pair_t(2,f2) };
	
	std::vector<Matrix> solutions = findRoots(initList, 2, 50, 300);
	
	std::cout << "Znalezione rozwiazania: " << std::endl;
	for (auto& x : solutions)
		std::cout << x << std::endl;


	_getch();
	return 0;
}

