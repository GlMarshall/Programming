/***************************************************************************
* Project Type: win32_console_Application                                  *
* Project Name: C:\Users\fe1nfly\source\repos\Prog_laba_2                  *
* File Name: Prog_laba_1.cpp                                               *
* Language: C++, Microsoft  Visual Studio 2022                             *
* Programmers: Бригада №2                                                  *
* Programmer (1): Дудукалов Глеб Максимович                                *
* Programmer (2): Ривоненко Никита Павлович                                *
* Modified by:                                                             *
* Created: 05.04.2026                                                      *
* Last Revision: NO_DATA                                                   *
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
using namespace std;

const int maxlen = 1000;

int GetStringLength(const char* str);
int ReadFromFile(const char* filename, char* buffer, int maxLen);
bool HasUniqueLettersInWord(const char* str, int start, int end);
void FindANdPrintUniqueLetterWords(const char* str, int length, const char* title, int& differentWordCount);
void CombineString(const char* str, int len1, const char* str2, int len2, char* result);

int main() {
	char str_1[maxlen];
	char str_2[maxlen];
	char str_new[maxlen];
	const char* readFile_1 = "stroka_1.txt";
	const char* readFile_2 = "stroka_2.txt";

	int lenstr_1 = 0;
	int lenstr_2 = 0;
	int differentwords1 = 0;
	int disserentwords2 = 0;

	lenstr_1 = ReadFromFile(readFile_1, str_1, maxlen);
	if (lenstr_1 == -1) {
		return 1;
	}

	lenstr_2 = ReadFromFile(readFile_2, str_2, maxlen);
	if (lenstr_2 == -1) {
		return 1;
	}

	FindANdPrintUniqueLetterWords(str_1, lenstr_1, "First String", differentwords1);
	if (differentwords1 == 0) {
		return 1;
	}

	cout << endl;
	FindANdPrintUniqueLetterWords(str_2, lenstr_2, "First String", disserentwords2);
	if (disserentwords2 == 0) {
		return 1;
	}

	cout << endl;
	cout << "Word Count without repitable letters in two string " << differentwords1 + disserentwords2 << endl;
	cout << endl;
	cout << "Combine string: ";
	CombineString(str_1, lenstr_1, str_2, lenstr_2, str_new);
	cout << str_new << endl;
	return 0;
}

int GetStringLength(const char* str)
{
	int length = 0;
	while (str[length] != '\0') {
		length++;
	}
	return length;
}

int ReadFromFile(const char* filename, char* buffer, int maxLen)
{
	ifstream file(filename);
	if (!file) {
		cout << "Cannot Open File " << filename << endl;
		return -1;
	}
	
	file.getline(buffer, maxlen);
	int length = GetStringLength(buffer);

	if (length == 0) {
		cout << "File " << filename << " is empty" << endl;
		return -1;
	}

	return length;
}

bool HasUniqueLettersInWord(const char* str, int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		for (int j = end; j > i; j--)
		{
			if (str[i] == str[j])
				return false;
		}
	}
	return true;
}

void FindANdPrintUniqueLetterWords(const char* str, int length, const char* title, int& differentWordCount)
{
	int i = 0;
	int numberWord = 0;
	int check_words = 0;
	differentWordCount = 0;

	while (i < length) {
		while ((str[i] == ' ') && (i < length)) {
			i++;
		}
		int bw = i;
		int ew = bw;

		while ((str[i] != ' ') && (i < length)) {
			check_words += 1;
			i++;
			ew++;
		}
		ew--;
		numberWord += 1;

		if (HasUniqueLettersInWord(str, bw, ew)) {
			differentWordCount += 1;
			cout << "Word number " << numberWord << "without repitable words";
			for (int i = 0; i < ew; i++)
			{
				cout << str[i];
			}
			cout << " ford start: " << bw << " word end " << ew << endl;
		}
	}
	if (check_words == 0) {
		cout << "No words in " << title << endl;
	}
	else if (differentWordCount == 0) {
		cout << "In " << title << " exists words with only repitable letters";
	}
	else {
		cout << "In " << title << " exists " << differentWordCount << " without repitable letters" << endl;
	}
}

void CombineString(const char* str, int len1, const char* str2, int len2, char* result)
{
	int i = 0;
	int j = 0;

	if (len1 < len2) {
		int ostlen = len1 - len2;

		if (len2 % 2 != 0) {
			int k = 0;
			while (j < len2 - 1) {
				result[i] = str[j];
				result[i + 1] = str[j + 1];
				result[i + 2] = str2[j];
				result[i + 3] = str2[j + 1];
				i += 4;
				j += 2;
			}

			result[i] = str[j];
			result[i + 1] = str[j + 1];
			result[i + 2] = str2[j];
			i += 3;

			int sdwig = 1;
			while (k < ostlen) {
				result[i] = str[len2 + sdwig];
				k++;
				sdwig++;
				i++;
			}
		}
		else {
			int k = 0;
			while (j < len2) {
				result[i] = str[j];
				result[i + 1] = str[j + 1];
				result[i + 2] = str2[j];
				result[i + 3] = str2[j + 1];
				i += 4;
				j += 2;
			}
			int sdwig = 0;
			while (k < ostlen) {
				result[i] = str[len2 + sdwig];
				k++;
				sdwig++;
				i++;
			}
			result[i] = '\0';
		}
	}
	else {
		int ostlen = len1 - len2;
		if (len1 % 2 != 0) {
			int k = 0;
			while (j < len1 - 1) {
				result[i] = str[j];
				result[i + 1] = str[j + 1];
				result[i + 2] = str2[j];
				result[i + 3] = str2[j + 1];
				i += 4;
				j += 2;
			}
			result[i] = str[j];
			result[i + 1] = str[j + 1];
			result[i + 2] = str2[j];
			i += 3;
			int sdwig = 1;
			while (k < ostlen) {
				result[i] = str[len2 + sdwig];
				k++;
				sdwig++;
				i++;
			}
		}
		else {
			int k = 0;
			while (j < len1) {
				result[i] = str[j];
				result[i + 1] = str[j + 1];
				result[i + 2] = str2[j];
				result[i + 3] = str2[j + 1];
				i += 4;
				j += 2;
			}
			int sdwig = 0;
			while (k < ostlen) {
				result[i] = str[len2 + sdwig];
				k++;
				sdwig++;
				i++;
			}
			result[i] = '\0';
		}
	}
}
