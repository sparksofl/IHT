// IHT.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "memory.h"
#include "float.h"
#include <stdlib.h>
#include "iostream"
#include <Windows.h>
#include <ctime>

using namespace std;

float** fillMatrix(int size) 
{
	float** matrix = (float**)malloc(size * sizeof(float*));
	for (int k = 0; k < size; k++)
	{
		matrix[k] = (float*)malloc(size * sizeof(float));
	}

	for (int i = 0; i < size; i++)
	{
		//matrix[i] = new float[size];
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = rand() / (RAND_MAX + 1.);
		}
	}
	return matrix;
}

float* fillVector(int size)
{
	float* vector = new float[size];
	for (int i = 0; i < size; i++)
	{
		vector[i] = rand() / (RAND_MAX + 1.);
	}
	return vector;
}

void printMatrix(float** matrix, int size)
{
	cout.precision(2);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void printVector(float* v, int len)
{
	cout.precision(2);
	for (int i = 0; i < len; i++)
	{
		cout << v[i] << " ";
	}
}

void findMax(float** matrix, int size)
{
	float max = FLT_MIN;
	float row = 0, column = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] > max)
			{
				max = matrix[i][j];
				row = i;
				column = j;
			}
		}
	}

	cout << "max: " << max << ", row: " << row << ", column: " << column << endl;
}

float* multiplyByVector(float* a[], float b[], float* c, int n)
{
	for (int i = 0; i < n; i++)
	{
		c[i] = 0;
		for (int j = 0; j < n; j++)
		{
			c[i] += a[i][j] * b[j];
		}
	}
	return c;
}

void multiply(float** a, float** b, float** &c, int n) 
{
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			c[i][j] = 0;
			for (int k = 0; k < n; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void optimizedMultiply(float** a, float** b, float** &c, int n)
{
	for (size_t i = 0; i < n; i++){
		for (size_t j = 0; j < n; j++){
			float t = a[i][j];
			for (size_t k = 0; k < n; k++){
				c[i][k] += t * b[j][k];
			}
		}
	}
}

bool equals(float** m1, float** m2, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (m1[i][j] != m2[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

void testFindMax(int size, int times)
{
	cout << "find max\n";
	double min = DBL_MAX;

	for (int i = 0; i < times; i++)
	{
		float** matrix = fillMatrix(size);
		clock_t begin, end;
		double elapsed_secs = 0;

		begin = clock();
		findMax(matrix, size);
		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		if (elapsed_secs < min)
		{
			min = elapsed_secs;
		}
	}

	cout << "time: " << min << endl;
}

void testMultiplyByVector(int size)
{
	cout << "\nmultiply by vector\n";

	float** matrix = fillMatrix(size);
	float* vector = fillVector(size);
	float* resultVector = new float[size];
	clock_t begin, end;
	double elapsed_secs;

	begin = clock();
	resultVector = multiplyByVector(matrix, vector, resultVector, size);
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "time: " << elapsed_secs << endl;
}

float** testMultiply(float** m1, float** m2, int size)
{
	float** matrix = m1;
	float** matrix2 = m2;
	float** resultMatrix = new float*[size];
	clock_t begin, end;
	double elapsed_secs = 0;

	for (int i = 0; i < size; i++)
	{
		resultMatrix[i] = new float[size];
	}

	begin = clock();
	multiply(matrix, matrix2, resultMatrix, size);
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "time: " << elapsed_secs << endl;

	free(matrix);
	free(matrix2);

	return resultMatrix;
}

float** testOptimizedMultiply(float** m1, float** m2, int size)
{
	float** matrix = m1;
	float** matrix2 = m2;

	float** resultMatrix = new float*[size];
	for (int i = 0; i < size; i++)
	{
		resultMatrix[i] = new float[size];
	}
	//float** resultMatrix = (float**)calloc(size, sizeof(float*));
	//for (int k = 0; k < size; k++)
	{
		//resultMatrix[k] = (float*)calloc(size, sizeof(float));
	}

	clock_t begin, end;
	double elapsed_secs = 0;

	begin = clock();
	optimizedMultiply(matrix, matrix2, resultMatrix, size);
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "time: " << elapsed_secs << endl;

	free(matrix);
	free(matrix2);

	return resultMatrix;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int size = 128, times = 10; 
	float** m1 = fillMatrix(size);
	float** m2 = fillMatrix(size);
	float** a = new float*[size];
	float** b = new float*[size];

	cout << "size: " << size << endl << endl;

	testFindMax(size, times);
	testMultiplyByVector(size);

	cout << "\nordinary multiplication: " << endl;
	a = testMultiply(m1, m2, size);

	cout << "\noptimized multiplication: " << endl;
	b = testOptimizedMultiply(m1, m2, size);
	
	cout << "test equality: " << equals(a, b, size) << endl;

	float** result = (float**)calloc(size, sizeof(float*));
	for (int k = 0; k < size; k++)
	{
		result[k] = (float*)calloc(size, sizeof(float));
	}

	/*free(m1);
	free(m2);
	free(a);
	free(b);*/

	return 0;
}
