#include "Utility.h"

std::pair<double, Matrix*> computeLeadingEigenpair(Matrix* matrix, int steps){
    if(matrix->getSize().x != matrix->getSize().y){
        std::cout << "Given matrix in not square!" << std::endl;
        exit(-1);
    }
    
    unsigned dimension = matrix->getSize().x;
    Matrix* prevVec = new Matrix(dimension, 1);
    
    for(unsigned i=0;i<dimension;i++)
        (*prevVec)(i, 0) = (std::rand()% 10) + 1;
    std::cout << "\nRandom vector = " << prevVec->transpose();
    prevVec->normalizeVector();
    std::cout << "Normalized random vector = "<< prevVec->transpose() << std::endl;


    Matrix vecMultResult(dimension, 1);
    for(unsigned i=0;i<steps;i++){
        vecMultResult = matrix->multiply(*prevVec); 
        *prevVec = vecMultResult.getMultipliedByScalar(1.f/vecMultResult.getVectorLength());
    }
    return std::pair<double, Matrix*>(vecMultResult.getVectorLength(), prevVec);
}

void computeEigenpairs(Matrix* matrix, int steps){
    std::pair<double, Matrix*> leadingEigenpair = computeLeadingEigenpair(matrix, steps);
    std::cout << "Wiodąca wartość własna = " << leadingEigenpair.first << std::endl;
	std::cout << "Wiodący wektor własny = "<< leadingEigenpair.second->transpose();

    unsigned dimension = matrix->getSize().x;
    Matrix* prevVec = new Matrix(dimension, 1);
    *prevVec = leadingEigenpair.second->findPerpendicularVector();
    std::cout << "prev before normalization = " << prevVec->transpose() << std::endl;
    std::cout << "Scalar product = " << prevVec->getScalarProduct(*leadingEigenpair.second) << std::endl;
    prevVec->normalizeVector();
    Matrix vecMultResult(dimension,1);

    for(unsigned i=0;i<steps;i++){
        vecMultResult = matrix->multiply(*prevVec); 
    
        vecMultResult -= leadingEigenpair.second->multiply(leadingEigenpair.second->transpose().multiply(vecMultResult));
        *prevVec = vecMultResult.getMultipliedByScalar(1.f/vecMultResult.getVectorLength());
    }

    std::cout << "Druga wiodąca wartość własna = " << vecMultResult.getVectorLength() << std::endl;
    std::cout << "Drugi wiodący wektor własny = " << prevVec->transpose();
}