#pragma once
#include "Libs.h"
#include "Matrix.h"

std::pair<double, Matrix*> computeLeadingEigenpair(Matrix* matrix, int steps);
void computeEigenpairs(Matrix*, int steps);

bool gauss(Matrix A, Matrix& X, Matrix B);

