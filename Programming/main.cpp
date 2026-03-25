#include <iostream>
#include <fstream>
#include <climits>
#include <iomanip>
using namespace std;

double** ReadMatrixFromFile(const char* filename, int& n, int& m);
void PrintMatrix(double** matrix, int n, int m);
void MatrixSumm(double** matrix, int n, int m, double& minsumm, int& columnCount);

int main() {
	cout << "=== Working With matrix A ===" << endl;
	int n1, m1;
	double** matrixA = ReadMatrixFromFile("matrixA.txt", n1, m1);

	if (matrixA) {
		PrintMatrix(matrixA, n1, m1);

		double minSummA;
		int columnCountA;

		MatrixSumm(matrixA, n1, m1, minSummA, columnCountA);

		if (columnCountA > 0) {
			cout << "\nColumn Count without negative elements: " << columnCountA << endl;
			cout << "Minimal Summ between this columns: " << minSummA << endl;
		}
		else {
			cout << "\nNo Column without negative elements." << endl;
		}
	}

	cout << "\n\n";


	cout << "=== Working With matrix B ===" << endl;
	int n2, m2;
	double** matrixB = ReadMatrixFromFile("matrixB.txt", n2, m2);

	if (matrixB) {
		PrintMatrix(matrixB, n1, m1);

		double minSummB;
		int columnCountB;

		MatrixSumm(matrixB, n1, m1, minSummB, columnCountB);

		if (columnCountB > 0) {
			cout << "\nColumn Count without negative elements: " << columnCountB << endl;
			cout << "Minimal Summ between this columns: " << minSummB << endl;
		}
		else {
			cout << "\nNo Column without negative elements." << endl;
		}
	}
	
	return 0;
}

double** ReadMatrixFromFile(const char* filename, int& n, int& m)
{
	ifstream file(filename);

	if (!file.is_open()) {
		cerr << "Error, can't open file" << endl;
		return nullptr;
	}

	file >> n >> m;

	double** matrix = new double* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new double[m];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			file >> matrix[i][j];
		}
	}
	file.close();

	return matrix;
}

void PrintMatrix(double** matrix, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << setw(10) << fixed << setprecision(2) <<matrix[i][j];
		}
		cout << endl;
	}
}

void MatrixSumm(double** matrix, int n, int m, double& minSumm, int& columnCount)
{
	minSumm = DBL_MAX;
	columnCount = 0;

	for (int i = 0; i < m; i++)
	{
		bool hasNegative = false;
		double columnSumm = 0.0;
		for (int j = 0; j < n; j++)
		{
			if (matrix[i][j] < 0) {
				hasNegative = true;
				break;
			}

			columnSumm += matrix[i][j];
		}

		if (!hasNegative) {
			columnCount += 1;
			if (columnSumm < minSumm)
				minSumm = columnSumm;
		}
	}
}
