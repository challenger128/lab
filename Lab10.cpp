#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <cstdlib> 
#include <iostream>
#include <math.h>
#include <ctime>
#include <locale>
#include <random>
using namespace std;

// Выделение двумерного массива, 
// вообще говоря существует двумерного массива с использованием 
// всего двух операций new, которые меньше "фрагментируют" нашу память, 
// но здесь мы напишем наивное решение.


int** CreateMatrix(int x, int y) {
	int** Array = new int* [x];
	for (int i = 0; i < x; ++i) {
		Array[i] = new int[y];
	}
	return Array;
}

void FillMatrix(int** Matrix, int x, int y) {
	mt19937 rndm; // Вихрь Мерсенна, самый мощный генератор псевдослучайных чисел разработанный японскими учеными.
	rndm.seed(time(0)); // Устанавливаем "зерно"
	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			Matrix[i][j] = rndm() % 1024;
		}
	}
}

void PrintMatrix(int** Matrix, int x, int y) {
	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			cout << Matrix[i][j] << ' ';
		}
		cout << '\n';
	}
}

void DeleteMatrix(int** Matrix, int x, int y) {
	for (int i = 0; i < x; ++i) {
		delete[] Matrix[i];
	}
	delete[] Matrix;
}

// Добавляем к-тый столбец
// Можно было бы не возвращать указатель на указатель, но тогда бы приходилось
// передавать в функцию указатель на указатель на указатель, для того чтобы изменить внешнюю **Matrix
int** AddKthCol(int ** Matrix, int x, int& y) {
	cout << "\nДобавление столбца ... \n";
	cout << "Введите номер столбца -> ";
	int k; 
	cin >> k;
	if (k > y) {
		int** tmp = new int* [x];
		for (int i = 0; i < x; ++i) {
			tmp[i] = new int[y];
		}
		for (int i = 0; i < x; ++i) {
			for (int j = 0; j < y; ++j) {
				tmp[i][j] = Matrix[i][j];
			}
		}
		DeleteMatrix(Matrix, x, y);
		Matrix = new int* [x];
		for (int i = 0; i < x; ++i) {
			Matrix[i] = new int[k];
		}
		for (int i = 0; i < x; ++i) {
			for (int j = 0; j < k; ++j) {
				if (j < y) {
					Matrix[i][j] = tmp[i][j];
				}
				else Matrix[i][j] = 0;
			}
		}
		DeleteMatrix(tmp, x, y);
		y = k;
		cout << "Добавление прошло успешно ... \n";
		PrintMatrix(Matrix, x, y);
	}
	else {
		cout << "Данный столбец уже существует \n";
	}
	return Matrix;
}





int main() {

	setlocale(LC_ALL, "Russian");
	int x, y;
	cout << "Введите размерность матрицы (двумерного массива) \n";
	cout << "Введите количество строк -> ";
	cin >> x;
	cout << "Введите количество столбцов -> ";
	cin >> y;
	int** Matrix = CreateMatrix(x, y);
	FillMatrix(Matrix, x, y);
	PrintMatrix(Matrix, x, y);
	Matrix=AddKthCol(Matrix, x, y);
	DeleteMatrix(Matrix, x, y);
	system("pause");
	return 0;
}

