// MatrixMultiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctime>
#include <fstream>
using namespace std;

int main()
{
	static int a[1000][1000], b[1000][1000];
	int r1, c1, r2, c2, i, j, k;
	static long int c[1000][1000];
	char input[] = "a";
	char quit[] = "q";
	srand(time(NULL));
	int maxSize = 1000;
	int minSize = 999;
	int matrixSize = 1000;

	r1 = c1 = r2 = c2 = matrixSize;
	/*
	r1 = rand() % (maxSize - minSize + 1) + minSize;
	c1 = rand() % (maxSize - minSize + 1) + minSize;
	r2 = c1;
	c2 = rand() % (maxSize - minSize + 1) + minSize;
	*/
	cout << "r1= " << r1 << endl;
	cout << "c1= " << c1 << endl;
	cout << "r2= " << r2 << endl;
	cout << "c2= " << c2 << endl;

	// Storing elements of first matrix.
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c1; ++j)
		{
			a[i][j] = rand() % 1000;
		}

	/*
	//Displaying first matrix
	cout << endl << "First Matrix: " << endl;
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c1; ++j)
		{
			cout << " " << a[i][j];
			if (j == c1 - 1)
				cout << endl;
		}
		*/

		// Storing elements of second matrix.
	for (i = 0; i < r2; ++i)
		for (j = 0; j < c2; ++j)
		{
			b[i][j] = rand() % 10;
		}

	/*
	//Displaying second matrix
	cout << endl << "Second Matrix: " << endl;
	for (i = 0; i < r2; ++i)
		for (j = 0; j < c2; ++j)
		{
			cout << " " << b[i][j];
			if (j == c2 - 1)
				cout << endl;
		}
	*/

	// Initializing elements of matrix mult to 0.
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c2; ++j)
		{
			c[i][j] = 0;
		}

	//Start clock
	clock_t begin = clock();

	try {
		// Multiplying matrix a and b and storing in array mult.
		for (i = 0; i < r1; ++i)
			for (j = 0; j < c2; ++j)
				for (k = 0; k < c1; ++k)
				{
					c[i][j] += a[i][k] * b[k][j];
				}

		//End clock
		clock_t end = clock();
		double elapsedTime = double(end - begin) / CLOCKS_PER_SEC;
		cout << "Time taken to multiply: " << elapsedTime << " seconds" << endl;
	}
	catch (overflow_error& e) {
		cout << e.what();
	}

	
	// Writing the multiplication of two matrix to file.

	ofstream outfile;
	outfile.open("matrixOutput.txt");
	outfile << endl << "Output Matrix: " << endl;
	for (i = 0; i < r1; ++i)
		for (j = 0; j < c2; ++j)
		{
			outfile << " " << c[i][j];
			if (j == c2 - 1)
				outfile << endl;
		}
		
	outfile.close();
	return 0;
}

