#include <iostream>
#include <conio.h>
#include "Utility.h"
#include "Matrix.h"
#include "VectorOfFunctions.h"
#include <vector>
#include <functional>




int main(int argc, char * argv[]) {

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


	
	_getch();
	return 0;
}

