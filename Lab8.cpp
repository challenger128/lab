#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE 
#include "windows.h"
#include <locale>
#include <iostream>
using namespace std;

struct Patient {
    char surname[30];		//�������
    char name[30];			//���
    char patronymic[30];	//��������
    char adress[70];        //�����
    int medcard;            //��������  
    int insurance;          //���������
};

Patient NewPatient() {
    Patient Bob;
    cout << "������� -> ";
    cin >> Bob.surname;
    cout << "��� -> ";
    cin >> Bob.name;
    cout << "�������� -> ";
    cin >> Bob.patronymic;
    cout << "����� -> ";
    cin >> Bob.adress;
    cout << "�������� (9-�� ������� �����) -> ";
    cin >> Bob.medcard;
    cout << "��������� (9-�� ������� �����) -> ";
    cin >> Bob.insurance;
    return Bob;
}

FILE* MyFile;       //����
int CountRegister;  //���������� ����������� (�.�. �������)


void CreateFile() {
    MyFile = fopen("patients.dat", "wb");
    if (MyFile == 0) {
        cout << "������ ��� �������� ����� !\n";
        exit(1);
    }
    cout << "\n������������ ����� �������� ... \n\n";
    CountRegister = 0;
    bool binInput;
    cout << "�������� ������ � ��������? �� (1) / ��� (0) -> ";
    cin >> binInput;
    while (binInput) {
        Patient client = NewPatient();
        fwrite(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "������ ������ � ���� !\n";
            exit(2);
        }
        CountRegister++;
        cout << "�������� ������ � ��������? �� (1) / ��� (0) -> ";
        cin >> binInput;
    }
    fclose(MyFile);
}

void ReadFile() {
    cout << "\n������ ����� �������� ... \n\n";
    MyFile = fopen("patients.dat", "rb");
    if (MyFile == 0) {
        cout << "������ �������� ����� ! \n";
        exit(1);
    }
    Patient client;
    int cnt = 0;
    while (!feof(MyFile) && cnt < CountRegister) {
        fread(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "������ ������ ����� ! \n";
            exit(4);
        }
        cnt++;
        cout << "������� -> " << client.surname << '\n';
        cout << "��� -> " << client.name << '\n';
        cout << "�������� -> " << client.patronymic << '\n';
        cout << "����� -> " << client.adress << '\n';
        cout << "����� �������� -> " << client.medcard << '\n';
        cout << "����� ��������� -> " << client.insurance << '\n';
    }
    fclose(MyFile);
}

void AddPatient() {
    FILE* tmp;
    cout << "\n���������� 2-�� ��������� � ������ ����� �������� ... \n\n";
    tmp = fopen("tmp.dat", "wb");
    if (tmp == 0) {
        cout << "������ �������� ����� \n ";
        exit(1);
    }
    MyFile = fopen("patients.dat", "rb");
    if (MyFile == 0) {
        cout << "������ �������� ����� ! \n ";
        exit(1);
    }
    for (int i = 0; i < 2; ++i) {
        Patient client = NewPatient();
        cout << '\n';
        fwrite(&client, sizeof(Patient), 1, tmp);
        if (ferror(tmp) != 0) {
            cout << "������ ������ ����� ! \n ";
            exit(2);
        }
    }
    int cnt = 0;
    while (!feof(MyFile) && cnt < CountRegister) {
        Patient client;
        fread(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "������ ������ ����� ! \n";
            exit(4);
        }
        fwrite(&client, sizeof(Patient), 1, tmp);
        if (ferror(tmp) != 0) {
            cout << "������ ������ ����� ! \n";
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
    cout << "\n�������� �������� �������� ... \n\n";
    int medcard;
    cout << "������� ����� �������� ��� �������� �������� -> ";
    cin >> medcard;
    MyFile = fopen("patients.dat", "rb");
    if (MyFile == 0) {
        cout << "������ �������� ����� ! \n";
        exit(1);
    }
    tmp = fopen("tmp.dat", "wb");
    if (tmp == 0) {
        cout << "������ �������� ����� ! \n";
        exit(1);
    }
    int cnt = 0;
    while (!feof(MyFile) && cnt < CountRegister) {
        Patient client;
        fread(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "������ ������ ����� ! \n";
            exit(4);
        }
        if (client.medcard != medcard) {
            fwrite(&client, sizeof(Patient), 1, tmp);
            if (ferror(tmp) != 0) {
                cout << "������ ������ ����� ! \n";
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
    cout << "\n���� ����� ���������� 2-�� ���������\n";
    ReadFile();
    DeletePatient();
    cout << "\n���� ����� �������� ��������\n";
    ReadFile();
    system("pause");
    return 0;
}