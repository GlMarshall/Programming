/**************************************************************************
* Project Type: win32_console_Application                                 *
* Project Name:  C:\Users\fe1nfly\source\repos\Laba№1_2semestr            *
* File Name:   Laba№1_2semestr.cpp                                        *
* Language: C++, Microsoft  Visual Studio 2022                            *
* Programmers: Бригада №2                                                 *
* Programmer (1): Дудукалов Глеб Максимович                               *
* Programmer (2): Ривоненко Никита Павлович                               *
* Modified by:                                                            *
* Created: 09.03.2026                                                     *
* Last Revision: 11.03.2026                                               *
* Comment:                                                                *
* Тема:«Символьные данные»                                                *
* 1) Печать всех слов строки, в которых все буквы различны;               *
* 2) Объединение символов двух строк в строку, в которой символы исходных *
*    строк чередуются через два.                                          *
**************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <climits>	
using namespace std;

// Декларация функции чтения из файла
double** ReadMatrixFromFile(const char* filename, int* n, int* m);
// Декларация функции вывода матрицы
void PrintMatrix(double** matrix, int n, int m);
// Декларация функции главного алгоритма
void MatrixSumm(double** matrix, int n, int m, double* minSumm, int* columnCount);
// Декларация функции освобождения ресурсов
void FreeMatrix(double** matrix, int n);


int main() {
	cout << "--- Matrix A ---" << endl;

	// Декларация Строк и стиолбцов
	int n1, m1;

	// Декларация матрицы
	double** matrixA = ReadMatrixFromFile("matrixA.txt", &n1, &m1);
	
	// Проверка ненулевой матрицы
	if (matrixA) {
		// Вывод матрицы
		PrintMatrix(matrixA, n1, m1);

		// Декларация переменных
		double minSummA;
		int columnCountA;

		cout << "Columns without negative elements" << endl;
		// Главный алгоритм
		MatrixSumm(matrixA, n1, m1, &minSummA, &columnCountA);

		// Проверка ненулевого значения
		if (columnCountA > 0) {
			cout << endl;
			cout << "Column Count without negative elements" << columnCountA << endl;
			cout << "MinSumm" << fixed << setprecision(2) << minSummA << endl;
		}
		else {
			cout << endl;
			cout << "No Columns without negative elements" << endl;
		}

		// Освобождение памяти
		FreeMatrix(matrixA, n1);

		// разделительная черта
		cout << endl << endl;

		// Дркгая матрица
		cout << "--- Matrix B ---" << endl;

		// Декларация строк и столбцов
		int n2, m2;
		// Чтение Матрицы из Файла
		double** matrixB = ReadMatrixFromFile("matrixB.txt", &n2, &m2);
		
		// Вывод матрицы B		
		PrintMatrix(matrixB, n2, m2);

		// Декларация переменных
		double minSummB;
		int columnCountB;

		cout << "Columns without negative elements" << endl;
		// Главный алгоритм
		MatrixSumm(matrixB, n2, m2, &minSummB, &columnCountB);

		// Проверка ненулевого значения
		if (columnCountB > 0) {
			cout << endl;
			cout << "Column Count without negative elements" << columnCountB << endl;
			cout << "MinSumm" << fixed << setprecision(2) << minSummB << endl;
		}
		else {
			cout << endl;
			cout << "No Columns without negative elements" << endl;
		}
		// Освобождение памяти
		FreeMatrix(matrixB, n2);
		
		return 0;
	}
}

// Чтоение матрицы из Файла
double** ReadMatrixFromFile(const char* filename, int* n, int* m) 
{
	// Файл
	ifstream file(filename);

	// Если Файл не найден
	if (!file.is_open()) {
		cout << "Cannot Open File" << endl;
		return nullptr;
	}

	// Чтение и разыменование
	file >> *n >> *m;

	// Новая матрица
	double** matrix = new double* [*n];
	for (int i = 0; i < *n; i++)
	{
		*(matrix + i) = new double[*m];
	}

	// Заполенение данными
	for (int i = 0; i < *n; i++)
	{
		for (int j = 0; j < *m; j++)
		{
			// Разыменывание разыменования
			file >> *(*(matrix + i) + j);
		}
	}

	// Закрытие файла
	file.close();
	// Дефолтный возврат
	return matrix;
}

// Вывод матрицы
void PrintMatrix(double** matrix, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << setw(10) << fixed << setprecision(2) << *(*(matrix + i) + j);
		}
		cout << endl;
	}
}

// Чтение из файла
void MatrixSumm(double** matrix, int n, int m, double* minSumm, int* columnCount)
{
	// разыменование переменных и присовение им начальных данных
	*minSumm = DBL_MAX;
	*columnCount = 0;
	
	// Столбцы
	for (int i = 0; i < n; i++)
	{
		// Переменная наличия отрицательного значения
		bool negative = false;
		// Сумма
		double columnSum = 0;
		// Строки
		for (int j = 0; j < m; j++)
		{
			// Элемент
			double* element = *(matrix + i) + j;
			// Проверка на положительность Элемента
			if (*element < 0) {
				negative = true;
				break;
			}
			// Прибавка к сумме
			columnSum += *element;
		}
		
		// Ну и присвоение minSumm значение суммы столбца
		if (!negative) {
			(*columnCount) += 1;
			if (columnSum < *minSumm) {
				*minSumm = columnSum;
			}
		}

	}
}

// Освобождение русурсов
void FreeMatrix(double** matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		delete[] * (matrix + i);
	}
	delete[] matrix;
}
