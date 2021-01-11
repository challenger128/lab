#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale>
#include <iostream>

using namespace std;

FILE* MyFile;
const char* filename = "output.txt";

struct Node {
    int value;
    Node* next;
    Node* prev;
};

Node* CreateList(int ListSize) {
    Node* FirstElement, * LastElement, * tmp;
    if (ListSize == 0) {
        FirstElement = nullptr;
    }
    else {
        FirstElement = new(Node);
        FirstElement->value = 1;
        FirstElement->prev = nullptr;
        LastElement = FirstElement;
        for (int i = 2; i <= ListSize; ++i) {
            tmp = new(Node);
            tmp->value = i;
            tmp->prev = LastElement;
            LastElement->next = tmp;
            LastElement = tmp;
        }
        LastElement->next = nullptr;
    }
    return FirstElement;
}

void PrintList(Node* FirstElement) {
    if (FirstElement == nullptr) {
        cout << "Список пуст \n";
    }
    else {
        cout << "NULL <-> ";
        while (FirstElement != nullptr) {
            cout << FirstElement->value << " <-> ";
            FirstElement = FirstElement->next;
        }
        cout << "NULL\n";
    }
}

Node* AddBack(Node* FirstElement, int k) {
    if (FirstElement == 0) {
        if (k != 0) {
            FirstElement = new (Node);
            FirstElement->prev = nullptr;
            FirstElement->value = 1;
            Node* tmp, * LastElement;
            LastElement = FirstElement;
            for (int i = 2; i <= k; ++i) {
                tmp = new (Node);
                tmp->value = i;
                tmp->prev = LastElement;
                LastElement->next = tmp;
                LastElement = tmp;
            }
            LastElement->next = nullptr;
        }
    }
    else {
        Node* LastElement = FirstElement;
        while (LastElement->next != 0) {
            LastElement = LastElement->next;
        }
        LastElement->next = new (Node);
        LastElement->next->value = LastElement->value + 1;
        LastElement->next->prev = LastElement;
        LastElement = LastElement->next;
        Node* tmp;
        for (int i = 2; i <= k; ++i) {
            tmp = new (Node);
            tmp->value = LastElement->value + 1;
            tmp->prev = LastElement;
            LastElement->next = tmp;
            LastElement = tmp;
        }
        LastElement->next = nullptr;
    }
    return FirstElement;
}

Node* DeleteFromList(Node* FirstElement, int n, int k) {
    Node* tmp = FirstElement;
    bool Found = false;
    while (tmp->next != nullptr) {
        if (tmp->value == n) {
            Found = true;
            break;
        }
        tmp = tmp->next;
    }

    if (tmp->value == n) {
        Found = true;
    }

    if (!Found) {
        cout << "Такого элемента нет \n ";
        return FirstElement;
    }
    else {
        Node* ntmp = tmp->prev;
        while (k > 0) {
            if (ntmp == FirstElement) {
                ntmp->next->prev = nullptr;
                Node* nntmp = ntmp->next;
                delete ntmp;
                return nntmp;
            }
            ntmp->prev->next = ntmp->next;
            Node* nntmp = ntmp->prev;
            delete ntmp;
            ntmp = nntmp;
            k--;
        }
        return FirstElement;
    }
}

void FilePrintList(Node* FirstElement) {
    MyFile = fopen(filename, "w");
    while (FirstElement != nullptr) {
        fprintf(MyFile, "%d ", FirstElement->value);
        FirstElement = FirstElement->next;
    }
    fclose(MyFile);
}

Node* CreateListFromFile() {
    MyFile = fopen(filename, "r");
    Node* FirstElement, * LastElement, * tmp;
    if (feof(MyFile)) {
        FirstElement = nullptr;
    }
    else {
        int key = 0;
        FirstElement = new (Node);
        fscanf(MyFile, "%d", &key);
        FirstElement->value = key;
        FirstElement->prev = nullptr;
        LastElement = FirstElement;
        fscanf(MyFile, "%d", &key);
        while (!feof(MyFile)) {
            tmp = new (Node);
            tmp->value = key;
            tmp->prev = LastElement;
            LastElement->next = tmp;
            LastElement = tmp;
            fscanf(MyFile, "%d", &key);
        }
        LastElement->next = nullptr;
    }
    fclose(MyFile);
    return FirstElement;
}

Node* DeleteList(Node* FirstElement) {
    while (FirstElement != 0) {
        Node* tmp = FirstElement->next;
        delete FirstElement;
        FirstElement = tmp;
    }
    return FirstElement;
}



int main() {
    setlocale(LC_ALL, "Russian");
    cout << "\nСоздание списка ... \n";
    int n;
    cout << "Введите желаемое число элементов списка -> ";
    cin >> n;
    Node* List = CreateList(n);
    cout << "\nПечать списка ... \n";
    PrintList(List);
    cout << "\nДобавление k элементов в конец списка ... \n";
    cout << "Введите k -> ";
    cin >> n;
    List = AddBack(List, n);
    cout << "\nПечать списка ... \n";
    PrintList(List);
    cout << "\nВывод в файл списка ... \n";
    FilePrintList(List);
    cout << "\nУдаление списка ... \n";
    List = DeleteList(List);
    cout << "\nПечать списка ... \n";
    PrintList(List);
    cout << "\nВосстановление списка из файла ... \n";
    List = CreateListFromFile();
    cout << "\nПечать списка ... \n";
    PrintList(List);
    cout << "\nУдаление k элементов перед элементом n ... \n";
    cout << "Введите n -> ";
    cin >> n;
    int k;
    cout << "Введите k -> ";
    cin >> k;
    List = DeleteFromList(List, n, k);
    cout << "\nПечать списка ... \n";
    PrintList(List);
    cout << "\nВосстановление списка из файла ... \n";
    List = CreateListFromFile();
    cout << "\nПечать списка ... \n";
    PrintList(List);
    return 0;
}
