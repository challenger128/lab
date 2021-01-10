#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <locale>
#include <iostream>
using namespace std;

struct Fraction {
    int numerator;    // числитель
    int denominator;  // знаменатель
};

double Sum(double a, double b) {
    return a + b;
}

Fraction Sum(Fraction a, Fraction b) {
    return { a.numerator * b.denominator + b.numerator * a.denominator,
            a.denominator * b.denominator };
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Введите два десятичных числа\n";
    double a, b;
    cout << "Число №1 -> ";
    cin >> a;
    cout << "Число №2 -> ";
    cin >> b;
    cout << "Введите две обыкновенные дроби\n";
    Fraction c, d;
    cout << "Числитель и знаменатель первой дроби -> ";
    cin >> c.numerator >> c.denominator;
    cout << "Числитель и знаменатель второй дроби -> ";
    cin >> d.numerator >> d.denominator;
    cout << "Сумма десятичных дробей: " << a << " + " << b << " = " << Sum(a, b) << endl;
    cout << "Сумма обыкновенных дробей: " << c.numerator << '/' << c.denominator << " + " <<
        d.numerator << '/' << d.denominator << " = " << Sum(c, d).numerator << '/' << Sum(c, d).denominator << endl;

    return 0;
}
