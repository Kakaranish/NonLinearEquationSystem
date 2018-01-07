#pragma once
#include "Libs.h"
#include "Utility.h"
#include "Matrix.h"

typedef std::pair<double, std::function<double(std::vector<double>)>> func_pair;


//Single function is called with vetor of arguments
//Function is given in pair with num of her arguments
class VectorOfFunctions {
private:
	unsigned argc = 0;
	std::vector<std::function<double(std::vector<double>)>> functions;

	double getDerivative(unsigned functionNum, unsigned differedVarNum, std::vector<double>& args);
public:
	VectorOfFunctions(std::initializer_list<func_pair> list);
	Matrix computeValuesVector(std::vector<double> args);
	std::vector<double> getDefaultArgsVector();
	Matrix computeJacobianInPoint(std::vector<double> args);
};