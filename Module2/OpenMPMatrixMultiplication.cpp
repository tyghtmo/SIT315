// OpenMPMatrixMultiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "omp.h"
using namespace std;

const int maxNumber = 1;
const int matrixSize = 2000;
const int maxThreads = 4;

//Function to fill matrix a and b with random numbers
void fillMatrix(int matrix[matrixSize][matrixSize], int size) {
	int i, j;
	for (i = 0; i < size; ++i)
		for (j = 0; j < size; ++j)
		{
			matrix[i][j] = rand() % maxNumber + 1;
		}
}

//Function to write matrix to file
void writeMatrixToFile(long matrix[matrixSize][matrixSize]) {
	ofstream outfile;
	outfile.open("matrixOutput.txt");
	outfile << "Output Matrix: " << endl;
	for (int i = 0; i < matrixSize; ++i)
		for (int j = 0; j < matrixSize; ++j)
		{
			outfile << " " << matrix[i][j];
			if (j == matrixSize - 1)
				outfile << endl;
		}

	outfile.close();
}

int main()
{
	int i, j, k;
	srand(time(NULL));

	cout << "Matrix Size:  " << matrixSize << endl;

	static int matrixA[matrixSize][matrixSize], matrixB[matrixSize][matrixSize];
	static long int matrixC[matrixSize][matrixSize];
	fillMatrix(matrixA, matrixSize);
	fillMatrix(matrixB, matrixSize);

	//omp_set_num_threads(maxThreads);
	//int threadSize = matrixSize / maxThreads;

	//Start clock
	cout << "Starting Matrix Multiplication" << endl;
	clock_t begin = clock();


		// Multiplying matrix a and b and storing in array mult.
#pragma omp parallel for private(i,j,k) shared(matrixA,matrixB,matrixC)
		for (i = 0; i < matrixSize; ++i) 
		{
			for (j = 0; j < matrixSize; ++j) 
			{
				for (k = 0; k < matrixSize; ++k) 
				{
					matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
				}
			}
		}

	//End clock
	clock_t end = clock();
	cout << "Matrix Multiplication Finished" << endl;
	double elapsedTime = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Time taken to multiply: " << elapsedTime << " seconds" << endl;

	cout << "Writing result to file" << endl;
	writeMatrixToFile(matrixC);

	return 0;
}