#pragma once
#include "Libs.h"
#include "Matrix.h"
#include "VectorOfFunctions.h"

bool gauss(Matrix A, Matrix& X, Matrix B);
Matrix findRoot(std::initializer_list<pair_t> f_list, Matrix initVec, int steps);
std::vector<Matrix> findRoots(std::initializer_list<pair_t> f_list, int vecSize, int numOfRandomVectors, int steps);