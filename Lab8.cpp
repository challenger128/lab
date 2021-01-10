#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE 
#include "windows.h"
#include <locale>
#include <iostream>
using namespace std;

struct Patient {
    char surname[30];		//Ôàìèëèя
    char name[30];			//Èìÿ
    char patronymic[30];	//Îò÷åñòâî
    char adress[70];        //Àäðåñ
    int medcard;            //Ìåäêàðòà  
    int insurance;          //Ñòðàõîâêà
};

Patient NewPatient() {
    Patient Bob;
    cout << "Ôàìèëèÿ -> ";
    cin >> Bob.surname;
    cout << "Èìÿ -> ";
    cin >> Bob.name;
    cout << "Îò÷åñòâî -> ";
    cin >> Bob.patronymic;
    cout << "Àäðåñ -> ";
    cin >> Bob.adress;
    cout << "Ìåäêàðòà (9-òè çíà÷íîå ÷èñëî) -> ";
    cin >> Bob.medcard;
    cout << "Ñòðàõîâêà (9-òè çíà÷íîå ÷èñëî) -> ";
    cin >> Bob.insurance;
    return Bob;
}

FILE* MyFile;       //Ôàéë
int CountRegister;  //Êîëè÷åñòâî Ðåãèñòðàöèé (ò.å. çàïèñåé)


void CreateFile() {
    MyFile = fopen("patients.dat", "wb");
    if (MyFile == 0) {
        cout << "Îøèáêà ïðè îòêðûòèè ôàéëà !\n";
        exit(1);
    }
    cout << "\nÔîðìèðîâàíèå ôàéëà íà÷àëîñü ... \n\n";
    CountRegister = 0;
    bool binInput;
    cout << "Äîáàâèòü çàïèñü î ïàöèåíòå? Äà (1) / Íåò (0) -> ";
    cin >> binInput;
    while (binInput) {
        Patient client = NewPatient();
        fwrite(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "Îøèáêà çàïèñè â ôàéë !\n";
            exit(2);
        }
        CountRegister++;
        cout << "Äîáàâèòü çàïèñü î ïàöèåíòå? Äà (1) / Íåò (0) -> ";
        cin >> binInput;
    }
    fclose(MyFile);
}

void ReadFile() {
    cout << "\n×òåíèå ôàéëà íà÷àëîñü ... \n\n";
    MyFile = fopen("patients.dat", "rb");
    if (MyFile == 0) {
        cout << "Îøèáêà îòêðûòèÿ ôàéëà ! \n";
        exit(1);
    }
    Patient client;
    int cnt = 0;
    while (!feof(MyFile) && cnt < CountRegister) {
        fread(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "Îøèáêà ÷òåíèÿ ôàéëà ! \n";
            exit(4);
        }
        cnt++;
        cout << "Ôàìèëèÿ -> " << client.surname << '\n';
        cout << "Èìÿ -> " << client.name << '\n';
        cout << "Îò÷åñòâî -> " << client.patronymic << '\n';
        cout << "Àäðåñ -> " << client.adress << '\n';
        cout << "Íîìåð ìåäêàðòû -> " << client.medcard << '\n';
        cout << "Íîìåð ñòðàõîâêè -> " << client.insurance << '\n';
    }
    fclose(MyFile);
}

void AddPatient() {
    FILE* tmp;
    cout << "\nÄîáàâëåíèå 2-óõ ïàöèåíòîâ â íà÷àëî ôàéëà íà÷àëîñü ... \n\n";
    tmp = fopen("tmp.dat", "wb");
    if (tmp == 0) {
        cout << "Îøèáêà îòêðûòèÿ ôàéëà \n ";
        exit(1);
    }
    MyFile = fopen("patients.dat", "rb");
    if (MyFile == 0) {
        cout << "Îøèáêà îòêðûòèÿ ôàéëà ! \n ";
        exit(1);
    }
    for (int i = 0; i < 2; ++i) {
        Patient client = NewPatient();
        cout << '\n';
        fwrite(&client, sizeof(Patient), 1, tmp);
        if (ferror(tmp) != 0) {
            cout << "Îøèáêà çàïèñè ôàéëà ! \n ";
            exit(2);
        }
    }
    int cnt = 0;
    while (!feof(MyFile) && cnt < CountRegister) {
        Patient client;
        fread(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "Îøèáêà ÷òåíèÿ ôàéëà ! \n";
            exit(4);
        }
        fwrite(&client, sizeof(Patient), 1, tmp);
        if (ferror(tmp) != 0) {
            cout << "Îøèáêà çàïèñè ôàéëà ! \n";
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
    cout << "\nÓäàëåíèå ïàöèåíòà íà÷àëîñü ... \n\n";
    int medcard;
    cout << "Ââåäèòå íîìåð ìåäêàðòû äëÿ óäàëåíèÿ ïàöèåíòà -> ";
    cin >> medcard;
    MyFile = fopen("patients.dat", "rb");
    if (MyFile == 0) {
        cout << "Îøèáêà îòêðûòèÿ ôàéëà ! \n";
        exit(1);
    }
    tmp = fopen("tmp.dat", "wb");
    if (tmp == 0) {
        cout << "Îøèáêà îòêðûòèÿ ôàéëà ! \n";
        exit(1);
    }
    int cnt = 0;
    while (!feof(MyFile) && cnt < CountRegister) {
        Patient client;
        fread(&client, sizeof(Patient), 1, MyFile);
        if (ferror(MyFile) != 0) {
            cout << "Îøèáêà ÷òåíèÿ ôàéëà ! \n";
            exit(4);
        }
        if (client.medcard != medcard) {
            fwrite(&client, sizeof(Patient), 1, tmp);
            if (ferror(tmp) != 0) {
                cout << "Îøèáêà çàïèñè ôàéëà ! \n";
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
    cout << "\nÔàéë ïîñëå äîáàâëåíèÿ 2-óõ ïàöèåíòîâ\n";
    ReadFile();
    DeletePatient();
    cout << "\nÔàéë ïîñëå óäàëåíèÿ ïàöèåíòà\n";
    ReadFile();
    system("pause");
    return 0;
}
