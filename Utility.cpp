    #include "Utility.h"

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
	Matrix findRoot(std::initializer_list<pair_t> f_list, Matrix initVec, int steps) {

		VectorOfFunctions func_vec(f_list);

		//Step 1 - init vec_x_i
		Matrix vec_x_i = initVec;

		//Step 2 - compute J(vec_x_i), F(vec_x_i)
		auto J_x_i = func_vec.computeJacobianInPoint(vec_x_i.toVectorList());
		auto F_x_i = func_vec.computeValuesVector(vec_x_i.toVectorList());


		//Step 3 - compute y_x_i from equation J(vec_x_i)y_x_i = -F(vec_x_i)
		Matrix y_i(func_vec.getArgc(), 1);

		try {
			bool hasSolution = gauss(J_x_i, y_i, F_x_i.getMultipliedByScalar(-1));
			if (hasSolution) {
				//std::cout << y_i;
			}

		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}


		Matrix vec_x_next_i(vec_x_i + y_i);
		for (int i = 0; i < steps; i++) {
			//Step 4 - compute vec_x_next_i
			//Step 5 - till convergent!

			if (i != 0)
				vec_x_next_i = vec_x_i + y_i;


			vec_x_i = vec_x_next_i;
			J_x_i = func_vec.computeJacobianInPoint(vec_x_i.toVectorList());
			F_x_i = func_vec.computeValuesVector(vec_x_i.toVectorList());

			try {
				bool hasSolution = gauss(J_x_i, y_i, F_x_i.getMultipliedByScalar(-1));
				if (hasSolution) {
					//std::cout << y_i;
				}
			}
			catch (std::exception e) {
				std::cout << e.what() << std::endl;
			}
		}
		return vec_x_next_i;
	}
	std::vector<Matrix> findRoots(std::initializer_list<pair_t> f_list, int vecSize, int numOfRandomVectors, int steps) {
		std::vector<Matrix> rootsVector;

		Matrix initVec(vecSize, 1);

		for (int i = 0; i < numOfRandomVectors; i++) {
			initVec.initRandomValues(-100, 100);
			auto tVec = findRoot(f_list, initVec, steps);
			tVec.roundMatrix(5);

			if (!(std::find(rootsVector.begin(), rootsVector.end(), tVec) != rootsVector.end())) 
				rootsVector.push_back(tVec);	
		}
		return rootsVector;
	}