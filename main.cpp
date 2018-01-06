#include "Libs.h"
#include "Matrix.h"
#include "Utility.h"

void test(unsigned x) {
	std::cout << x << std::endl;
}


int main(int argc, char * argv[]) {
	



	{
		
		
		
		
		Matrix mA(5, 5);
		mA.initRandomValues(1,100);

		Matrix m1(5, 2);
		m1(0, 0) = 5;
		m1(0, 1) = 1;
		m1(1, 0) = -3;
		m1(1, 1) = 3;
		m1(2, 0) = 4;
		m1(2, 1) = -1;
		m1(3, 0) = -1;
		m1(3, 1) = 2;
		m1(4, 0) = 0;
		m1(4, 1) = 7;

		Matrix m2(2, 7);
		m2(0, 0) = 1;
		m2(0, 1) = 7;
		m2(0, 2) = 0;
		m2(0, 3) = -1;
		m2(0, 4) = 9;
		m2(0, 5) = 0;
		m2(0, 6) = 5;

		m2(1, 0) = 2;
		m2(1, 1) = -6;
		m2(1, 2) = -1;
		m2(1, 3) = 10;
		m2(1, 4) = 2;
		m2(1, 5) = -3;
		m2(1, 6) = 1;


		std::cout << "m1 = " << std::endl;
		std::cout << m1 << std::endl;
		std::cout << "m2 = " << std::endl;
		std::cout << m2 << std::endl;

		std::cout << "m1 x m2" << std::endl;
		std::cout << m1.getMultipliedByMatrix(m2) << std::endl;
		
		m1.multiplyByMatrix(m2);
		std::cout << m1 << std::endl;



		/*
		Matrix vec1(1, 3);
		vec1.initRandomValues(1,100);

		std::cout << vec1 << std::endl;
		vec1.transpose();
		std::cout << vec1 << std::endl;
		vec1.transpose();
		std::cout << vec1 << std::endl;
		*/


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