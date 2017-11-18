#include "Libs.h"
#include "Matrix.h"
#include "Utility.h"

int main(int argc, char * argv[]) {
	
	srand(static_cast<int>(time(NULL)));

	int n;
	std::cout << "**************************************************" << std::endl;
	std::cout << "***       PROGRAM WYKONAL STANISLAW GRUZ       ***" << std::endl;
	std::cout << "*** POWER ITERATION DLA MACIERZY HERMITOWSKIEJ ***" << std::endl;
	std::cout << "**************************************" << std::endl;
	std::cout << "UWAGA! Podajemy np. 1 2 3 4 i na koncu po podaniu wiersza wciskamy ENTER!" << std::endl;
	std::cout << "Podaj wymiar macierzy: ";
	std::cin >> n;

	if (std::cin.fail() || n <= 0) //jesli podany cos co nie jest intem
		exit(-1);


	std::cout << std::endl;

	Matrix A(n,n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			std::cin >> A(i, j);
	
	
	std::cout << "\nWpisana przez Ciebie macierz to: " << std::endl;
	std::cout << A << std::endl;

	return 0;
}