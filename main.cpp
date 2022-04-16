#include "hpx/hpx_main.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>
#include "Matrix.h"
#include "Matrix_Operations.h"

void runTest(int m1rows, int m1cols, int m2rows, int m2cols) {
	Matrix<double> m1(m1rows, m1cols);
	Matrix<double> m2(m2rows, m2cols);

	//Initiate matrices with random values
	std::for_each(m1.begin(), m1.end(), [](double& i) {
		i = (std::rand() % 40) / 0.25;
		}
	);
	std::for_each(m2.begin(), m2.end(), [](double& i) {
		i = (std::rand() % 40) / 0.25;
		}
	);

	//now we compare sequential vs parallel run time
	std::cout << "Multiplying 2 matrices of dimensions: m1:" << m1rows << "x" << m1cols 
		<< "  m2:" << m2rows << "x" << m2cols << std::endl;

	
	auto startTime = std::chrono::high_resolution_clock::now();
	Matrix<double> prod1 = matops::seq::product(m1, m2); //sequential matrix multiplication
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed_seconds = endTime - startTime;
	std::cout << "Sequential multiplication: " << elapsed_seconds.count() << std::endl;

	startTime = std::chrono::high_resolution_clock::now();
	Matrix<double> prod2 = matops::par::product(m1, m2); //parallell matrix multiplication
	endTime = std::chrono::high_resolution_clock::now();
	elapsed_seconds = endTime - startTime;
	std::cout << "Parallel multiplication (2): " << elapsed_seconds.count() << std::endl;
	
	startTime = std::chrono::high_resolution_clock::now();
	Matrix<double> prod3 = matops::par::product2(m1, m2); //parallell matrix multiplication (2)
	endTime = std::chrono::high_resolution_clock::now();
	elapsed_seconds = endTime - startTime;
	std::cout << "Parallel multiplication: " << elapsed_seconds.count() << std::endl;
	



	std::cout << '\n' << std::endl;
}

int main()
{
	//compares sequential to parallel execution times, for matrices of different dimensions
	runTest(3, 300000, 300000, 3);
	runTest(30, 30000, 30000, 3);
	runTest(30, 3000, 3000, 30);
	runTest(300, 300, 300, 30);
	runTest(300, 30, 30, 300);
	runTest(3000, 30, 30, 300);
	runTest(3000, 30, 30, 3000);

	
	return 0;
}
