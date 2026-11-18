#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <set> // Добавили set для удобства проверки уникальности склеек

using namespace std;

const int N = 4;
const int KOLVO_NABOROV = 16;

struct Term {
    int perem[4]; 
};

struct Skleika {
    Term term;
    int nomer1; 
    int nomer2; 
};

// Вспомогательная функция для вывода терма в строку
string poluchitStroku(Term t) {
    string s = "";
    for (int k = 0; k < N; k++) {
        char perem = (char)('a' + k);
        if (t.perem[k] == 1) s += perem;
        else if (t.perem[k] == 0) { s += "~"; s += perem; }
    }
    if (s == "") return "1";
    return s;
}

void tablicaistinnosti(const vector<int>& f) {
    cout << "\n===== ТАБЛИЦА ИСТИННОСТИ =====\n";
    cout << "a b c d | f\n";
    cout << "--------+---\n";
    for (int i = 0; i < KOLVO_NABOROV; i++) {
        for (int bit = N - 1; bit >= 0; bit--) cout << ((i >> bit) & 1) << " ";
        cout << "| " << f[i] << "\n";
    }
}

void vyvestiSDNF(const vector<int>& f) {
    cout << "\n===== ПОСТРОЕНИЕ СДНФ =====\n";
    cout << "Обозначения: ~ (тильда) - ОТРИЦАНИЕ, v - ИЛИ, * - И\n\n";
    bool pervaya = true;
    int nomerTerma = 1;

    for (int i = 0; i < KOLVO_NABOROV; i++) {
        if (f[i] != 1) continue;
        cout << "Терм " << nomerTerma << " (строка ";
        for (int bit = N - 1; bit >= 0; bit--) cout << ((i >> bit) & 1);
        cout << "):\n  ";
        if (!pervaya) cout << "v ";
        pervaya = false;
        for (int bit = N - 1; bit >= 0; bit--) {
            char perem = (char)('a' + (N - 1 - bit));
            int znachenie = (i >> bit) & 1;
            if (bit < N - 1) cout << " * ";
            if (znachenie == 1) cout << perem;
            else cout << "~" << perem;
        }
        cout << "\n";
        nomerTerma++;
    }
    
    cout << "\nИТОГОВАЯ СДНФ:\n";
    pervaya = true;
    for (int i = 0; i < KOLVO_NABOROV; i++) {
        if (f[i] != 1) continue;
        if (!pervaya) cout << " v ";
        pervaya = false;
        for (int bit = N - 1; bit >= 0; bit--) {
            char perem = (char)('a' + (N - 1 - bit));
            int znachenie = (i >> bit) & 1;
            if (znachenie == 1) cout << perem;
            else cout << "~" << perem;
        }
    }
    if (pervaya) cout << "0 (функция тождественный ноль)";
    cout << "\n";
}

// =========================================================================
// НОВАЯ ФУНКЦИЯ: МНОГОСТУПЕНЧАТОЕ СКЛЕИВАНИЕ
// =========================================================================
void naitiSkleiki(const vector<int>& f) {
    // 1. Переводим все единицы из СДНФ в структуры Term
    vector<Term> tekushie;
    for (int i = 0; i < KOLVO_NABOROV; i++) {
        if (f[i] == 1) {
            Term t;
            for (int bit = N - 1; bit >= 0; bit--) t.perem[N - 1 - bit] = (i >> bit) & 1;
            tekushie.push_back(t);
        }
    }

    if (tekushie.empty()) {
        cout << "Функция тождественный ноль, склеивать нечего.\n";
        return;
    }

    cout << "\n===== РЕЗУЛЬТАТЫ СКЛЕИВАНИЙ =====\n";
    
    vector<Term> vseProstyeImplikanty; // Сюда будем собирать итоговые склейки
    int shag = 1;

    // 2. Запускаем цикл, пока есть что склеивать
    while (true) {
        vector<Term> novyeSkleiki;      // Склейки, полученные на этом шаге
        vector<bool> ispolzovano(tekushie.size(), false); // Флаги: участвовал ли терм в склейке

        // Сравниваем все пары текущего уровня
        for (int i = 0; i < (int)tekushie.size(); i++) {
            for (int j = i + 1; j < (int)tekushie.size(); j++) {
                
                int razlichiya = 0;
                int pozRazlichiya = -1;
                
                // Считаем различия (2 - это прочерк, он не считается за различие, если совпадает)
                for (int k = 0; k < N; k++) {
                    if (tekushie[i].perem[k] != 2 && tekushie[j].perem[k] != 2) {
                        if (tekushie[i].perem[k] != tekushie[j].perem[k]) {
                            razlichiya++;
                            pozRazlichiya = k;
                        }
                    }
                }

                // Если различие ровно 1 - склеиваем
                if (razlichiya == 1) {
                    ispolzovano[i] = true;
                    ispolzovano[j] = true;

                    Term skleika;
                    for (int k = 0; k < N; k++) {
                        if (k == pozRazlichiya) skleika.perem[k] = 2;
                        else if (tekushie[i].perem[k] == 2) skleika.perem[k] = 2;
                        else skleika.perem[k] = tekushie[i].perem[k];
                    }

                    // Проверяем, нет ли уже такой склейки в новом списке (избегаем дублей)
                    bool estUje = false;
                    for (const auto& s : novyeSkleiki) {
                        bool odinakovo = true;
                        for (int k = 0; k < N; k++) {
                            if (s.perem[k] != skleika.perem[k]) { odinakovo = false; break; }
                        }
                        if (odinakovo) { estUje = true; break; }
                    }

                    if (!estUje) {
                        novyeSkleiki.push_back(skleika);
                        cout << "Шаг " << shag << ": (" << poluchitStroku(tekushie[i]) 
                             << ") и (" << poluchitStroku(tekushie[j]) << ") => " 
                             << poluchitStroku(skleika) << "\n";
                    }
                }
            }
        }

        // Если склеек не нашлось - выходим из цикла
        if (novyeSkleiki.empty()) break;

        // Термы, которые НЕ участвовали в склейке на этом шаге, становятся простыми импликантами
        for (int i = 0; i < (int)tekushie.size(); i++) {
            if (!ispolzovano[i]) {
                vseProstyeImplikanty.push_back(tekushie[i]);
            }
        }

        // Переходим на следующий уровень: теперь склеиваем новые склейки
        tekushie = novyeSkleiki;
        shag++;
    }

    // Те, что остались в tekushie после последнего прохода - тоже простые импликанты
    for (int i = 0; i < (int)tekushie.size(); i++) {
        vseProstyeImplikanty.push_back(tekushie[i]);
    }

    // ========================================================
    // ВЫВОД ИМПЛИКАНТНОЙ МАТРИЦЫ (по итоговым склейкам)
    // ========================================================
    cout << "\n===== ИМПЛИКАНТНАЯ МАТРИЦА =====\n";
    
    // Сначала соберем исходные термы (из СДНФ)
    vector<Term> ishodnye;
    for (int i = 0; i < KOLVO_NABOROV; i++) {
        if (f[i] == 1) {
            Term t;
            for (int bit = N - 1; bit >= 0; bit--) t.perem[N - 1 - bit] = (i >> bit) & 1;
            ishodnye.push_back(t);
        }
    }

    int shirina = 12;
    
    // Верхняя линия
    cout << "+" << string(shirina, '-') << "+";
    for (int i = 0; i < (int)ishodnye.size(); i++) cout << string(shirina, '-') << "+";
    cout << "\n";

    // Шапка (исходные термы)
    cout << "|" << string(shirina, ' ') << "|";
    for (int i = 0; i < (int)ishodnye.size(); i++) {
        string s = poluchitStroku(ishodnye[i]);
        cout << " " << s << string(shirina - 1 - (int)s.length(), ' ') << "|";
    }
    cout << "\n";

    // Разделитель
    cout << "+" << string(shirina, '-') << "+";
    for (int i = 0; i < (int)ishodnye.size(); i++) cout << string(shirina, '-') << "+";
    cout << "\n";

    // Строки (итоговые импликанты)
    for (int i = 0; i < (int)vseProstyeImplikanty.size(); i++) {
        string s = poluchitStroku(vseProstyeImplikanty[i]);
        cout << "| " << s << string(shirina - 1 - (int)s.length(), ' ') << "|";
        
        for (int j = 0; j < (int)ishodnye.size(); j++) {
            bool podhodit = true;
            for (int k = 0; k < N; k++) {
                if (vseProstyeImplikanty[i].perem[k] != 2 && vseProstyeImplikanty[i].perem[k] != ishodnye[j].perem[k]) {
                    podhodit = false;
                    break;
                }
            }
            string val = podhodit ? "+" : ".";
            cout << " " << val << string(shirina - 2, ' ') << "|";
        }
        cout << "\n";
        
        // Нижняя линия
        cout << "+" << string(shirina, '-') << "+";
        for (int j = 0; j < (int)ishodnye.size(); j++) cout << string(shirina, '-') << "+";
        cout << "\n";
    }
}
// =========================================================================

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    vector<int> f(KOLVO_NABOROV, 0);
    bool vektorVveden = false;
    while (true) {
        cout << "\n===== ЛАБОРАТОРНАЯ РАБОТА №3 =====\n";
        cout << "1. Ввести вектор функции (16 чисел)\n";
        cout << "2. Таблица истинности\n";
        cout << "3. СДНФ\n";
        cout << "4. Склейки и матрица\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 0) break;

        if (choice >= 2 && choice <= 4 && !vektorVveden) {
            cout << "Сначала введите вектор (пункт 1)!\n";
            continue;
        }

        if (choice == 1) {
            cout << "Введите вектор (16 чисел 0/1):\n";
            string stroka;
            cin.ignore(10000, '\n');
            getline(cin, stroka);
            string ochishennaya = "";
            for (int i = 0; i < (int)stroka.length(); i++) {
                if (stroka[i] == '0' || stroka[i] == '1') ochishennaya += stroka[i];
            }
            
            if (ochishennaya.length() != KOLVO_NABOROV) {
                cout << "Ошибка: нужно ровно 16 цифр!\n";
            } else {
                for (int i = 0; i < KOLVO_NABOROV; i++) f[i] = ochishennaya[i] - '0';
                vektorVveden = true;
                cout << "Вектор сохранен.\n";
            }
        }
        else if (choice == 2) tablicaistinnosti(f);
        else if (choice == 3) vyvestiSDNF(f);
        else if (choice == 4) naitiSkleiki(f);
    }

    return 0;
}