#include <iostream>
using namespace std;

int const razmer = 8;

bool mozno(int doska[razmer][razmer], int stroka, int stolb) {
    // 1. столбец
    for (int i = 0; i < stroka; i++) {
        if (doska[i][stolb] == 1) {
            return false;
        }
    }
    // 2. левая верхняя диагональ
    for (int i = stroka, j = stolb; i >= 0 && j >= 0; i--, j--) {
        if (doska[i][j] == 1) {
            return false;
        }
    }
    // 3. правая верхняя диагональ
    for (int i = stroka, j = stolb; i >= 0 && j < razmer; i--, j++) {  
        if (doska[i][j] == 1) {
            return false;
        }
    }
    return true;
}

void vivod(int doska[razmer][razmer], int nomer) {
    cout << "Решение № " << nomer << endl; 
    for (int i = 0; i < razmer; i++) {
        for (int j = 0; j < razmer; j++) {  
            if (doska[i][j] == 1) {
                cout << " Q ";  
            } 
            else {
                cout << " . ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void reshenie(int doska[razmer][razmer], int stroka, int &nomer) {
    if (stroka == razmer) {
        nomer++;
        vivod(doska, nomer);
        return;
    }
    for (int stolb = 0; stolb < razmer; stolb++) {
        if (mozno(doska, stroka, stolb)) {
            doska[stroka][stolb] = 1;
            reshenie(doska, stroka + 1, nomer);
            doska[stroka][stolb] = 0;
        }
    }
}

int main() {
    int doska[razmer][razmer] = {0};
    int number = 0;
    reshenie(doska, 0, number);
    if (number == 0) {
        cout << "Решений не найдено";
    } 
    else {
        cout << "Всего решений: " << number << endl;
    }
    return 0;
}