    #include "Utility.h"

    std::pair<double, Matrix*> computeLeadingEigenpair(Matrix* matrix, int steps){
        if(matrix->getSize().getColNum()!= matrix->getSize().getRowsNum()){
            std::cout << "Given matrix in not square!" << std::endl;
            exit(-1);
        }
        
        unsigned dimension = matrix->getSize().getColNum();
        Matrix* prevVec = new Matrix(dimension, 1);
        
        for(unsigned i=0;i<dimension;i++)
            (*prevVec)(i, 0) = (std::rand()% 10) + 1;
        std::cout << "\nRandom vector = " << prevVec->getTransposed();
        prevVec->normalizeVector();
        std::cout << "Normalized random vector = "<< prevVec->getTransposed() << std::endl;


        Matrix vecMultResult(dimension, 1);
        for(unsigned i=0;i<steps;i++){
            vecMultResult = matrix->getMultipliedByMatrix(*prevVec); 
            *prevVec = vecMultResult.getMultipliedByScalar(1.f/vecMultResult.getVectorLength());
        }
        return std::pair<double, Matrix*>(vecMultResult.getVectorLength(), prevVec);
    }
	void computeEigenpairs(Matrix* matrix, int steps){
        std::pair<double, Matrix*> leadingEigenpair = computeLeadingEigenpair(matrix, steps);
        std::cout << "Wiodąca wartość własna = " << leadingEigenpair.first << std::endl;
        std::cout << "Wiodący wektor własny = "<< leadingEigenpair.second->getTransposed();

        unsigned dimension = matrix->getSize().getColNum();
        Matrix* prevVec = new Matrix(dimension, 1);
        *prevVec = leadingEigenpair.second->findPerpendicularVector();
        prevVec->normalizeVector();
        Matrix vecMultResult(dimension,1);

        for(unsigned i=0;i<steps;i++){
            vecMultResult = matrix->getMultipliedByMatrix(*prevVec); 
            vecMultResult -= leadingEigenpair.second->getMultipliedByMatrix(leadingEigenpair.second->getTransposed().getMultipliedByMatrix(vecMultResult));
            *prevVec = vecMultResult.getMultipliedByScalar(1.f/vecMultResult.getVectorLength());
        }

        std::cout << "Druga wiodąca wartość własna = " << vecMultResult.getVectorLength() << std::endl;
        std::cout << "Drugi wiodący wektor własny = " << prevVec->getTransposed();
    }

	//We want to operate on copied variables
	bool gauss(Matrix A, Matrix& X, Matrix B) {

		if (A.getSize().getRowsNum() != A.getSize().getColNum())
			throw MatrixException("Unable to perform Gaussian Elimination! Matrix A isn't square!");
		if (A.getSize().getColNum() != X.getSize().getRowsNum() || A.getSize().getColNum() != B.getSize().getRowsNum())
			throw MatrixException("Unable to perform Gaussian Elimination! Matrix X or B has wrong dimensions!");

		double m = 0, s = 0;
		unsigned size = A.getSize().getColNum();
		double eps = 1e-12; //lower value than this will be trated as zero

							//Here we are creating extended matrix [A|B]
		Matrix AB(size, size + 1);
		for (unsigned i = 0; i < size; i++) {
			for (unsigned j = 0; j < size; j++)
				AB(i, j) = A(i, j);
			AB(i, size) = B(i, 0);
		}

		//Elimination of coefficients
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (fabs(AB(i, i)) < eps)
					return false;
				m = -AB(j, i) / AB(i, i);
				for (int k = i + 1; k <= size; k++)
					AB(j, k) += m * AB(i, k);
			}
		}

		//Computing X matrix

		//in this loop we have to init i to int type, because if i=0, and loop iterates,
		//then unsigned i will be very big positive number
		//and we will go out of range
		for (int i = size - 1; i >= 0; i--) {
			s = AB(i, size);
			for (unsigned j = size - 1; j >= i + 1; j--)
				s -= AB(i, j) * X(j, 0);
			if (fabs(AB(i, i)) < eps)
				return false;
			X(i, 0) = s / AB(i, i);
		}
		return true;
	}