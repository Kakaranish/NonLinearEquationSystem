#include "Libs.h"
#include "Matrix.h"
#include "Utility.h"

void test(unsigned x) {
	std::cout << x << std::endl;
}


int main(int argc, char * argv[]) {
	



	{
		Matrix mA(4, 3);
		mA(0, 0) = 1;
		mA(1, 1) = 2;
		mA(2, 2) = 3;
		mA(0, 2) = 9;

		Matrix vec1(1, 3);
		Matrix vec2(1, 3);

		vec1.initRandomValues(10,20);
		vec2.initRandomValues(1, 5);

		std::cout << "vec1 = " << std::endl;
		std::cout << vec1 << std::endl;

		vec1.normalizeVector();
		std::cout << vec1 << std::endl;

		std::cout << vec1.findPerpendicularVector() << std::endl;

		vec1.mulitiplyByScalar(3);
		std::cout << vec1;

		std::cout << "mA = " << std::endl;
		std::cout << mA << std::endl;
		mA.mulitiplyByScalar(3);
		std::cout << mA << std::endl;

		try {
			std::cout << "vec1 o vec2 = " << vec1.getScalarProduct(vec2) << std::endl;
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}




	}

	/*
	{ 
		Matrix mA(3, 3);
		mA(0, 0) = 1;
		mA(1, 1) = 2;
		mA(2, 2) = 3;
		mA(0, 2) = 9;
		Matrix mB(mA);
		std::cout << mB << std::endl;

		std::cout << mB.transpose() << std::endl;

		std::cout << "mC = " << std::endl;
		Matrix mC = std::move(mB);
		std::cout << mC << std::endl;
		std::cout << "mC ptr = " << mC.getArrPtr() << std::endl;
		std::cout << mB.getArrPtr() << std::endl;

	}
	*/



	_getch();
	return 0;
}
	/*
	srand(static_cast<int>(time(NULL)));
	int n;
	std::cout << "**************************************************" << std::endl;
	std::cout << "***       PROGRAM WYKONAL STANISLAW GRUZ       ***" << std::endl;
	std::cout << "*** POWER ITERATION DLA MACIERZY HERMITOWSKIEJ ***" << std::endl;
	std::cout << "**************************************************" << std::endl;
	std::cout << "UWAGA! Podajemy np. 1 2 3 4 i na koncu po podaniu wiersza wciskamy ENTER!" << std::endl;
	std::cout << "Podaj wymiar macierzy: ";
	std::cin >> n;

	if (std::cin.fail() || n <= 0)
		exit(-1);

	std::cout << std::endl;

	Matrix A(n,n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			std::cin >> A(i, j);

	A.mulitiplyByScalar(1/12.f);
	computeEigenpairs(&A,300);

	*/