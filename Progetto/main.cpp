#include <iostream>
#include "matrix.h"

int main()
{
	Matrix<3,4,int> m1;
	m1.fill(3);

	Matrix<3,4,int> m2;
	m2.fill(0);
	m2.at(0,0) = 2;

	Matrix<4,6,int> m3;
	m3.fill(2);
	m3.at(2,3) = -4;
	m3.at(2,1) = 0;

	std::cout << "m1\n" << m1 << std::endl;
	std::cout << "m2\n" << m2 << std::endl;
	std::cout << "m3\n" << m3 << std::endl;
	
	std::cout << "m1+m2\n" << m1+m2 << std::endl;
	std::cout << "m1*m3\n" << m1*m3 << std::endl;

	return 0;
}
