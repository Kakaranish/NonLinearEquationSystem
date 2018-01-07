#include "VectorOfFunctions.h"

//Private methods
double VectorOfFunctions::getDerivative(unsigned functionNum, unsigned differedVarNum, std::vector<double>& args) {
	if (functionNum >= argc || differedVarNum >= argc || args.size() != argc)
		throw MatrixException("Unable to take derivative!");

	std::vector<double> lArgsCopy(args); //have to use copy constructor
	std::vector<double> rArgsCopy(args);

	double h = sqrt(DBL_EPSILON); //half of smallest value in cpp; recomended
	lArgsCopy.at(differedVarNum) += h;
	rArgsCopy.at(differedVarNum) -= h;

	return (functions.at(functionNum)(lArgsCopy) - functions.at(functionNum)(rArgsCopy)) / (2. * h);
}

//Constructor
VectorOfFunctions::VectorOfFunctions(std::initializer_list<func_pair> list) {
	int func_num = list.size();

	for (auto& x : list) {
		//we want to check wheter number of args of every single function is equal to number of functions
		if (x.first != func_num)
			throw MatrixException("Can't create VectorOfFunctions! Func num is not compatible with quantity of args of some function!");
		functions.push_back(x.second);
	}
	argc = func_num;
}

//Misc
Matrix VectorOfFunctions::computeValuesVector(std::vector<double> args) {
	Matrix tMatrix(argc, 1);
	for (int i = 0; i < functions.size(); i++)
		tMatrix(i, 0) = functions.at(i)(args);

	return tMatrix;
}
std::vector<double> VectorOfFunctions::getDefaultArgsVector() {
	std::vector<double> argsVector;
	for (int i = 0; i < argc; i++)
		argsVector.push_back(1);

	return argsVector;
}
//point = (args(0),args(1),...,(args(argc))
Matrix VectorOfFunctions::computeJacobianInPoint(std::vector<double> args) {
	Matrix jacobianMatrix(argc, argc);

	for (int i = 0; i < argc; i++) {
		for (int j = 0; j < argc; j++) {
			//i-th function
			//j-th var derivative

			jacobianMatrix(i, j) = getDerivative(i, j, args);
		}
	}
	return jacobianMatrix;
}