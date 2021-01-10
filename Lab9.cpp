#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE 
#include "windows.h"
#include <locale>
#include <iostream>
using namespace std;

const int MAXLINE = 255;

FILE* FirstFile, * SecondFile;

// Скопировать все строки из F1 в F2, содержащие одно слово
// Условимся что слова разделяются пробелом

void FirstTask() {
	FirstFile = fopen("F1.txt", "r");
	SecondFile = fopen("F2.txt", "w");
	char buffer[MAXLINE];
	while (fgets(buffer, MAXLINE, FirstFile) != 0) {
		bool OneWord = true;
		int i = 0;
		while (buffer[i] != '\0') {
			if (buffer[i++] == ' ') {
				OneWord = false;
				break;
			}
		}
		if (OneWord == true)
			fputs(buffer, SecondFile);
	}
	fclose(FirstFile);
	fclose(SecondFile);
}

// Самое длинное слово.

void SecondTask() {
	SecondFile = fopen("F2.txt", "r");
	char buffer[MAXLINE];
	char BiggestWord[MAXLINE];
	int Length = 0;
	while (fgets(buffer, MAXLINE, SecondFile) != 0) {
		int i = 0;
		while (buffer[i] != '\0') {
			i++;
		}
		if (i > Length) {
			for (int j = 0; j <= i; ++j) {
				BiggestWord[j] = buffer[j];
			}
			Length = i;
		}

	}
	cout << "BiggestWord: \"";
	for (int i = 0; i < Length; ++i) {
		if (BiggestWord[i] != '\n') {
			cout << BiggestWord[i];
		}
		else {
			cout << "\"" << BiggestWord[i];
		}
	}

	fclose(SecondFile);
}

int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");
	FirstTask();
	SecondTask();	
	system("pause");
	return 0;
}
