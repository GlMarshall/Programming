#include <iostream>
#include <fstream>
#include <climits>
#include <iomanip>
using namespace std;

// Декларация функции чтения из файла
double** ReadMatrixFromFile(const char* filename, int& n, int& m);
// Декларация функции вывода матрицы
void PrintMatrix(double** matrix, int n, int m);
// Декларация функции главного алгоритма
void MatrixSumm(double** matrix, int n, int m, double& minsumm, int& columnCount);
// Декларация функции освобождения ресурсов
void FreeMatrix(double** matrix, int n);

int main() {
    cout << "--- Working With matrix A ---" << endl;
    // Декларация строк и столбцов
    int n1, m1;
    // Получение матрицы из файла
    double** matrixA = ReadMatrixFromFile("matrixA.txt", n1, m1);

    // Проверка ненулевой матрицы
    if (matrixA) {
        // Вывод матрицы
        PrintMatrix(matrixA, n1, m1);

        // Декларация переменной суммы
        double minSummA;
        // Декларация переменной кол-ва столбцов
        int columnCountA;

        MatrixSumm(matrixA, n1, m1, minSummA, columnCountA);

        // Проверка ненулевого значения
        if (columnCountA > 0) {
            cout << "\nColumn Count without negative elements: " << columnCountA << endl;
            cout << "Minimal Summ between this columns: " << minSummA << endl;
        }
        else {
            cout << "\nNo Column without negative elements." << endl;
        }
    }
    // Освобождение ресурсов
    FreeMatrix(matrixA, n1);
    cout << "\n\n";


    cout << "=== Working With matrix B ===" << endl;
    // Декларация строк и столбцов
    int n2, m2;
    // Получение матрицы из файла
    double** matrixB = ReadMatrixFromFile("matrixB.txt", n2, m2);

    // Проверка ненулевой матрицы
    if (matrixB) {
        // Вывод матрицы
        PrintMatrix(matrixB, n2, m2);

        // Декларация переменной суммы
        double minSummB;
        // Декларация переменной кол-ва столбцов
        int columnCountB;

        MatrixSumm(matrixB, n2, m2, minSummB, columnCountB);

        // ПАроверка ненулевого значения
        if (columnCountB > 0) {
            cout << "\nColumn Count without negative elements: " << columnCountB << endl;
            cout << "Minimal Summ between this columns: " << minSummB << endl;
        }
        else {
            cout << "\nNo Column without negative elements." << endl;
        }
    }
    // Освобождение ресурсов
    FreeMatrix(matrixB, n2);

    return 0;
}

// Чтоение из файла
double** ReadMatrixFromFile(const char* filename, int& n, int& m)
{
    // сам файл
    ifstream file(filename);

    // Проверка открытости файла
    if (!file.is_open()) {
        cout << "Error, can't open file" << endl;
        return nullptr;
    }

    // Записываем в переменые значения кол-ва сткрок и столбцов
    file >> n >> m;

    // создаем матрицу  
    double** matrix = new double* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[m];
    }

    // Заполняем матрицу
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            file >> matrix[i][j];
        }
    }
    // Закрываем поток
    file.close();

    // Возвращаем матрицу
    return matrix;
}

// Функция вывода матрицы
void PrintMatrix(double** matrix, int n, int m)
{
    // Столбцы
    for (int i = 0; i < n; i++)
    {
        // Строки
        for (int j = 0; j < m; j++)
        {
            // Вывод
            cout << setw(10) << fixed << setprecision(2) << matrix[i][j];
        }
        // Новая строка
        cout << endl;
    }
}

// Функция основного алгоритма
void MatrixSumm(double** matrix, int n, int m, double& minSumm, int& columnCount)
{
    // Инициализация начальных значений
    minSumm = DBL_MAX;
    columnCount = 0;

    // Столбцы
    for (int col = 0; col < m; col++) {
        // Наличие отрицательного
        bool hasNegative = false;
        // Сумма
        double colSum = 0.0;
        // Строки
        for (int row = 0; row < n; row++) {
            // Проверка отрицательного
            if (matrix[row][col] < 0) {
                hasNegative = true;
                break;
            }
            // Суммирование
            colSum += matrix[row][col];
        }
        // Присвоенние минимальной суммы
        if (!hasNegative) {
            columnCount++;
            if (colSum < minSumm) minSumm = colSum;
        }
    }
}

// Функция освобождения ресурсов (Пояснять не надо)
void FreeMatrix(double** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}
