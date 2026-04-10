/***************************************************************************
* Project Type: win32_console_Application                                  *
* Project Name: C:\Users\fe1nfly\source\repos\Prog_laba_2                  *
* File Name: Prog_laba_2.cpp                                               *
* Language: C++, Microsoft  Visual Studio 2022                             *
* Programmers: Бригада №2                                                  *
* Programmer (1): Дудукалов Глеб Максимович                                *
* Programmer (2): Ривоненко Никита Павлович                                *
* Modified by:                                                             *
* Created: 05.04.2026                                                      *
* Last Revision: 09.04.2026                                                *
* Comment:                                                                 *
* Тема:«Двумерные массивы»                                                 *
* 1) Определить сумму элементов в тех столбцах матрицы, которые не         *
*    содержат отрицательных элементов;                                     *
* 2) Определить минимум среди найденных сумм                               *
* Алгоритм должен быть параметризирован.                                   *
* Реализовать программу в двух вариантах: через индексы и указатели        *
***************************************************************************/

#include <iostream> //Библиотека для ввода/вывода
#include <fstream> //Библиотека для работы с файлами
#include <iomanip> //Библиотека для управления форматированием ввода/вывода
#include <cfloat> //Предоставляет константы, характеризующие типы данных с плавающей точкой
using namespace std;

//Реализация программы через индексы
double** ReadMatrIndex(const char* filename, int& n, int& m, int number); //Чтение матрицы
void PrintMatrIndex(double** Matr, int n, int m, int number); //Вывод матрицы
void DeleteMatrIndex(double** Matr, int n); //Удаление матрицы (освобождение памяти)
//Определение суммы элементов в столбцах без отрицательных элементов
void SumMatrIndex(double** Matr, int n, int m, double* ArraySum, int& countcol);
void MinSumIndex(double* ArraySum, int m, double& minsum); //Определение минимума среди найденных сумм

//Реализация программы через указатели
double** ReadMatrPointer(const char* filename, int& n, int& m, int number); //Чтение матрицы
void PrintMatrPointer(double** Matr, int n, int m, int number); //Вывод матрицы
void DeleteMatrPointer(double** Matr, int n); //Удаление матрицы (освобождение памяти)
//Определение суммы элементов в столбцах без отрицательных элементов
void SumMatrPointer(double** Matr, int n, int m, double* ArraySum, int& countcol);
void MinSumPointer(double* ArraySum, int m, double& minsum); //Определение минимума среди найденных сумм

int main()
{
	setlocale(LC_ALL, "RUSSIAN"); //Подключение русского языка
	system("color F0"); //Буквы-чёрные, фон-белый
	const char* filename1 = "Matr_A.txt"; //Файл с первой матрицей
	const char* filename2 = "Matr_B.txt"; //Файл со второй матрицей
	int N1, M1; //Количество строк, столбцов в первой матрице
	int N2, M2; //Количество строк, столбцов во второй матрице
	int number1 = 1; //Номер первой матрицы
	int number2 = 2; //Номер второй матрицы
	double MinSum; //Минимальная сумма
	int countcolumn; //Количество столбцов без отрицательных элементов


    cout << "===Реализация программы с помощью индексов===" << endl << endl;
    double** MatrIndexA = ReadMatrIndex(filename1, N1, M1, number1); //Чтение первой матрицы
    //Проверка что при выполнении функции ReadMatrIndex была возвращена матрица, а не ошибка
    if (MatrIndexA)
    {
        double* ArraySum1 = new double[M1]; //Массив для хранения найденных сумм для первой матрицы
        PrintMatrIndex(MatrIndexA, N1, M1, number1); //Вывод первой матрицы
        cout << "===========================================================================================================" << endl;
        cout << "Определение сумм элементов столбцов без отрицательных элементов и нахождение минимальной суммы в матрице№1" << endl;
        cout << "===========================================================================================================" << endl;
        //Определение суммы элементов в столбцах без отрицательных элементов в первой матрице
        SumMatrIndex(MatrIndexA, N1, M1, ArraySum1, countcolumn);
        for (int i = 0; i < M1; i++) //Цикл для вывода найденных сумм
        {
            if (ArraySum1[i] != -1.0) //Если сумма найдена
            {
                cout << "Cумма элементов в " << i + 1 << " столбце равна " << ArraySum1[i] << endl;
            }
            else //Сумма не была найдена
            {
                cout << "В столбце " << i + 1 << " есть отрицательные элементы" << endl;
            }
        }
        if (countcolumn > 0) //Если в матрице есть столбцы без отрицательных элементов
        {
            MinSumIndex(ArraySum1, M1, MinSum); //Определение минимума среди найденных сумм в первой матрице
            cout << "Минимальная сумма: " << MinSum << endl;
        }
        else
        {
            cout << "Все столбцы матрицы содержат отрицательные элементы" << endl;
        }
        cout << "===========================================================================================================" << endl << endl;
        delete[]ArraySum1; //Освобождение памяти, которая была выделена под массив с суммами
        DeleteMatrIndex(MatrIndexA, N1); //Освобождение памяти, которая была выделена под матрицу
    }
    else
    {
        //Сообщение об ошибке
        cout << "Матрица №" << number1 << " пропущена из-за ошибки" << endl;
        cout << "Переходим к следующей матрице" << endl << endl;
    }

    //Комментарии к алгоритму для обработки второй матрицы с помощью индексов и этих же матриц с помощью указателей аналогичны
    double** MatrIndexB = ReadMatrIndex(filename2, N2, M2, number2);
    if (MatrIndexB)
    {
        double* ArraySum2 = new double[M2]; //Массив для хранения найденных сумм для второй матрицы
        PrintMatrIndex(MatrIndexB, N2, M2, number2);
        cout << "===========================================================================================================" << endl;
        cout << "Определение сумм элементов столбцов без отрицательных элементов и нахождение минимальной суммы в матрице№2" << endl;
        cout << "===========================================================================================================" << endl;
        SumMatrIndex(MatrIndexB, N2, M2, ArraySum2, countcolumn);
        for (int i = 0; i < M2; i++)
        {
            if (ArraySum2[i] != -1.0)
            {
                cout << "Cумма элементов в " << i + 1 << " столбце равна " << ArraySum2[i] << endl;
            }
            else
            {
                cout << "В столбце " << i + 1 << " есть отрицательные элементы" << endl;
            }
        }
        if (countcolumn > 0)
        {
            MinSumIndex(ArraySum2, M2, MinSum);
            cout << "Минимальная сумма: " << MinSum << endl;
        }
        else
        {
            cout << "Все столбцы матрицы содержат отрицательные элементы" << endl;
        }
        cout << "===========================================================================================================" << endl << endl;
        delete[]ArraySum2;
        DeleteMatrIndex(MatrIndexB, N2);
    }
    else
    {
        cout << "Матрица №" << number2 << " пропущена из-за ошибки" << endl;
    }


    cout << "===Реализация программы с помощью указателей===" << endl << endl;
    double** MatrPointerA = ReadMatrPointer(filename1, N1, M1, number1);
    if (MatrPointerA)
    {
        double* ArraySum1 = new double[M1];
        PrintMatrPointer(MatrPointerA, N1, M1, number1);
        cout << "===========================================================================================================" << endl;
        cout << "Определение сумм элементов столбцов без отрицательных элементов и нахождение минимальной суммы в матрице№1" << endl;
        cout << "===========================================================================================================" << endl;
        SumMatrPointer(MatrPointerA, N1, M1, ArraySum1, countcolumn);
        for (int i = 0; i < M1; i++)
        {
            if (*(ArraySum1 + i) != -1.0)
            {
                cout << "Cумма элементов в " << i + 1 << " столбце равна " << *(ArraySum1 + i) << endl;
            }
            else
            {
                cout << "В столбце " << i + 1 << " есть отрицательные элементы" << endl;
            }
        }
        if (countcolumn > 0)
        {
            MinSumPointer(ArraySum1, M1, MinSum);
            cout << "Минимальная сумма: " << MinSum << endl;
        }
        else
        {
            cout << "Все столбцы матрицы содержат отрицательные элементы" << endl;
        }
        cout << "===========================================================================================================" << endl << endl;
        delete[]ArraySum1;
        DeleteMatrPointer(MatrPointerA, N1);
    }
    else
    {
        cout << "Матрица №" << number1 << " пропущена из-за ошибки" << endl;
        cout << "Переходим к следующей матрице" << endl << endl;
    }

    double** MatrPointerB = ReadMatrPointer(filename2, N2, M2, number2);
    if (MatrPointerB)
    {
        double* ArraySum2 = new double[M2];
        PrintMatrPointer(MatrPointerB, N2, M2, number2);
        cout << "===========================================================================================================" << endl;
        cout << "Определение сумм элементов столбцов без отрицательных элементов и нахождение минимальной суммы в матрице№2" << endl;
        cout << "===========================================================================================================" << endl;
        SumMatrPointer(MatrPointerB, N2, M2, ArraySum2, countcolumn);
        for (int i = 0; i < M2; i++)
        {
            if (*(ArraySum2 + i) != -1.0)
            {
                cout << "Cумма элементов в " << i + 1 << " столбце равна " << *(ArraySum2 + i) << endl;
            }
            else
            {
                cout << "В столбце " << i + 1 << " есть отрицательные элементы" << endl;
            }
        }
        if (countcolumn > 0)
        {
            MinSumPointer(ArraySum2, M2, MinSum);
            cout << "Минимальная сумма: " << MinSum << endl;
        }
        else
        {
            cout << "Все столбцы матрицы содержат отрицательные элементы" << endl;
        }
        cout << "===========================================================================================================" << endl << endl;
        delete[]ArraySum2;
        DeleteMatrPointer(MatrPointerB, N2);
    }
    else
    {
        cout << "Матрица №" << number2 << " пропущена из-за ошибки" << endl;
    }

    return 0;
}


//Чтение матрицы через индексы
double** ReadMatrIndex(const char* filename, int& n, int& m, int number)
{
    ifstream file(filename); //Создание потока чтения из файла
    // Обработка ошибки открытия файла
    if (!file)
    {   //Сообщение об ошибке и возвращение нулевого указателя
        cout << "Файл " << filename << " не найден!" << endl;
        return nullptr;
    }
    file >> n >> m; //Чтение размеров матрицы
    if (file.fail()) //Если ошибка при чтении файла
    {
        if (file.eof()) //Если файл пустой
        {
            //Сообщение об ошибке
            cout << "Файл " << filename << " пустой!" << endl;
        }
        else
        {
            //Сообщение об ошибке
            cout << "Ошибка при чтении размера матрицы№" << number << endl;
        }
        return nullptr; //Возвращение нулевого указателя
    }
    if (n <= 0 || m <= 0) //Если количество строк или столбцов меньше 0
    {
        //Сообщение об ошибке и возвращение нулевого указателя
        cout << "Недопустимые значения размеров для матрицы№" << number << endl;
        return nullptr;
    }
    //Выделение динамической памяти под матрицу
    double** matr = new double* [n]; //Выделение памяти под массив указателей
    for (int i = 0; i < n; i++)
    {
        matr[i] = nullptr;
    }
    bool error = false; //Фиксирует ошибку
    //Чтение элементов матрицы 
    for (int i = 0; i < n && !error; i++)
    {
        matr[i] = new double[m]; //Выделение памяти под строки матрицы
        for (int j = 0; j < m; j++)
        {
            file >> matr[i][j];
            if (file.fail()) //Если ошибка при чтении файла
            {
                if (file.eof()) //Если в файле элементов меньше чем указано
                {
                    //Сообщение об ошибке
                    cout << "В файле " << filename << " недостаточно элементов" << endl;
                }
                else
                {
                    //Сообщение об ошибке
                    cout << "Ошибка при чтении элемента c координатами " << "[" << i + 1 << "]" << "[" << j + 1 << "]" << endl;
                }
                error = true; //Фиксируем ошибку
                break; //Выход из цикла
            }
        }
    }
    if (!file.eof() && !error) //Если в файле больше элементов, чем указано и до этого не было зафиксировано ошибки
    {
        //Вывод сообщения об ошибке и помечаем ошибку
        cout << "В файле " << filename << " слишком много элементов" << endl;
        error = true;
    }
    //Если ошибка 
    if (error)
    {
        //Очищаем уже выделенную память и возвращаем нулевой указатель
        for (int i = 0; i < n; ++i)
        {
            delete[] matr[i];
        }
        delete[] matr;
        return nullptr;
    }
    file.close(); //Закрытие потока чтения из файла
    return matr; //Возвращение матрицы
}

//Вывод матрицы через индексы
void PrintMatrIndex(double** Matr, int n, int m, int number)
{
    cout << "Матрица №" << number << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << setw(6) << fixed << setprecision(3) << Matr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//Удаление матрицы (освобождение памяти) через индексы
void DeleteMatrIndex(double** Matr, int n)
{
    //Если при чтении матрицы вернули нулевой указатель, а не матрицу
    if (!Matr)
    {
        return;
    }
    for (int i = 0; i < n; i++)
    {
        delete[]Matr[i];
    }
    delete[]Matr;
}


//Определение суммы элементов в столбцах без отрицательных элементов через индексы
void SumMatrIndex(double** Matr, int n, int m, double* ArraySum, int& countcol)
{
    countcol = 0; //Количество столбцов без отрицательных элементов
    for (int j = 0; j < m; j++)
    {
        double summa = 0; //Сумма элементов в столбце
        int count = 0; //Количество неотрицательных элементов в столбце
        //Считаем неотрицательные элементы в столбце
        for (int i = 0; i < n; i++)
        {
            if (Matr[i][j] >= 0)
            {
                count++;
            }
        }
        //Если в столбце нет отрицательных элементов
        if (count == n)
        {
            countcol++; //Увеличиваем счётчик столбцов без отрицательных элементов
            //Считаем сумму
            for (int i = 0; i < n; i++)
            {
                summa += Matr[i][j];
            }
            ArraySum[j] = summa; //Записываем сумму в массив
        }
        //Записываем в массив невозможное значение для суммы неотрицательных элементов (отрицательное число)
        else
        {
            ArraySum[j] = -1.0;
        }
    }
}

//Определение минимума среди найденных сумм
void MinSumIndex(double* ArraySum, int m, double& minsum)
{
    minsum = DBL_MAX; //Инициализируем минимальную сумму
    //Нахождение минимальной суммы в массиве
    for (int i = 0; i < m; i++)
    {
        if (ArraySum[i] < minsum && ArraySum[i] != -1.0)
        {
            minsum = ArraySum[i];
        }
    }
}

//Далее программа реализована абсолютно также, только через указатели, поэтому все комментарии остаются верными
double** ReadMatrPointer(const char* filename, int& n, int& m, int number)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Файл " << filename << " не найден!" << endl;
        return nullptr;
    }
    file >> n >> m;
    if (file.fail())
    {
        if (file.eof())
        {
            cout << "Файл " << filename << " пустой!" << endl;
        }
        else
        {
            cout << "Ошибка при чтении размера матрицы№" << number << endl;
        }
        return nullptr;
    }
    if (n <= 0 || m <= 0)
    {
        cout << "Недопустимые значения размеров для матрицы№" << number << endl;
        return nullptr;
    }
    double** matr = new double* [n];
    for (int i = 0; i < n; i++)
    {
        *(matr + i) = nullptr;
    }
    bool error = false;
    for (int i = 0; i < n && !error; i++)
    {
        *(matr + i) = new double[m];
        for (int j = 0; j < m; j++)
        {
            file >> *(*(matr + i) + j);
            if (file.fail())
            {
                if (file.eof())
                {
                    cout << "В файле " << filename << " недостаточно элементов" << endl;
                }
                else
                {
                    cout << "Ошибка при чтении элемента c координатами " << "[" << i + 1 << "]" << "[" << j + 1 << "]" << endl;
                }
                error = true;
                break;
            }
        }
    }
    if (!file.eof() && !error)
    {
        cout << "В файле " << filename << " слишком много элементов" << endl;
        error = true;
    }
    if (error)
    {
        for (int i = 0; i < n; ++i)
        {
            delete[] * (matr + i);
        }
        delete[] matr;
        return nullptr;
    }
    file.close();
    return matr;
}

void PrintMatrPointer(double** Matr, int n, int m, int number)
{
    cout << "Матрица №" << number << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << setw(6) << fixed << setprecision(3) << *(*(Matr + i) + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void DeleteMatrPointer(double** Matr, int n)
{
    if (!Matr)
    {
        return;
    }
    for (int i = 0; i < n; i++)
    {
        delete[] * (Matr + i);
    }
    delete[]Matr;
}

void SumMatrPointer(double** Matr, int n, int m, double* ArraySum, int& countcol)
{
    countcol = 0;
    for (int j = 0; j < m; j++)
    {
        double summa = 0;
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (*(*(Matr + i) + j) >= 0)
            {
                count++;
            }
        }
        if (count == n)
        {
            countcol++;
            for (int i = 0; i < n; i++)
            {
                summa += *(*(Matr + i) + j);
            }
            *(ArraySum + j) = summa;
        }
        else
        {
            *(ArraySum + j) = -1.0;
        }
    }
}


void MinSumPointer(double* ArraySum, int m, double& minsum)
{
    minsum = DBL_MAX;
    for (int i = 0; i < m; i++)
    {
        if (*(ArraySum + i) < minsum && *(ArraySum + i) != -1.0)
        {
            minsum = *(ArraySum + i);
        }
    }
}
