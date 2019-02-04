#include <stdio.h>
#include "pch.h"
#include <omp.h>
#include<time.h>

#include <iostream>

#define length 2000

using namespace std;

void popuni(double **matrix, double num);
void ispis(double **matrix);

int main()
{
	double **matrixA = new double*[length];
	double **matrixB = new double*[length];
	double **matrixC = new double*[length];
	int brojThreadova = 4, buffer = 0;
	clock_t pocetak, kraj;
	double MFLOPS = 0;
	double n = 0;

	//Aloc
	for (int i = 0; i < length; i++)
	{
		matrixA[i] = new double[length];
		matrixB[i] = new double[length];
		matrixC[i] = new double[length];
	}

	//Threadovi
	//cout << "Unos broja threadova: ";
	//cin >> brojThreadova;
	//cout << "\n";
	omp_set_num_threads(brojThreadova);

	//Popunjavanje
	popuni(matrixA, 2);
	popuni(matrixB, 2);
	popuni(matrixC, 0);

	//Mnozenje
	pocetak = clock();
#pragma omp parallel for private(buffer, n) reduction(+:n)
	for (int i = 0; i < length; i++)
	{
		for (int k = 0; k < length; k++)
		{			
			buffer = 0;
			for (int j = 0; j < length; j++)
			{
				buffer += matrixA[i][j] * matrixB[j][i];
				n = n + 2;
			}
			matrixC[i][k] = buffer;
		}
	}
	kraj = clock();
	
	

	//Ispis
	// ispis(matrixC);

	//Brisanje
	for (int i = 0; i < length; i++)
	{
		delete[] matrixA[i];
		delete[] matrixB[i];
		delete[] matrixC[i];
	}
	delete[] matrixA;
	delete[] matrixB;
	delete[] matrixC;

	
	float T = kraj - pocetak;
	cout << "MFLOP= " << n / (T * pow(10, 6)) << "\n";

	cout << "CPU user time:= " << T << "\n";
	cout << "CPU real time:= " << T * 4 << "\n";
	return 0;
}

void popuni(double **matrix, double num)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			matrix[i][j] = num;
		}
	}

}
void ispis(double **matrix)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}