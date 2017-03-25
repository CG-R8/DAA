/*
 ============================================================================
 Name        : strassen.c
 Author      : Chetan
 Email       : cgajare1@binghamton.edu
 Created on  : Mar 12, 2017
 Description : 
 ============================================================================
 */
#include<stdio.h>
#include<stdlib.h>

int size;
int sizeToPrintMatrix;
void strassensMultiplication(float a[][size], float b[][size], int size);
void standardMultiplication(float a[][size], float b[][size], int size);
void initializeToRandom(float a[][size], float b[][size]);
void customRecusriveStrassensMultFunction(float a[][size], float b[][size], float result[][size], int size);
void addMatrix(float a[][size], float b[][size], float result[][size], int matrixSize);
void subMatrix(float a[][size], float b[][size], float result[][size], int matrixSize);
void print(float a[][size], int newMatrixSize);


int main(int argc, char *argv[])
{
	size = atoi(argv[1]);
	sizeToPrintMatrix = size;
	//Check the power of n is 2^k or find nearest power.
	int power = 1;
	while (power < size)
		power *= 2;

	float a[power][power];
	float b[power][power];
	//Fill matrix with random no.
	if (size == power)
	{
		initializeToRandom(a, b);
	}
	else
	{
		int i, j;
		//Fill all element with Zeros
		for (i = 0; i < power; i++)
			for (j = 0; j < power; j++)
			{
				a[i][j] = 0.0;
				b[i][j] = 0.0;
			}
		//Fill matrix with random no. for desired range of 'n' (size)
		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
			{
				a[i][j] = -5 + 10 * ((float) rand()) / RAND_MAX;
				a[i][j] = roundf(a[i][j] * 100) / 100;
				b[i][j] = -5 + 10 * (float) (rand()) / RAND_MAX;
				b[i][j] = roundf(b[i][j] * 100) / 100;
			}
		size = power;
	}
	printf("\nMatrix A:\n");
	print(a, size);
	printf("\nMatrix B:\n");
	print(b, size);

	strassensMultiplication(a, b, size);
	standardMultiplication(a, b, size);

	return 0;
}
//Fill the Matrix with random values
void initializeToRandom(float a[][size], float b[][size])
{
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
		{
			a[i][j] = -5 + 10 * ((float) rand()) / RAND_MAX;
			a[i][j] = roundf(a[i][j] * 100) / 100;
			b[i][j] = -5 + 10 * (float) (rand()) / RAND_MAX;
			b[i][j] = roundf(b[i][j] * 100) / 100;
		}
}
//Add two Matrix
void addMatrix(float a[][size], float b[][size], float result[][size], int matrixSize)
{
	int i, j;
	for (i = 0; i < matrixSize; i++)
		for (j = 0; j < matrixSize; j++)
			result[i][j] = a[i][j] + b[i][j];
}

//Subtract two Matrix
void subMatrix(float a[][size], float b[][size], float result[][size], int matrixSize)
{
	int i, j;
	for (i = 0; i < matrixSize; i++)
		for (j = 0; j < matrixSize; j++)
			result[i][j] = a[i][j] - b[i][j];
}

void print(float a[][size], int matrixSize)
{
	int i, j;
	for (i = 0; i < sizeToPrintMatrix; i++)
	{
		for (j = 0; j < sizeToPrintMatrix; j++)
		{
			printf("%.2f\t", a[i][j]);
		}
		printf("\n");
	}
}

void createResultMatrix(float c[][size], float result[][size], int startRow, int startCol, int matrixSize)
{
	int a, a2;
	int b, b2;
	for (a = 0, a2 = startRow; a < matrixSize; a++, a2++)
	{
		for (b = 0, b2 = startCol; b < matrixSize; b++, b2++)
		{
			result[a2][b2] = c[a][b];
		}
	}
}

void customRecusriveStrassensMultFunction(float a[][size], float b[][size], float result[][size], int matrixSize)
{
	int i, j, k;
	int newMatrixSize;
	// Base for recursion. When both matrix have single element.
	if (matrixSize <= 1)
	{
		result[0][0] = a[0][0] * b[0][0];
	}
	else
	{
		newMatrixSize = matrixSize / 2;
		float a11[size][size];
		float a12[size][size];
		float a21[size][size];
		float a22[size][size];
		float b11[size][size];
		float b12[size][size];
		float b21[size][size];
		float b22[size][size];
		float addResult1[size][size];
		float addResult2[size][size];
		float subtResult[size][size];
		float m1[size][size];
		float m2[size][size];
		float m3[size][size];
		float m4[size][size];
		float m5[size][size];
		float m6[size][size];
		float m7[size][size];
		float c11[size][size];
		float c12[size][size];
		float c21[size][size];
		float c22[size][size];
		//Divide both a and b matrix into sub-matrix
		for (i = 0; i < newMatrixSize; i++)
		{
			for (j = 0; j < newMatrixSize; j++)
			{
				a11[i][j] = a[i][j];
				a12[i][j] = a[i][j + newMatrixSize];
				a21[i][j] = a[i + newMatrixSize][j];
				a22[i][j] = a[i + newMatrixSize][j + newMatrixSize];
				b11[i][j] = b[i][j];
				b12[i][j] = b[i][j + newMatrixSize];
				b21[i][j] = b[i + newMatrixSize][j];
				b22[i][j] = b[i + newMatrixSize][j + newMatrixSize];
			}
		}
		//  		m1 = (a11 + a22)(b11+b22)
		addMatrix(a11, a22, addResult1, newMatrixSize);
		addMatrix(b11, b22, addResult2, newMatrixSize);
		customRecusriveStrassensMultFunction(addResult1, addResult2, m1, newMatrixSize);
		//  		m2 = (a21 + a22) b11
		addMatrix(a21, a22, addResult1, newMatrixSize);
		customRecusriveStrassensMultFunction(addResult1, b11, m2, newMatrixSize);
		//  		m3 = a11 (b12 – b22)
		subMatrix(b12, b22, subtResult, newMatrixSize);
		customRecusriveStrassensMultFunction(a11, subtResult, m3, newMatrixSize);
		//  		m4 = a22 (b21 – b11))
		subMatrix(b21, b11, subtResult, newMatrixSize);
		customRecusriveStrassensMultFunction(a22, subtResult, m4, newMatrixSize);
		//  		m5 = (a11 + a12) b22
		addMatrix(a11, a12, addResult1, newMatrixSize);
		customRecusriveStrassensMultFunction(addResult1, b22, m5, newMatrixSize);
		//  		m6 = (a21 – a11) (b11+b12)
		subMatrix(a21, a11, subtResult, newMatrixSize);
		addMatrix(b11, b12, addResult1, newMatrixSize);
		customRecusriveStrassensMultFunction(subtResult, addResult1, m6, newMatrixSize);
		//  		m7 = (a12 – a22)(b21 + b22
		subMatrix(a12, a22, subtResult, newMatrixSize);
		addMatrix(b21, b22, addResult1, newMatrixSize);
		customRecusriveStrassensMultFunction(subtResult, addResult1, m7, newMatrixSize);
		//  		c11 = m1+m4-m5+m7
		addMatrix(m1, m4, addResult1, newMatrixSize);
		addMatrix(addResult1, m7, addResult2, newMatrixSize);
		subMatrix(addResult2, m5, c11, newMatrixSize);
		//  		c12
		addMatrix(m3, m5, c12, newMatrixSize);
		//  		c21
		addMatrix(m2, m4, c21, newMatrixSize);
		//  	    c22
		addMatrix(m1, m3, addResult1, newMatrixSize);
		addMatrix(addResult1, m6, addResult2, newMatrixSize);
		subMatrix(addResult2, m2, c22, newMatrixSize);
		//			Create the resultant matrix by combining c11 c12 c21 c22
		createResultMatrix(c11, result, 0, 0, newMatrixSize);
		createResultMatrix(c12, result, 0, newMatrixSize, newMatrixSize);
		createResultMatrix(c21, result, newMatrixSize, 0, newMatrixSize);
		createResultMatrix(c22, result, newMatrixSize, newMatrixSize, newMatrixSize);
	}
}
void strassensMultiplication(float a[][size], float b[][size], int size)
{
	float result[size][size];
	customRecusriveStrassensMultFunction(a, b, result, size);
	printf("\nStrassen’s Multiplication Output:\n");
	print(result, size);
}
void standardMultiplication(float a[][size], float b[][size], int size)
{
	int i, j, k;
	float result[size][size];
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			result[i][j] = 0;
			for (k = 0; k < size; k++)
			{
				result[i][j] = result[i][j] + a[i][k] * b[k][j];
			}
		}
	}
	printf("\nStandard Multiplication Output:\n");
	print(result, size);
}
