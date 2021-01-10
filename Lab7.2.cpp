#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <cstdarg>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <locale>
#include <iostream>
#include <iomanip>

using namespace std;

// 1 - double, 0 - int

double Max (int type, ...){
    int *ptr=&type;
    ++ptr;
    if (type==1){
        double *nptr=(double *)ptr; // настраиваем указатель на дабл.
        double res=*nptr;
        for (; *nptr; nptr++){
            res=(*nptr>res? *nptr: res);
        }
        return res;
    }
    else{
        double res=*ptr;
        for (; *ptr; ptr++){
            res=(*ptr>res? *ptr: res);
        }
        return res;
    }
}


int main (){
    SetConsoleOutputCP(CP_UTF8);
    cout << "Максимум среди целых чисел: {2; -1; 3} это "
    << Max (0,2,-1,3,0) << endl;
    cout << "Максимум среди чисел с плавающей точкой: {3.14; 2.71; 1.41; 1.73; 0.57} это "
    << Max (1,3.14,2.71,1.41,1.73,0.57,0.0) << endl;
    cout << "Максимум среди целых чисел: {2; 3; 12; -12; -558; 102; 7; 8; 9; 230; -11; -12} это "
    << Max (0,2, 3, 12, -12, -558, 102, 7, 8, 9, 230, -11, -12, 0) << endl;

    return 0;
}
