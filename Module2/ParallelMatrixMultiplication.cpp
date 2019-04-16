// ParallelMatrixMultiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <thread>
using namespace std;

const int maxNumber = 1;
const int matrixSize = 1000;
const int maxThreads = 1000;
int counter = 0;

static int matrixA[matrixSize][matrixSize], matrixB[matrixSize][matrixSize];
static long int matrixC[matrixSize][matrixSize];
thread matrixThread[matrixSize];

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

void multiplication(int threadNo) {

	// Multiplying matrix a and b and storing in array mult.
	for (int i = threadNo * matrixSize / maxThreads; i < (threadNo + 1) * matrixSize / maxThreads; i++) {
		for (int j = 0; j < matrixSize; j++) {
			for (int k = 0; k < matrixSize; k++) {
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
}

int main()
{
	srand(time(NULL));

	cout << "Matrix Size:  " << matrixSize << endl;

	fillMatrix(matrixA, matrixSize);
	fillMatrix(matrixB, matrixSize);

	//Start clock
	cout << "Starting Matrix Multiplication" << endl;
	clock_t begin = clock();

	/*
	// Multiplying matrix a and b and storing in array mult.
	for (i = 0; i < matrixSize; ++i) {
		for (j = 0; j < matrixSize; ++j) {
			for (k = 0; k < matrixSize; ++k) {
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}
	*/
	for (int i = 0; i < maxThreads; i++) {
		matrixThread[i] = thread(multiplication, i);
	}

	for (int j = 0; j < maxThreads; j++) {
		matrixThread[j].join();
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

