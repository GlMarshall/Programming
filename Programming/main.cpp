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
* Last Revision: 05.05.2026                                                *
* Comment:                                                                 *
* Тема:«Двумерные массивы»                                                 *
* 1) Определить сумму элементов в тех столбцах матрицы, которые не         *
*    содержат отрицательных элементов;                                     *
* 2) Определить минимум среди найденных сумм                               *
* Алгоритм должен быть параметризирован.                                   *
* Реализовать программу в двух вариантах: через индексы и указатели        *
***************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

enum ERROR_MESSAGE
{
    NO_ERRORS,
    FILE_NOT_FOUND,
    FILE_EMPTY,
    MARTIX_SIZE,
    NUMBER_OF_ROWS,
    ROWS_GREATER_THAN_MAX_SIZE,
    COLUMNS_GREATER_THAN_MAX_SIZE,
    NUMBER_OF_COLUMNS,
    NOT_ENOUGHT_ELEMENTS,
    TOO_MANY_EMELENTS,
    READING_ELEMENT,
};

//Константа для максимального размера статической матрицы
const int MAX_SIZE = 100;

void PrintErrorMessage(int code, const char* filename, int number = 0, int row = -1, int col = -1); //Функция вывода сообщений об ошибках

//Реализация программы через индексы
int ReadMatrIndex(const char* filename, double Matr[][MAX_SIZE], int& n, int& m, int number, int& errorRow, int& errorCol); //Чтение матрицы
void PrintMatrIndex(double Matr[][MAX_SIZE], int n, int m, int number); //Вывод матрицы
//Определение суммы элементов матрицы в столбцах без отрицательных элементов
void SumMatrIndex(double Matr[][MAX_SIZE], int n, int m, double ArraySum[MAX_SIZE], int& countcol);
void MinSumIndex(double ArraySum[MAX_SIZE], int m, int countcol); //Определение минимума среди найденных сумм

//Реализация программы через указатели
double** ReadMatrPointer(const char* filename, int& n, int& m, int number); //Чтение матрицы
void PrintMatrPointer(double** Matr, int n, int m, int number); //Вывод матрицы
void DeleteMatrPointer(double** Matr, int n); //Удаление матрицы (освобождение памяти)
//Определение суммы элементов матрицы в столбцах без отрицательных элементов
void SumMatrPointer(double** Matr, int n, int m, double* ArraySum, int& countcol);
void MinSumPointer(double* ArraySum, int m, int countcol); //Определение минимума среди найденных сумм

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
    int countcolumn; //Количество столбцов без отрицательных элементов
    double MatrIndexA[MAX_SIZE][MAX_SIZE]; //Первая матрица для работы с индексами
    double MatrIndexB[MAX_SIZE][MAX_SIZE]; //Вторая матрица для работы с индексами
    int errorRow = -1, errorCol = -1;  // Переменные для хранения координат элемента с ошибкой
    int ERROR = ReadMatrIndex(filename1, MatrIndexA, N1, M1, number1, errorRow, errorCol); //Переменная для определения типа ошибки


    cout << "=====Реализация программы с помощью индексов=====" << endl << endl;
    //Обработка первой матрицы через индексы
    if (ERROR == NO_ERRORS) //Если ошибки нет
    {
        double ArraySum1[MAX_SIZE]; //Массив для хранения найденных сумм для первой матрицы
        PrintMatrIndex(MatrIndexA, N1, M1, number1); //Вывод первой матрицы
        cout << "===========================================================================================================" << endl;
        cout << "Определение сумм элементов столбцов без отрицательных элементов и нахождение минимальной суммы в матрице№1" << endl;
        cout << "===========================================================================================================" << endl;
        //Определение суммы элементов матрицы в столбцах без отрицательных элементов в первой матрице
        SumMatrIndex(MatrIndexA, N1, M1, ArraySum1, countcolumn);
        MinSumIndex(ArraySum1, M1, countcolumn); //Нахождение минимальной суммы
        cout << "===========================================================================================================" << endl << endl;
    }
    else //Ошибка есть
    {
        PrintErrorMessage(ERROR, filename1, number1, errorRow, errorCol); //Вывод ошибки
    }

    //Обработка второй матрицы через индексы
    ERROR = ReadMatrIndex(filename2, MatrIndexB, N2, M2, number2, errorRow, errorCol); //Проверка на наличие ошибок
    if (ERROR == NO_ERRORS) //Ошибки нет
    {
        double ArraySum2[MAX_SIZE]; //Массив для хранения найденных сумм для второй матрицы
        PrintMatrIndex(MatrIndexB, N2, M2, number2); //Вывод второй матрицы
        cout << "===========================================================================================================" << endl;
        cout << "Определение сумм элементов столбцов без отрицательных элементов и нахождение минимальной суммы в матрице№2" << endl;
        cout << "===========================================================================================================" << endl;
        //Определение суммы элементов матрицы в столбцах без отрицательных элементов в первой матрице
        SumMatrIndex(MatrIndexB, N2, M2, ArraySum2, countcolumn);
        MinSumIndex(ArraySum2, M2, countcolumn); //Нахождение минимальной суммы
        cout << "===========================================================================================================" << endl << endl;
    }
    else //Ошибка есть
    {
        PrintErrorMessage(ERROR, filename2, number2, errorRow, errorCol); //Вывод сообщения об ошибке
    }

    cout << endl << "=====Реализация программы с помощью указателей=====" << endl << endl;
    //Реализация через указатели для первой матрицы
    double** MatrPointerA = ReadMatrPointer(filename1, N1, M1, number1); //Функция возвращает матрицу, если ошибки нет, иначе - пустой указатель
    if (MatrPointerA) //Если Ошибки нет
    {
        double* ArraySum1 = new double[M1]; //Создание динамического массива для хранения найденных сумм в первой матрице
        PrintMatrPointer(MatrPointerA, N1, M1, number1); //Вывод первой матрицы
        cout << "===========================================================================================================" << endl;
        cout << "Определение сумм элементов столбцов без отрицательных элементов и нахождение минимальной суммы в матрице№1" << endl;
        cout << "===========================================================================================================" << endl;
        //Определение суммы элементов матрицы в столбцах без отрицательных элементов в первой матрице
        SumMatrPointer(MatrPointerA, N1, M1, ArraySum1, countcolumn);
        MinSumPointer(ArraySum1, M1, countcolumn); //Нахождение минимальной суммы
        cout << "===========================================================================================================" << endl << endl;
        delete[]ArraySum1; //Освобождение памяти из-под динамического массива для хранения сумм первой матрицы
        DeleteMatrPointer(MatrPointerA, N1); //Удаление первой матрицы (освобождение памяти)
    }


    //Реализация через указатели для второй матрицы
    double** MatrPointerB = ReadMatrPointer(filename2, N2, M2, number2);
    if (MatrPointerB)
    {
        double* ArraySum2 = new double[M2]; //Создание динамического массива для хранения найденных сумм во второй матрице
        PrintMatrPointer(MatrPointerB, N2, M2, number2); //Вывод второй матрицы
        cout << "===========================================================================================================" << endl;
        cout << "Определение сумм элементов столбцов без отрицательных элементов и нахождение минимальной суммы в матрице№2" << endl;
        cout << "===========================================================================================================" << endl;
        //Определение суммы элементов матрицы в столбцах без отрицательных элементов во второй матрице
        SumMatrPointer(MatrPointerB, N2, M2, ArraySum2, countcolumn);
        MinSumPointer(ArraySum2, M2, countcolumn); //Нахождение минимальной суммы
        cout << "===========================================================================================================" << endl << endl;
        delete[]ArraySum2; //Освобождение памяти из-под динамического массива для хранения сумм второй матрицы
        DeleteMatrPointer(MatrPointerB, N2); //Удаление второй матрицы (освобождение памяти)
    }

    return 0;
}

//Функция вывода сообщений об ошибках
void PrintErrorMessage(int code, const char* filename, int number, int row, int col)
{
    cout << "Матрица №" << number << " пропущена из-за ошибки" << endl;
    switch (code) {
    case NO_ERRORS: //Файл не найден
        cout << "Файл " << filename << " не найден!" << endl;
        break;
    case FILE_NOT_FOUND: //Файл пустой
        cout << "Файл " << filename << " пустой!" << endl;
        break;
    case MARTIX_SIZE: //Ошибка при чтении размера матрицы
        cout << "Ошибка при чтении размера матрицы №" << number << endl;
        break;
    case NUMBER_OF_ROWS: //Количество строк не является натуральным числом
        cout << "Количество строк не является натуральным числом для матрицы №" << number << endl;
        break;
    case NUMBER_OF_COLUMNS: //Количество столбцов не является натуральным числом 
        cout << "Количество столбцов не является натуральным числом для матрицы №" << number << endl;
        break;
    case NOT_ENOUGHT_ELEMENTS: //В файле недостаточно элементов
        cout << "В файле " << filename << " недостаточно элементов для матрицы №" << number << endl;
        break;
    case TOO_MANY_EMELENTS: //В файле слишком много элементов
        cout << "В файле " << filename << " слишком много элементов для матрицы №" << number << endl;
        break;
    case READING_ELEMENT: //Ошибка при чтении элемента
        cout << "Ошибка при чтении элемента c координатами " << "[" << row << "]" << "[" << col << "] в матрице №" << number << endl;
        break;
    case ROWS_GREATER_THAN_MAX_SIZE: // Количество строк больше чем MAX_SIZE
        cout << "Количество строк больше чем максимальное " << number << endl;
        break;
    case COLUMNS_GREATER_THAN_MAX_SIZE: // Количество столбцов больше чем MAX_SIZE
        cout << "Количество столбцов больше чем максимальное " << number << endl;
        break;
    default:
        cout << "Неизвестная ошибка (код: " << code << ")" << endl;
    }
    cout << endl;
}


//Чтение статической матрицы через индексы
int ReadMatrIndex(const char* filename, double Matr[][MAX_SIZE], int& n, int& m, int number, int& errorRow, int& errorCol)
{
    ifstream file(filename); //Создание потока чтения из файла
    if (!file) //Файл не найден
    {
        file.close(); //Закрытие потока чтения из файла
        return FILE_NOT_FOUND; //Возвращение кода ошибки FILE_NOT_FOUND
    }
    file >> n >> m; //Считывание размеров матрицы
    if (file.fail()) //Ошибка при чтении
    {
        if (file.eof()) //Файл пустой
        {
            file.close(); //Закрытие потока чтения из файла
            return FILE_EMPTY; //Возвращение кода ошибки FILE_EMPTY
        }
        else //Ошибка при чтении размеров матрицы
        {
            file.close(); //Закрытие потока чтения из файла
            return MARTIX_SIZE; //Возвращение кода ошибки 3
        }
    }
    if (n <= 0) //Количество строк ненатуральное число
    {
        file.close(); //Закрытие потока чтения из файла
        return NUMBER_OF_ROWS; //Возращение кода ошибки 4
    }
    if (n > MAX_SIZE) // Количество строк больше чем MAX_SIZE
    {
        file.close();
        return ROWS_GREATER_THAN_MAX_SIZE;
    }
    if (m <= 0) //Количество столбцов ненатуральное число
    {
        file.close(); //Закрытие потока чтения из файла
        return NUMBER_OF_COLUMNS; //Возвращение кода ошибки 5
    }
    if (m > MAX_SIZE) // Количество столбцов больше чем MAX_SIZE
    {
        file.close();
        return COLUMNS_GREATER_THAN_MAX_SIZE;
    }
    //Двойной цикл для чтения элементов матрицы
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            file >> Matr[i][j]; //Чтение элемента
            if (file.fail()) //Произошла ошибка
            {
                if (file.eof()) //Файл закончился раньше положенного
                {
                    file.close(); //Закрытие потока чтения из файла
                    return NOT_ENOUGHT_ELEMENTS; //Возвращение кода ошибки 6
                }
                else //Ошибка при чтении элемента матрицы
                {
                    errorRow = i + 1; //Номер строки элемента с ошибкой
                    errorCol = j + 1; //Номер столбца элемента с ошибкой
                    file.close(); //Закрытие потока чтения из файла
                    return READING_ELEMENT; //Возвращение кода ошибки 8
                }
            }
        }
    }
    double symbol; //Переменная для проверки на наличие лишних элементов
    if (file >> symbol) //Нашли лишний символ
    {
        file.close(); //Закрытие потока чтения из файла
        return TOO_MANY_EMELENTS; //Возвращение кода ошибки 7
    }
    file.close(); //Закрытие потока чтения из файла
    return NO_ERRORS; //Ошибок не обнаружили
}

//Вывод статической матрицы через индексы
void PrintMatrIndex(double Matr[][MAX_SIZE], int n, int m, int number)
{
    cout << "  Матрица №" << number << ":" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << setw(7) << fixed << setprecision(3) << Matr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//Определение суммы элементов в столбцах без отрицательных элементов через индексы для статической матрицы
void SumMatrIndex(double Matr[][MAX_SIZE], int n, int m, double ArraySum[MAX_SIZE], int& countcol)
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
    //Вывод найденных сумм
    for (int i = 0; i < m; i++)
    {
        if (ArraySum[i] != -1.0)
        {
            cout << "Cумма элементов в " << i + 1 << " столбце равна " << ArraySum[i] << endl;
        }
        else
        {
            cout << "В столбце " << i + 1 << " есть отрицательные элементы" << endl;
        }
    }
}


//Определение минимума среди найденных сумм для статической матрицы
void MinSumIndex(double ArraySum[MAX_SIZE], int m, int countcol)
{
    if (countcol > 0) //В матрице есть столбцы без отрицательных элементов
    {
        double minsum = DBL_MAX; //Инициализируем минимальную сумму
        //Нахождение минимальной суммы в массиве
        for (int i = 0; i < m; i++)
        {
            if (ArraySum[i] < minsum && ArraySum[i] != -1.0)
            {
                minsum = ArraySum[i];
            }
        }
        //Вывод минимальной суммы
        cout << "Минимальная сумма: " << minsum << endl;
    }
    else
    {
        cout << "Все столбцы матрицы содержат отрицательные элементы" << endl;
    }
}

//Чтение динамической матрицы через указатели с обработкой ошибок
double** ReadMatrPointer(const char* filename, int& n, int& m, int number)
{
    ifstream file(filename); //Создание потока чтения из файла
    int err = 0; //Код ошибки
    if (!file) //Файл не найден
    {
        err = 1; //Код ошибки 1
        PrintErrorMessage(err, filename, number); //Вывод ошибки 
        return nullptr; //Возвращение нулевого указателя
    }
    file >> n >> m; //Чтение размеров матрицы
    if (file.fail()) //Ошибка
    {
        if (file.eof()) //Файл пустой
        {
            err = 2; //Код ошибки 2
            PrintErrorMessage(err, filename, number); //Вывод сообщения об ошибке
        }
        else //Ошибка при чтении размеров матрицы
        {
            err = 3; //Код ошибки 3
            PrintErrorMessage(err, filename, number); //Вывод сообщения об ошибке
        }
        return nullptr; //Возвращение нулевого указателя
    }
    //Количество строк ненатуральное число
    if (n <= 0 || n > MAX_SIZE)
    {
        err = 4; //Код ошибки 4
        PrintErrorMessage(err, filename, number); //Вывод сообщения об ошибке
        return nullptr; //Возвращение нулевого указателя
    }
    if (m <= 0 || m > MAX_SIZE) //Количество столбцов ненатуральное число
    {
        err = 5; //Код ошибки 5
        PrintErrorMessage(err, filename, number); //Вывод сообщения об ошибке
        return nullptr; //Возвращение нулевого укказателя
    }

    //Выделение динамической памяти под матрицу
    double** matr = new double* [n]; //Выделение памяти под массив указателей
    for (int i = 0; i < n; i++)
    {
        *(matr + i) = nullptr;
    }

    bool error = false; //Ошибка при чтении элементов матрицы
    int errorRow = -1, errorCol = -1; //координаты элемента с ошибкой

    //Чтение элементов матрицы 
    for (int i = 0; i < n && !error; i++)
    {
        *(matr + i) = new double[m]; //Выделение памяти под строки матрицы
        for (int j = 0; j < m; j++)
        {
            file >> *(*(matr + i) + j);
            if (file.fail()) //Если ошибка при чтении файла
            {
                if (file.eof()) //Если в файле элементов меньше чем указано
                {
                    err = 6; //Код ошибки 6
                    PrintErrorMessage(err, filename, number); //Вывод сообщения об ошибке
                }
                else //Ошибка при чтении элемента
                {
                    errorRow = i + 1; //Строка элемента с ошибкой
                    errorCol = j + 1; //Столбец элемента с ошибкой
                    err = 8; //Код ошибки 8
                    PrintErrorMessage(err, filename, number, errorRow, errorCol); //Вывод сообщения об ошибке
                }
                error = true; //Фиксируем ошибку
                break; //Выход из цикла
            }
        }
    }
    if (!error) //Ошибки нет
    {
        double symbol; //Переменная для проверки файла на наличие лишних символов
        if (file >> symbol) //Нашлилишний символ
        {
            err = 7; //Код ошибки 7
            PrintErrorMessage(err, filename, number); //Вывод сообщения об ошибке
            error = true; //Фиксируем ошибку
        }
    }

    //Если ошибка 
    if (error)
    {
        //Очищаем уже выделенную память и возвращаем нулевой указатель
        for (int i = 0; i < n; ++i)
        {
            if (*(matr + i) != nullptr)
            {
                delete[] * (matr + i);
            }
        }
        delete[] matr;
        return nullptr;
    }

    file.close(); //Закрытие потока чтения из файла
    return matr; //Возвращение матрицы
}


//Вывод матрицы через указатели
void PrintMatrPointer(double** Matr, int n, int m, int number)
{
    cout << "  Матрица №" << number << ":" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << setw(7) << fixed << setprecision(3) << *(*(Matr + i) + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//Удаление матрицы (освобождение памяти) через указатели
void DeleteMatrPointer(double** Matr, int n)
{
    //Если при чтении матрицы вернули нулевой указатель, а не матрицу
    if (!Matr)
    {
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (*(Matr + i) != nullptr)
        {
            delete[] * (Matr + i);
        }
    }
    delete[]Matr;
}

//Определение суммы элементов в столбцах без отрицательных элементов через указатели
void SumMatrPointer(double** Matr, int n, int m, double* ArraySum, int& countcol)
{
    countcol = 0; //Количество столбцов без отрицательных элементов
    for (int j = 0; j < m; j++)
    {
        double summa = 0; //Сумма элементов в столбце
        int count = 0; //Количество неотрицательных элементов в столбце
        //Считаем неотрицательные элементы в столбце
        for (int i = 0; i < n; i++)
        {
            if (*(*(Matr + i) + j) >= 0)
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
                summa += *(*(Matr + i) + j);
            }
            *(ArraySum + j) = summa; //Записываем сумму в массив
        }
        //Записываем в массив невозможное значение для суммы неотрицательных элементов (отрицательное число)
        else
        {
            *(ArraySum + j) = -1.0;
        }
    }
    //Вывод найденных сумм
    for (int i = 0; i < m; i++)
    {
        if (*(ArraySum + i) != -1.0)
        {
            cout << "Cумма элементов в " << i + 1 << " столбце равна " << *(ArraySum + i) << endl;
        }
        else
        {
            cout << "В столбце " << i + 1 << " есть отрицательные элементы" << endl;
        }
    }
}

//Определение минимума среди найденных сумм через указатели
void MinSumPointer(double* ArraySum, int m, int countcol)
{
    if (countcol > 0) //В матрице есть столбцы без отрицательных элементов
    {
        double minsum = DBL_MAX; //Инициализируем минимальную сумму
        //Нахождение минимальной суммы в массиве
        for (int i = 0; i < m; i++)
        {
            if (*(ArraySum + i) < minsum && *(ArraySum + i) != -1.0)
            {
                minsum = *(ArraySum + i);
            }
        }
        //Вывод минимальной суммы
        cout << "Минимальная сумма: " << minsum << endl;
    }
    else
    {
        cout << "Все столбцы матрицы содержат отрицательные элементы" << endl;
    }
}
