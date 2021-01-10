#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE 
#include "windows.h"
#include <locale>
#include <iostream>
using namespace std;

struct Patient {
    char surname[30];		//Фамилия
    char name[30];			//Имя
    char patronymic[30];	//Отчество
    char adress[70];        //Адрес
    int medcard;            //Медкарта  
    int insurance;          //Страховка
};

Patient NewPatient() {
    Patient Bob;
    cout << "Фамилия -> ";
    cin >> Bob.surname;
    cout << "Имя -> ";
    cin >> Bob.name;
    cout << "Отчество -> ";
    cin >> Bob.patronymic;
    cout << "Адрес -> ";
    cin >> Bob.adress;
    cout << "Медкарта (9-ти значное число) -> ";
    cin >> Bob.medcard;
    cout << "Страховка (9-ти значное число) -> ";
    cin >> Bob.insurance;
    return Bob;
}

FILE* MyFile;       //Файл
int CountRegister;  //Количество Регистраций (т.е. записей)


void CreateFile() {
    MyFile = fopen("patients.dat", "wb");
    if (MyFile == 0) {
        cout << "Ошибка при открытии файла !\n";
        exit(1);
    }
    cout << "\nФормирование файла началось ... \n\n";
    CountRegister = 0;
    bool binInput;
    cout << "Добавить запись о пациенте? Да (1) / Нет (0) -> ";
    cin >> binInput;
    while (binInput) {
        Patient client = NewPatient();
        fwrite(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "Ошибка записи в файл !\n";
            exit(2);
        }
        CountRegister++;
        cout << "Добавить запись о пациенте? Да (1) / Нет (0) -> ";
        cin >> binInput;
    }
    fclose(MyFile);
}

void ReadFile() {
    cout << "\nЧтение файла началось ... \n\n";
    MyFile = fopen("patients.dat", "rb");
    if (MyFile == 0) {
        cout << "Ошибка открытия файла ! \n";
        exit(1);
    }
    Patient client;
    int cnt = 0;
    while (!feof(MyFile) && cnt < CountRegister) {
        fread(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "Ошибка чтения файла ! \n";
            exit(4);
        }
        cnt++;
        cout << "Фамилия -> " << client.surname << '\n';
        cout << "Имя -> " << client.name << '\n';
        cout << "Отчество -> " << client.patronymic << '\n';
        cout << "Адрес -> " << client.adress << '\n';
        cout << "Номер медкарты -> " << client.medcard << '\n';
        cout << "Номер страховки -> " << client.insurance << '\n';
    }
    fclose(MyFile);
}

void AddPatient() {
    FILE* tmp;
    cout << "\nДобавление 2-ух пациентов в начало файла началось ... \n\n";
    tmp = fopen("tmp.dat", "wb");
    if (tmp == 0) {
        cout << "Ошибка открытия файла \n ";
        exit(1);
    }
    MyFile = fopen("patients.dat", "rb");
    if (MyFile == 0) {
        cout << "Ошибка открытия файла ! \n ";
        exit(1);
    }
    for (int i = 0; i < 2; ++i) {
        Patient client = NewPatient();
        cout << '\n';
        fwrite(&client, sizeof(Patient), 1, tmp);
        if (ferror(tmp) != 0) {
            cout << "Ошибка записи файла ! \n ";
            exit(2);
        }
    }
    int cnt = 0;
    while (!feof(MyFile) && cnt < CountRegister) {
        Patient client;
        fread(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "Ошибка чтения файла ! \n";
            exit(4);
        }
        fwrite(&client, sizeof(Patient), 1, tmp);
        if (ferror(tmp) != 0) {
            cout << "Ошибка записи файла ! \n";
            exit(2);
        }
    }
    CountRegister += 2;
    fclose(MyFile);
    fclose(tmp);
    remove("patients.dat");
    rename("tmp.dat", "patients.dat");
}

void DeletePatient() {
    FILE* tmp;
    cout << "\nУдаление пациента началось ... \n\n";
    int medcard;
    cout << "Введите номер медкарты для удаления пациента -> ";
    cin >> medcard;
    MyFile = fopen("patients.dat", "rb");
    if (MyFile == 0) {
        cout << "Ошибка открытия файла ! \n";
        exit(1);
    }
    tmp = fopen("tmp.dat", "wb");
    if (tmp == 0) {
        cout << "Ошибка открытия файла ! \n";
        exit(1);
    }
    int cnt = 0;
    while (!feof(MyFile) && cnt < CountRegister) {
        Patient client;
        fread(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "Ошибка чтения файла ! \n";
            exit(4);
        }
        if (client.medcard != medcard) {
            fwrite(&client, sizeof(Patient), 1, tmp);
            if (ferror(tmp) != 0) {
                cout << "Ошибка записи файла ! \n";
                exit(2);
            }
        }
        cnt++;
    }
    fclose(tmp);
    fclose(MyFile);
    remove("patients.dat");
    rename("tmp.dat", "patients.dat");
    CountRegister--;
}

int main() {
    setlocale(LC_ALL, "Russian"); 
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    CreateFile();
    ReadFile();
    AddPatient();
    cout << "\nФайл после добавления 2-ух пациентов\n";
    ReadFile();
    DeletePatient();
    cout << "\nФайл после удаления пациента\n";
    ReadFile();
    system("pause");
    return 0;
}