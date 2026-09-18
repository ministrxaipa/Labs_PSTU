// ============================================================
// ПОДКЛЮЧАЕМ БАЗОВЫЕ БИБЛИОТЕКИ
// Это НЕ библиотеки про множества, а основа C++
// ============================================================

#include <iostream>   // cin (ввод с клавиатуры), cout (вывод на экран)
#include <vector>     // vector — динамический массив (список чисел), чтобы был "растущий список"
#include <string>     // string — текст (имя множества "A", "B")
#include <cstdlib>    // rand() и srand() — случайные числа
#include <ctime>      // time(0) — чтобы случайные числа были разными
#include <clocale>    // setlocale — русский язык в консоли

using namespace std;  // чтобы писать cout вместо std::cout


// ============================================================
// УНИВЕРСУМ — границы всех возможных чисел (из задания)
// ============================================================

const int MIN_CHISLO = -30;   // минимум
const int MAX_CHISLO = 30;    // максимум


// ============================================================
// БЕЗОПАСНЫЙ ВВОД ЧИСЛА
// Если пользователь введёт букву или мусор — программа НЕ зациклится,
// а попросит ввести заново.
// ============================================================

int vvod() {
    int x;
    // while крутится, пока cin НЕ сможет прочитать число
    // !(cin >> x) = "ввод провалился"
    while (!(cin >> x)) { //работает, пока ввод не удался
        cin.clear();               //сбросить флаг ошибки потока (cin отказывается читать неверное)
        cin.ignore(10000, '\n');   //выкинуть из буфера всё до конца строки, иначе может сломаться след. cin
        cout << "Nujno chislo, poprobui eshe: ";  // попросить снова
    }
    return x;  // вернуть корректное число
}


// ============================================================
// СТРУКТУРА "МНОЖЕСТВО"
//способ объядинить несколько переменных разного типа в одну коробку
//+функции(estLi, dobavit, sortirovat, ochistit) внутри этой структуры работают с этими полями
// ============================================================

struct Mnojestvo {
    string imya;             // имя: "A", "B", "C" (как называется)
    vector<int> chisla;      // сами числа (динамический список)
    bool sozdano;            // задано ли множество (true/false)

    // --- КОНСТРУКТОР без параметров ---
    // Вызывается при Mnojestvo m; гарантирует, что объект рождается в известном состоянии
    Mnojestvo() {
        imya = "";
        sozdano = false;
    }

    // --- КОНСТРУКТОР с именем ---
    // Вызывается при Mnojestvo m("A"); то же самое, но имя сразу задается
    Mnojestvo(string s) {
        imya = s;
        sozdano = false;
    }

    // --- Есть ли число x в множестве? ---
    bool estLi(int x) { //передаем x
        for (int i = 0; i < (int)chisla.size(); i++) { //пока i<размера ТЕКУЩЕГО списка (в который мы еще добавляем)
            if (chisla[i] == x) return true;  // нашли
        }
        return false;  // не нашли
    }

    // --- Добавить число x (с проверками) ---
    bool dobavit(int x) { //передаем x
        // Проверка 1: не выходит ли за универсум
        if (x < MIN_CHISLO || x > MAX_CHISLO) return false;

        // Проверка 2: уникальность (нет ли уже такого)
        if (estLi(x)) return false; //estLi=true ->dobavit=false

        // Всё ок — добавляем
        chisla.push_back(x);    //положи x в конец списка, размер +1
        return true;
    }

    // --- Сортировка пузырьком ---
    void sortirovat() {
        int n = (int)chisla.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (chisla[j] > chisla[j + 1]) {
                    // Обмен местами через временную переменную
                    int temp = chisla[j];
                    chisla[j] = chisla[j + 1];
                    chisla[j + 1] = temp;
                }
            }
        }
    }

    // --- Очистить множество ---
    void ochistit() {
        chisla.clear();
    }
};


// ============================================================
// ОПЕРАЦИИ НАД МНОЖЕСТВАМИ
// Каждая принимает 2 множества (или 1 для дополнения),
// возвращает НОВОЕ множество
// ============================================================

// --- ОБЪЕДИНЕНИЕ (A U B) ---
// Всё из A + всё из B, без повторов
Mnojestvo objedinenie(Mnojestvo A, Mnojestvo B) { //передаем 2 множества
    Mnojestvo rezultat; //создали пустое 
    rezultat.imya = A.imya + " U " + B.imya; //имя=A U B

    // Копируем числа из A
    for (int i = 0; i < (int)A.chisla.size(); i++) {
        rezultat.dobavit(A.chisla[i]);  // dobavit сам отсеет повторы
    }
    // Копируем числа из B
    for (int i = 0; i < (int)B.chisla.size(); i++) {
        rezultat.dobavit(B.chisla[i]);  //dobavit внутри себя вызывает estLi и не дает добавить повторы
    }

    rezultat.sortirovat();
    return rezultat;
}

// --- ПЕРЕСЕЧЕНИЕ (A ^ B) ---
// Только то, что есть И в A, И в B
Mnojestvo peresechenie(Mnojestvo A, Mnojestvo B) {
    Mnojestvo rezultat;
    rezultat.imya = A.imya + " ^ " + B.imya;

    for (int i = 0; i < (int)A.chisla.size(); i++) { //идем по числам в A
        // Если число из A есть и в B — добавляем
        if (B.estLi(A.chisla[i])) {
            rezultat.dobavit(A.chisla[i]);
        }
    }

    rezultat.sortirovat();
    return rezultat;
}

// --- РАЗНОСТЬ (A \ B) ---
// То, что есть в A, но НЕТ в B
Mnojestvo raznost(Mnojestvo A, Mnojestvo B) {
    Mnojestvo rezultat;
    rezultat.imya = A.imya + " \\ " + B.imya;  // "\\" = один символ \

    for (int i = 0; i < (int)A.chisla.size(); i++) {//идем по числам в А
        // ! = НЕ. Если числа нет в B — добавляем
        if (!B.estLi(A.chisla[i])) {
            rezultat.dobavit(A.chisla[i]);
        }
    }

    rezultat.sortirovat();
    return rezultat;
}

// --- ДОПОЛНЕНИЕ (~A) ---
// Всё из универсума, чего нет в A
Mnojestvo dopolnenie(Mnojestvo A) { //передаем 1 множество
    Mnojestvo rezultat; //создаем пустой результат
    rezultat.imya = "~" + A.imya;

    // Перебираем ВЕСЬ универсум от -30 до 30
    for (int x = MIN_CHISLO; x <= MAX_CHISLO; x++) {
        if (!A.estLi(x)) {         // если такого числа нет в A
            rezultat.dobavit(x);   // добавляем в результат
        }
    }

    rezultat.sortirovat();
    return rezultat;
}


// ============================================================
// ВЫВОД МНОЖЕСТВА НА ЭКРАН
// ============================================================

void pokazat(Mnojestvo m) { //передаем само множество
    cout << m.imya << " = {"; //печатаем имя (A,B,C)+'{'

    if (m.chisla.size() == 0) {//если множество пустое
        cout << "0";  // пустое множество (ASCII-замена символа ∅)
    } else {
        for (int i = 0; i < (int)m.chisla.size(); i++) {
            cout << m.chisla[i];
            // Запятую после всех, кроме последнего
            if (i + 1 < (int)m.chisla.size()) cout << ", ";
        }
    }

    cout << "}\n";
}


// ============================================================
// СПОСОБ 1: ЗАДАТЬ СЛУЧАЙНО
//пользователь говорит сколько нужно, программа случайно выбирает числа
//если случайно выпадет уже добавленное-не добавляем
// ============================================================
// & = передача по ссылке (изменения сохранятся в оригинале)
void zadatSluchaino(Mnojestvo& m) {
    cout << "Skolko elementov? ";
    int kolvo = vvod();                 // БЕЗОПАСНЫЙ ввод (защищает от букв)

    if (kolvo < 0) kolvo = 0;           // защита от отрицательного
    if (kolvo > MAX_CHISLO - MIN_CHISLO + 1)  // максимум = 61
        kolvo = MAX_CHISLO - MIN_CHISLO + 1;

    m.ochistit();                        // стираем старое

    int popytki = 0; //счетчик попыток На последних шагах почти все числа уже добавлены,
                    //и чтобы найти последнее свободное, нужно много попыток. 
                    // если не набрали-выходим из цикла
    int maxPopytok = kolvo * 200 + 1000; // страховка от бесконечного цикла

    // Пока не набрали нужное количество
    while ((int)m.chisla.size() < kolvo && popytki < maxPopytok) {//пока в множестве меньшь kolvo чисел
                                                                //и пока попыток меньше лимита
        // Случайное число от -30 до 30
        int x = MIN_CHISLO + rand() % (MAX_CHISLO - MIN_CHISLO + 1);//случайное_от_MIN_до_MAX = MIN + rand() % (MAX - MIN + 1)
        //пример: rand() = 100 → 100 % 61 = 39 → -30 + 39 = 9
        m.dobavit(x);                    // dobavit сам отсеет повторы
        popytki++;
    }

    m.sortirovat();
    m.sozdano = true;
    cout << "Gotovo.\n";
}


// ============================================================
// СПОСОБ 2: ЗАДАТЬ ВРУЧНУЮ
// ============================================================
void zadatRuchno(Mnojestvo& m) { //ссылка, иначе не было бы изменений (множество пустое)
    cout << "Skolko elementov? ";
    int kolvo = vvod();                 // БЕЗОПАСНЫЙ ввод 
    if (kolvo < 0) kolvo = 0;           //отриц убираем

    m.ochistit();       //стираем то, что было (если множество было заполнено)

    int i = 0;      //счётчик успешно добавленных чисел
    while (i < kolvo) { //пока их меньше нужного-крутимся
        cout << "Element " << (i + 1) << ": "; //спрашиваем очередное число
        int x = vvod();                 // БЕЗОПАСНЫЙ ввод

        // Проверка: число внутри универсума?
        if (x < MIN_CHISLO || x > MAX_CHISLO) {
            cout << "  ! Chislo vne [-30;30], poprobui eshe.\n";
            continue;                    // i не растёт, спросим снова
        }
        // Проверка: уникальность?
        if (m.estLi(x)) { //идем по списку chisla
            cout << "  ! Takoe uje est, povtory nelzya.\n";
            continue;                    // тоже не считаем
        }

        m.dobavit(x);
        i++;                             // только теперь +1
    }

    m.sortirovat();
    m.sozdano = true;
    cout << "Gotovo.\n";
}


// ============================================================
// СПОСОБ 3: ЗАДАТЬ ПО УСЛОВИЯМ
//программа сама перебирает весь универсум и берёт числа, которые подходят хотя бы под одно правило
//пользователь сам выбирает правила
// ============================================================
void zadatPoUsloviyam(Mnojestvo& m) {
    m.ochistit(); //очищает множество перед заполнением
    //пользователь должен ввести номер условия, можно несколько (последовательно)
    cout << "Vyberi usloviya (mojno neskolko, 0 - zakonchit):\n";
    cout << " 1) polojitelnye\n";
    cout << " 2) otricatelnye\n";
    cout << " 3) chetnye\n";
    cout << " 4) nechetnye\n";
    cout << " 5) kratnye chislu\n";
    cout << " 6) diapazon\n";
    cout << " 0) zakonchit\n";

    // Флаги: vybrano[1] = true значит "выбрано условие 1"
    bool vybrano[7];
    for (int i = 0; i < 7; i++) vybrano[i] = false; //сначала ничего не выбрано

    int kratnost = 1;
    int lo = MIN_CHISLO, hi = MAX_CHISLO;

    while (true) {
        int vybor = vvod();              // БЕЗОПАСНЫЙ ввод
        if (vybor == 0) break;           // выход
        if (vybor < 1 || vybor > 6) {    //неправильно ввели-идем в начало
            cout << "Net takogo punkta.\n";
            continue;
        }
        vybrano[vybor] = true;  //ставим флаг этого условия в true

        if (vybor == 5) {   //кратность
            cout << "Kratnost kakomu chislu? "; //спрашиваем чему кратно
            kratnost = vvod(); //сохраняем ответ в kratnost
            if (kratnost == 0) kratnost = 1;  // защита от деления на 0
        }
        if (vybor == 6) {   //диапазон, спрашиваем границы
            cout << "ot: "; lo = vvod();
            cout << "do: "; hi = vvod();
        }
    }
    //цикл с условиями крутится, пока не выбрали 0
    // Перебираем весь универсум
    for (int x = MIN_CHISLO; x <= MAX_CHISLO; x++) {//перебираем весь универсум
        bool podhodit = false; //для каждого сначала говорим "не подходит"

        if (vybrano[1] && x > 0) podhodit = true;   //усдовие 1 выбрано и число положит->подходит
        if (vybrano[2] && x < 0) podhodit = true;   //условие 2 выбрано и число отриц->подходит
        if (vybrano[3] && x % 2 == 0) podhodit = true;  //%-остаток от деление, если чётное-подходит
        if (vybrano[4] && x % 2 != 0) podhodit = true;
        if (vybrano[5] && x % kratnost == 0) podhodit = true;
        if (vybrano[6] && x >= lo && x <= hi) podhodit = true;
        //если число подходит по нескольким условиям, оно будет добавлено один раз
        //если хотя бы один true-добавится
        //dobavit не даст дубль (поэтому не используем else if)
        if (podhodit) m.dobavit(x); //добавляем если подошло
    }

    m.sortirovat();
    m.sozdano = true;
    cout << "Gotovo.\n";
}


// ============================================================
// ГЛАВНАЯ ФУНКЦИЯ
// ============================================================
int main() {
    setlocale(LC_ALL, "Russian");   // русский в консоли
    srand((unsigned)time(0));       //заводим случайные числа
                                //rand берет стартовое число(одинак всегда), прогоняет через формулу-получает первое случайное число
                                //потом берет это первое-получает второе и тд
                                //формула(примерная):следующее_число = (предыдущее_число * 1103515245 + 12345) % 2147483648
                                //srand(N) — устанавливает зерно = N, чтобы передаавть разное N(последовательность будет разной)
                                //наше N-это текущее время (кол-во сек)
    // Создаём три множества
    const int KOLVO_MNOJESTV = 3; //создаем неизменяемую переменную со значением 3
    Mnojestvo mnojestva[KOLVO_MNOJESTV]; //создаем массив из 3 элементов типа Mnojestvo
    mnojestva[0].imya = "A";
    mnojestva[1].imya = "B";
    mnojestva[2].imya = "C";

    // Главный цикл программы
    while (true) {
        cout << "\n===== KALKULYATOR MNOJESTV =====\n";
        cout << "1. Zadat mnojestvo\n";
        cout << "2. Pokazat vse mnojestva\n";
        cout << "3. Edinichnye operacii\n";
        cout << "0. Vyhod\n";
        cout << "Vybor: ";

        int deistvie = vvod();       // БЕЗОПАСНЫЙ ввод
        if (deistvie == 0) break;

        // ---------- ПУНКТ 1: ЗАДАТЬ МНОЖЕСТВО ----------
        if (deistvie == 1) {
            cout << "Kakoe mnojestvo zadat?\n";
            for (int i = 0; i < KOLVO_MNOJESTV; i++) {
                cout << " " << (i + 1) << ") " << mnojestva[i].imya;
                if (mnojestva[i].sozdano) cout << " (uje zadano)";
                cout << "\n";
            }
            int nomer = vvod();
            if (nomer < 1 || nomer > KOLVO_MNOJESTV) { //если ввели неправильно-идем в начало
                cout << "Neverno.\n";
                continue;
            }

            cout << "Sposob:\n 1) sluchaino\n 2) vruchnuyu\n 3) po usloviyam\n";
            int sposob = vvod();

            if (sposob == 1) zadatSluchaino(mnojestva[nomer - 1]);
            else if (sposob == 2) zadatRuchno(mnojestva[nomer - 1]);
            else if (sposob == 3) zadatPoUsloviyam(mnojestva[nomer - 1]);
            else cout << "Neverno.\n";
        }

        // ---------- ПУНКТ 2: ПОКАЗАТЬ ----------
        else if (deistvie == 2) {
            for (int i = 0; i < KOLVO_MNOJESTV; i++) {
                if (mnojestva[i].sozdano) pokazat(mnojestva[i]); //если задано вызываем pokazat
                else cout << mnojestva[i].imya << " = (ne zadano)\n";
            }
        }

        // ---------- ПУНКТ 3: ОПЕРАЦИИ ----------
        else if (deistvie == 3) {
            cout << "Operaciya:\n";
            cout << " 1) Objedinenie (A U B)\n";
            cout << " 2) Peresechenie (A ^ B)\n";
            cout << " 3) Raznost (A \\ B)\n";
            cout << " 4) Dopolnenie (~A)\n";
            int operaciya = vvod();

            // --- ДОПОЛНЕНИЕ: одно множество ---
            if (operaciya == 4) {
                cout << "Vyberi mnojestvo:\n";
                for (int i = 0; i < KOLVO_MNOJESTV; i++) {
                    if (mnojestva[i].sozdano)
                        cout << " " << (i + 1) << ") " << mnojestva[i].imya << "\n";
                }
                int n1 = vvod();
                if (n1 < 1 || n1 > KOLVO_MNOJESTV || !mnojestva[n1 - 1].sozdano) {
                    cout << "Neverno.\n";
                    continue;
                }
                Mnojestvo rez = dopolnenie(mnojestva[n1 - 1]);
                pokazat(rez);
            }

            // --- ОПЕРАЦИИ С ДВУМЯ МНОЖЕСТВАМИ ---
            else if (operaciya >= 1 && operaciya <= 3) {
                cout << "Vyberi pervoe mnojestvo:\n";
                for (int i = 0; i < KOLVO_MNOJESTV; i++) {
                    if (mnojestva[i].sozdano)//показываем только созданные множества
                        cout << " " << (i + 1) << ") " << mnojestva[i].imya << "\n";
                }
                int n1 = vvod();

                cout << "Vyberi vtoroe mnojestvo:\n";
                for (int i = 0; i < KOLVO_MNOJESTV; i++) {
                    if (mnojestva[i].sozdano)
                        cout << " " << (i + 1) << ") " << mnojestva[i].imya << "\n";
                }
                int n2 = vvod();

                if (n1 < 1 || n1 > KOLVO_MNOJESTV || !mnojestva[n1 - 1].sozdano ||
                    n2 < 1 || n2 > KOLVO_MNOJESTV || !mnojestva[n2 - 1].sozdano) {
                    cout << "Neverno.\n";//проверяем, что числа ввели корректно и множества созданы
                    continue;
                }

                Mnojestvo rez; //вызываем нужную функцию, она возвращает НОВОЕ множество, кладем его в переменную rez
                if (operaciya == 1) rez = objedinenie(mnojestva[n1 - 1], mnojestva[n2 - 1]);
                if (operaciya == 2) rez = peresechenie(mnojestva[n1 - 1], mnojestva[n2 - 1]);
                if (operaciya == 3) rez = raznost(mnojestva[n1 - 1], mnojestva[n2 - 1]);
                pokazat(rez);   //печатаем (исходные множества НЕ МЕНЯЮТСЯ, функции работают с копиями)
            }
            else cout << "Neverno.\n";
        }
    }
    //после любой команды программа доходит до конца тела while и цикл крутится снова
    //печатает меню, ждет ввода, так до тех пор, пока не введешь 0
    return 0;  // успешное завершение программы
}