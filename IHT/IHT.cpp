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
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = rand() / (RAND_MAX + 1.);
		}
	}
	return matrix;
}

float* fillVector(int size)
{
	float* vector = (float*)malloc(size * sizeof(float));

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

void findMax(float** matrix, int size, float &max, int &row, int &column)
{
	max = matrix[0][0];
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
}

void findMaxSSE(float** matrix, int size, float &max, int &row, int &column)
{
	__m128** matrixSSE = (__m128**)matrix;
	__m128 maxSSE = matrixSSE[0][0];


}

void multiplyByVector(float** a, float* b, float* &c, int n)
{
	for (int i = 0; i < n; i++)
	{
		c[i] = 0;
		for (int j = 0; j < n; j++)
		{
			c[i] += a[i][j] * b[j];
		}
	}
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
				cout << m1[i][j] << "  " << m2[i][j] << endl << endl;
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
	float max;
	int row, col;

	for (int i = 0; i < times; i++)
	{
		float** matrix = fillMatrix(size);
		clock_t begin, end;
		double elapsed_secs = 0;

		begin = clock();
		findMax(matrix, size, max, row, col);
		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		if (elapsed_secs < min)
		{
			min = elapsed_secs;
		}

		free(matrix);
	}
	cout << "max: " << max << ", row: " << row << ", column: " << col << endl;
	cout << "time: " << min << endl;
}

void testMultiplyByVector(int size, int times)
{
	cout << "\nmultiply by vector\n";
	double min = DBL_MAX;

	for (int i = 0; i < times; i++)
	{
		float** matrix = fillMatrix(size);
		float* vector = fillVector(size);
		float* resultVector = new float[size];
		clock_t begin, end;
		double elapsed_secs;

		begin = clock();
		multiplyByVector(matrix, vector, resultVector, size);
		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		if (elapsed_secs < min)
		{
			min = elapsed_secs;
		}

		free(matrix);
		delete(vector);
		delete(resultVector);
	}

	cout << "time: " << min << endl;
}

float** testMultiply(float** m1, float** m2, int size, int times)
{
	double min = DBL_MAX;
	float** resultMatrix = (float**)malloc(size * sizeof(float*));

	for (int k = 0; k < size; k++)
	{
		resultMatrix[k] = (float*)malloc(size * sizeof(float));
	}


	for (int i = 0; i < times; i++)
	{

		float** matrixRes1 = fillMatrix(size);
		float** matrixRes2 = fillMatrix(size);

		clock_t begin, end;
		double elapsed_secs = 0;

		
		begin = clock();
		multiply(matrixRes1, matrixRes2, resultMatrix, size);
		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		if (elapsed_secs < min)
		{
			min = elapsed_secs;
		}

		free(matrixRes1);
		free(matrixRes2);
	}
	multiply(m1, m2, resultMatrix, size);
	
	cout << "time: " << min << endl;
	return resultMatrix;
}

float** testOptimizedMultiply(float** m1, float** m2, int size, int times)
{
	double min = DBL_MAX;
	float** resultMatrix = (float**)malloc(size * sizeof(float*));

	for (int k = 0; k < size; k++)
	{
		resultMatrix[k] = (float*)malloc(size * sizeof(float));
	}


	for (int i = 0; i < times; i++)
	{

		float** matrixRes1 = fillMatrix(size);
		float** matrixRes2 = fillMatrix(size);
		clock_t begin, end;
		double elapsed_secs = 0;


		begin = clock();
		optimizedMultiply(matrixRes1, matrixRes2, resultMatrix, size);
		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		if (elapsed_secs < min)
		{
			min = elapsed_secs;
		}

//		free(resultMatrix);
		free(matrixRes1);
		free(matrixRes2);
	}
	multiply(m1, m2, resultMatrix, size);

	cout << "time: " << min << endl;
	return resultMatrix;
}

/////////////////////
bool isAVXAvailable()
{
	bool result = true;
	__int64 xcr0 = _xgetbv(0);
	result = (xcr0 & 7) == 7;
	
	if (!result)
	{
		return false;
	}

	int regs[4];
	__cpuid(regs, 1);
	result = ((regs[2] >> 26) & 7) == 7;
	
	if (!result)
	{
		return false;
	}

	result = (regs[2] & ((1 << 12) | (1 << 22))) == ((1 << 12) | (1 << 22));
	
	if (!result)
	{
		return result;
	}

	int c = (1 << 3) | (1 << 5) | (1 << 8);
	__cpuid(regs, 7);
	result = (regs[1] & c) == c;

	if (!result)
	{
		return result;
	}

	return result;
}

void runFirstStage()
{
	int times = 10;

	for (int size = 128; size < 513; size *= 2)
	{
		float** m1 = fillMatrix(size);
		float** m2 = fillMatrix(size);

		cout << "size: " << size << endl << endl;

		testFindMax(size, times);
		testMultiplyByVector(size, times);

		cout << "\nordinary multiplication: " << endl;
		float** a = testMultiply(m1, m2, size, times);

		cout << "\noptimized multiplication: " << endl;
		float** b = testOptimizedMultiply(m1, m2, size, times);

		cout << "\ntest equality: " << equals(a, b, size) << endl;

		free(m1);
		free(m2);

		cout << endl << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	runFirstStage();
	//cout << "is AVX available: " << isAVXAvailable() << endl;

	return 0;
}
