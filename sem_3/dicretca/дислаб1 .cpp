// ============================================================
// ПОДКЛЮЧАЕМ БАЗОВЫЕ БИБЛИОТЕКИ
// Это НЕ библиотеки про множества, а основа C++
// ============================================================
#include <windows.h>
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
        cout << "Нужно число, попробуй ещё: ";  // попросить снова
    }
    return x;  // вернуть корректное число
}

// ============================================================
// БЕЗОПАСНЫЙ ВВОД СТРОКИ (для формул)
// Читает строку целиком, включая пробелы
// ============================================================
string vvodStroki() {
    string s;
    cin.ignore(10000, '\n');  // выкинуть остаток предыдущей строки из буфера
    getline(cin, s);          // прочитать всю строку до Enter
    return s;
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
    Mnojestvo() {imya = "";sozdano = false;}
    // --- КОНСТРУКТОР с именем ---
    // Вызывается при Mnojestvo m("A"); то же самое, но имя сразу задается
    Mnojestvo(string s) {imya = s;sozdano = false;}
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

//---СИММЕТРИЧЕСКАЯ РАЗНОСТЬ (A+B)---
//Всё, что есть только в одном из множеств (не в обоих сразу)
Mnojestvo simmetrichRaznost(Mnojestvo A, Mnojestvo B){
    Mnojestvo rezultat;
    rezultat.imya=A.imya+"+"+B.imya;
    for(int i=0;i<(int)A.chisla.size();i++){
        if(!B.estLi(A.chisla[i]))rezultat.dobavit(A.chisla[i]);
    }
    for(int i=0;i<(int)B.chisla.size();i++){
        if(!A.estLi(B.chisla[i]))rezultat.dobavit(B.chisla[i]);
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
    cout << "Сколько элементов? ";
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
    cout << "Готово\n";
}


// ============================================================
// СПОСОБ 2: ЗАДАТЬ ВРУЧНУЮ
// ============================================================
void zadatRuchno(Mnojestvo& m) { //ссылка, иначе не было бы изменений (множество пустое)
    cout << "Сколько элементов? ";
    int kolvo = vvod();                 // БЕЗОПАСНЫЙ ввод 
    if (kolvo < 0) kolvo = 0;           //отриц убираем

    m.ochistit();       //стираем то, что было (если множество было заполнено)

    int i = 0;      //счётчик успешно добавленных чисел
    while (i < kolvo) { //пока их меньше нужного-крутимся
        cout << "Элемент " << (i + 1) << ": "; //спрашиваем очередное число
        int x = vvod();                 // БЕЗОПАСНЫЙ ввод

        // Проверка: число внутри универсума?
        if (x < MIN_CHISLO || x > MAX_CHISLO) {
            cout << "Число вне [-30;30], попробуй ещё.\n";
            continue;                    // i не растёт, спросим снова
        }
        // Проверка: уникальность?
        if (m.estLi(x)) { //идем по списку chisla
            cout << "Такое уже есть, повторы нельзя\n";
            continue;                    // тоже не считаем
        }

        m.dobavit(x);
        i++;                             // только теперь +1
    }

    m.sortirovat();
    m.sozdano = true;
    cout << "Готово\n";
}


// ============================================================
// СПОСОБ 3: ЗАДАТЬ ПО УСЛОВИЯМ
//программа сама перебирает весь универсум и берёт числа, которые подходят хотя бы под одно правило
//пользователь сам выбирает правила
// ============================================================
void zadatPoUsloviyam(Mnojestvo& m) {
    m.ochistit(); //очищает множество перед заполнением
    //пользователь должен ввести номер условия, можно несколько (последовательно)
    cout << "Выбери условия (можно несколько, 0-закончить):\n";
    cout << " 1)положительные\n";
    cout << " 2)отрицательные\n";
    cout << " 3)чётные\n";
    cout << " 4)нечётные\n";
    cout << " 5)кратные числу\n";
    cout << " 6)диапазон\n";
    cout << " 0)закончить\n";
    // Флаги: vybrano[1] = true значит "выбрано условие 1"
    bool vybrano[7];
    for (int i = 0; i < 7; i++) vybrano[i] = false; //сначала ничего не выбрано
    int kratnost = 1;
    int lo = MIN_CHISLO, hi = MAX_CHISLO;
    while (true) {
        int vybor = vvod();              // БЕЗОПАСНЫЙ ввод
        if (vybor == 0) break;           // выход
        if (vybor < 1 || vybor > 6) {    //неправильно ввели-идем в начало
            cout << "Нет такого пункта\n";
            continue;
        }
        vybrano[vybor] = true;  //ставим флаг этого условия в true

        if (vybor == 5) {   //кратность
            cout << "Кратность какому числу? "; //спрашиваем чему кратно
            kratnost = vvod(); //сохраняем ответ в kratnost
            if (kratnost == 0) kratnost = 1;  // защита от деления на 0
        }
        if (vybor == 6) {   //диапазон, спрашиваем границы
            cout << "от: "; lo = vvod();
            cout << "до: "; hi = vvod();
        }
    }
    //цикл с условиями крутится, пока не выбрали 0
    // Перебираем весь универсум
    for (int x = MIN_CHISLO; x <= MAX_CHISLO; x++) {//перебираем весь универсум
        bool podhodit = true; //для каждого сначала говорим "не подходит"
        //если условие выбрано и число ему НЕ соответсвует->не подходит
        if (vybrano[1] && !(x > 0)) podhodit = false;   //усдовие 1 выбрано и число положит->подходит
        if (vybrano[2] && !(x < 0)) podhodit = false;   //условие 2 выбрано и число отриц->подходит
        if (vybrano[3] && !(x % 2 == 0)) podhodit = false;  //%-остаток от деление, если чётное-подходит
        if (vybrano[4] && !(x % 2 != 0)) podhodit = false;
        if (vybrano[5] && !(x % kratnost == 0)) podhodit = false;
        if (vybrano[6] && !(x >= lo && x <= hi)) podhodit = false;
        //если число подходит по нескольким условиям, оно будет добавлено один раз
        //если хотя бы один true-добавится
        //dobavit не даст дубль (поэтому не используем else if)
        if (podhodit) m.dobavit(x); //добавляем если подошло
    }
    m.sortirovat();
    m.sozdano = true;
    cout << "Готово\n";
}

//=============================================================
//Выбор множества по номеру
//Возвращает индекс (0...kolvo-1) или -1 если выбор плохой
//=============================================================
int vybratMnojestvo(Mnojestvo mnojestva[], int kolvo){
    for(int i=0;i<kolvo;i++){
        if(mnojestva[i].sozdano){
            cout<<""<<(i+1)<<")"<<mnojestva[i].imya<<"\n";
        }
    }
    int n=vvod();
    if(n<1||n>kolvo||!mnojestva[n-1].sozdano) return -1;
    return n-1;
}

// ============================================================
// РАЗБОР ФОРМУЛ
// Легенда символов:
//   U — объединение       ^ — пересечение
//   \ — разность          + — симметрическая разность
//   ~ — дополнение        ( ) — скобки (без вложенности)
//   Множества: A, B, C
// Формула не длиннее 3 множеств, скобки без вложенности.
// ============================================================

// --- Убрать все пробелы из строки ---
string uberiProbel(string s) {
    string rezultat = "";
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] != ' ' && s[i] != '\t') rezultat += s[i];
    }
    return rezultat;
}

// --- Сгенерировать имя-заглушку, которого нет среди текущих ---
// Используем буквы 'x','y','z','X','Y','Z','p','q','r' и т.д.
char svobodnoeImya(vector<Mnojestvo>& vse) {
    // Список кандидатов (не A/B/C, чтобы не перепутать)
    string kandidaty = "xyzXYZpqrstuvw";
    for (int k = 0; k < (int)kandidaty.size(); k++) {
        char c = kandidaty[k];
        bool zanyato = false;
        for (int i = 0; i < (int)vse.size(); i++) {
            if (vse[i].imya.size() == 1 && vse[i].imya[0] == c) { zanyato = true; break; }
        }
        if (!zanyato) return c;
    }
    return '?'; // на всякий случай
}

// --- Найти множество по имени в массиве ---
Mnojestvo* naitiPoImeni(vector<Mnojestvo>& vse, char imya) {
    for (int i = 0; i < (int)vse.size(); i++) {
        if (vse[i].imya.size() == 1 && vse[i].imya[0] == imya) return &vse[i];
    }
    return nullptr;
}

// --- Вычислить выражение БЕЗ скобок ---
// Сначала обрабатываем '~', потом '^', потом U, \, + слева направо
Mnojestvo vychislitBezSkobok(string s, Mnojestvo mnojestva[], int kolvo, bool& oshibka) {
    oshibka = false;
    Mnojestvo pustoe;

    // Копируем исходные множества в вектор (чтобы можно было дописывать промежуточные)
    vector<Mnojestvo> vse;
    for (int i = 0; i < kolvo; i++) vse.push_back(mnojestva[i]);

    // ----- ШАГ 1: обрабатываем все "~X" -----
    while (true) {
        int pos = -1;
        for (int i = 0; i < (int)s.size(); i++) if (s[i] == '~') { pos = i; break; }
        if (pos == -1) break;

        if (pos + 1 >= (int)s.size()) { oshibka = true; return pustoe; }
        char imya = s[pos + 1];
        Mnojestvo* istochnik = naitiPoImeni(vse, imya);
        if (istochnik == nullptr) { oshibka = true; return pustoe; }

        Mnojestvo dop = dopolnenie(*istochnik);
        char novoe = svobodnoeImya(vse);
        dop.imya = string(1, novoe);
        vse.push_back(dop);

        // Заменяем "~X" на новое имя
        string novaya = "";
        for (int i = 0; i < (int)s.size(); i++) {
            if (i == pos) { novaya += novoe; i++; }  // пропускаем ~ и букву
            else novaya += s[i];
        }
        s = novaya;
    }

    // ----- ШАГ 2: обрабатываем все "^" -----
    while (true) {
        int pos = -1;
        for (int i = 0; i < (int)s.size(); i++) if (s[i] == '^') { pos = i; break; }
        if (pos == -1) break;

        if (pos == 0 || pos + 1 >= (int)s.size()) { oshibka = true; return pustoe; }
        char imyaL = s[pos - 1];
        char imyaR = s[pos + 1];
        Mnojestvo* L = naitiPoImeni(vse, imyaL);
        Mnojestvo* R = naitiPoImeni(vse, imyaR);
        if (L == nullptr || R == nullptr) { oshibka = true; return pustoe; }

        Mnojestvo rez = peresechenie(*L, *R);
        char novoe = svobodnoeImya(vse);
        rez.imya = string(1, novoe);
        vse.push_back(rez);

        string novaya = "";
        for (int i = 0; i < (int)s.size(); i++) {
            if (i == pos - 1) { novaya += novoe; i += 2; }
            else novaya += s[i];
        }
        s = novaya;
    }

    // ----- ШАГ 3: обрабатываем U, \, + слева направо -----
    while (s.size() > 1) {
        int pos = -1;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == 'U' || s[i] == '\\' || s[i] == '+') { pos = i; break; }
        }
        if (pos == -1) { oshibka = true; return pustoe; }

        if (pos == 0 || pos + 1 >= (int)s.size()) { oshibka = true; return pustoe; }
        char oper = s[pos];
        char imyaL = s[pos - 1];
        char imyaR = s[pos + 1];
        Mnojestvo* L = naitiPoImeni(vse, imyaL);
        Mnojestvo* R = naitiPoImeni(vse, imyaR);
        if (L == nullptr || R == nullptr) { oshibka = true; return pustoe; }

        Mnojestvo rez;
        if (oper == 'U') rez = objedinenie(*L, *R);
        if (oper == '\\') rez = raznost(*L, *R);
        if (oper == '+') rez = simmetrichRaznost(*L, *R);

        char novoe = svobodnoeImya(vse);
        rez.imya = string(1, novoe);
        vse.push_back(rez);

        string novaya = "";
        for (int i = 0; i < (int)s.size(); i++) {
            if (i == pos - 1) { novaya += novoe; i += 2; }
            else novaya += s[i];
        }
        s = novaya;
    }

    // ----- В строке осталось одно имя — это результат -----
    if (s.size() != 1) { oshibka = true; return pustoe; }
    Mnojestvo* itog = naitiPoImeni(vse, s[0]);
    if (itog == nullptr) { oshibka = true; return pustoe; }
    return *itog;
}

// --- Найти первую пару внешних скобок ---
bool naitiSkobki(string s, int& open, int& close) {
    open = -1; close = -1;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') { open = i; break; }
    }
    if (open == -1) return false;
    for (int i = open + 1; i < (int)s.size(); i++) {
        if (s[i] == ')') { close = i; break; }
    }
    if (close == -1) return false;
    return true;
}

// --- ВЫЧИСЛИТЬ ФОРМУЛУ ЦЕЛИКОМ (со скобками) ---
Mnojestvo vychislitFormulu(string s, Mnojestvo mnojestva[], int kolvo, bool& oshibka) {
    oshibka = false;
    Mnojestvo pustoe;
    s = uberiProbel(s);
    if (s.empty()) { oshibka = true; return pustoe; }
    // Копируем исходные множества в рабочий вектор
    vector<Mnojestvo> rabochie;
    for (int i = 0; i < kolvo; i++) rabochie.push_back(mnojestva[i]);
    // Пошагово убираем скобки: считаем внутри, заменяем на имя-заглушку
    while (true) {
        int open, close;
        if (!naitiSkobki(s, open, close)) break;
        string vnutri = s.substr(open + 1, close - open - 1);
        // Считаем внутри (передаём rabochie как обычный массив)
        Mnojestvo* massiv = new Mnojestvo[rabochie.size()];
        for (int i = 0; i < (int)rabochie.size(); i++) massiv[i] = rabochie[i];
        bool oshibkaVnutri = false;
        Mnojestvo rez = vychislitBezSkobok(vnutri, massiv, (int)rabochie.size(), oshibkaVnutri);
        delete[] massiv;
        if (oshibkaVnutri) { oshibka = true; return pustoe; }
        char novoe = svobodnoeImya(rabochie);
        rez.imya = string(1, novoe);
        rabochie.push_back(rez);
        // Заменяем "( ... )" на имя
        string novaya = "";
        for (int i = 0; i < (int)s.size(); i++) {
            if (i == open) { novaya += novoe; i = close; }
            else novaya += s[i];
        }
        s = novaya;
    }
    // Считаем оставшееся
    Mnojestvo* massiv = new Mnojestvo[rabochie.size()];
    for (int i = 0; i < (int)rabochie.size(); i++) massiv[i] = rabochie[i];
    Mnojestvo rez = vychislitBezSkobok(s, massiv, (int)rabochie.size(), oshibka);
    delete[] massiv;
    return rez;
}

// --- Проверить, что в формуле только допустимые символы ---
bool proveritFormulu(string s) {
    s = uberiProbel(s);
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        bool ok = (c == 'A' || c == 'B' || c == 'C' ||
                   c == 'U' || c == '^' || c == '\\' || c == '+' ||
                   c == '~' || c == '(' || c == ')');
        if (!ok) return false;
    }
    return true;
}

// --- Показать легенду символов ---
void pokazatLegend() {
    cout << "\n===== ЛЕГЕНДА СИМВОЛОВ =====\n";
    cout << "Множества: A, B, C (только три)\n";
    cout << "Операции:\n";
    cout << "  U  - объединение           (A U B)\n";
    cout << "  ^  - пересечение          (A ^ B)\n";
    cout << "  \\  - разность               (A \\ B)\n";
    cout << "  +  - симметрическая разность   (A + B)\n";
    cout << "  ~  - дополнение            (~A ili ~(A U B))\n";
    cout << "Скобки - без вложений, например: ~(A U B)\n";
    cout << "Пробелы можно ставить где угодно (они игнорируются)\n";
    cout << "\nПримеры:\n";
    cout << "  A U B\n";
    cout << "  A ^ B U C\n";
    cout << "  ~A U B\n";
    cout << "  ~(A U B)\n";
    cout << "  (A + B) ^ C\n";
    cout << "============================\n\n";
}

// ============================================================
// ГЛАВНАЯ ФУНКЦИЯ
// ============================================================
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
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
        cout << "\n===== КАЛЬКУЛЯТОР МНОЖЕСТВ =====\n";
        cout << "1.Задать множество\n";
        cout << "2.Показать все множества\n";
        cout << "3.Единичные операции\n";
        cout << "4.Ввести формулу\n";
        cout << "0.Вывход\n";
        cout << "Выбор: ";

        int deistvie = vvod();       // БЕЗОПАСНЫЙ ввод
        if (deistvie == 0) break;

        // ---------- ПУНКТ 1: ЗАДАТЬ МНОЖЕСТВО ----------
        if (deistvie == 1) {
            cout << "Какое Множество задать?\n";
            for (int i = 0; i < KOLVO_MNOJESTV; i++) {
                cout << " " << (i + 1) << ") " << mnojestva[i].imya;
                if (mnojestva[i].sozdano) cout << " (уже задано)";
                cout << "\n";
            }
            int nomer = vvod();
            if (nomer < 1 || nomer > KOLVO_MNOJESTV) { //если ввели неправильно-идем в начало
                cout << "Неверно.\n";
                continue;
            }

            cout << "Способ:\n 1)случайно\n 2)вручную\n 3)по условию\n";
            int sposob = vvod();

            if (sposob == 1) zadatSluchaino(mnojestva[nomer - 1]);
            else if (sposob == 2) zadatRuchno(mnojestva[nomer - 1]);
            else if (sposob == 3) zadatPoUsloviyam(mnojestva[nomer - 1]);
            else cout << "Неверно.\n";
        }
        // ---------- ПУНКТ 2: ПОКАЗАТЬ ----------
        else if (deistvie == 2) {
            for (int i = 0; i < KOLVO_MNOJESTV; i++) {
                if (mnojestva[i].sozdano) pokazat(mnojestva[i]); //если задано вызываем pokazat
                else cout << mnojestva[i].imya << " = (не задано)\n";
            }
        }
        // ---------- ПУНКТ 3: ОПЕРАЦИИ ----------
        else if (deistvie == 3) {
            cout << "Операции:\n";
            cout << " 1)Объединение (A U B)\n";
            cout << " 2)Пересечение (A ^ B)\n";
            cout << " 3)Разность (A \\ B)\n";
            cout << " 4)Дополнение (~A)\n";
            cout << " 5)Симметрическая разность (A + B)\n";
            int operaciya = vvod();
            // --- ДОПОЛНЕНИЕ: одно множество ---
            if (operaciya == 4) {
                cout << "Выбери множество:\n";
                for (int i = 0; i < KOLVO_MNOJESTV; i++) {
                    if (mnojestva[i].sozdano)
                        cout << " " << (i + 1) << ") " << mnojestva[i].imya << "\n";
                }
                int n1 = vvod();
                if (n1 < 1 || n1 > KOLVO_MNOJESTV || !mnojestva[n1 - 1].sozdano) {
                    cout << "Неверно.\n";
                    continue;
                }
                Mnojestvo rez = dopolnenie(mnojestva[n1 - 1]);
                pokazat(rez);
            }
            // --- ОПЕРАЦИИ С ДВУМЯ МНОЖЕСТВАМИ ---
            else if (operaciya >= 1 && operaciya <= 5) {
                cout << "Выбери первое множество:\n";
                for (int i = 0; i < KOLVO_MNOJESTV; i++) {
                    if (mnojestva[i].sozdano)//показываем только созданные множества
                        cout << " " << (i + 1) << ") " << mnojestva[i].imya << "\n";
                }
                int n1 = vvod();

                cout << "Выбери второе множество:\n";
                for (int i = 0; i < KOLVO_MNOJESTV; i++) {
                    if (mnojestva[i].sozdano)
                        cout << " " << (i + 1) << ") " << mnojestva[i].imya << "\n";
                }
                int n2 = vvod();

                if (n1 < 1 || n1 > KOLVO_MNOJESTV || !mnojestva[n1 - 1].sozdano ||
                    n2 < 1 || n2 > KOLVO_MNOJESTV || !mnojestva[n2 - 1].sozdano) {
                    cout << "Неверно.\n";//проверяем, что числа ввели корректно и множества созданы
                    continue;
                }

                Mnojestvo rez; //вызываем нужную функцию, она возвращает НОВОЕ множество, кладем его в переменную rez
                if (operaciya == 1) rez = objedinenie(mnojestva[n1 - 1], mnojestva[n2 - 1]);
                if (operaciya == 2) rez = peresechenie(mnojestva[n1 - 1], mnojestva[n2 - 1]);
                if (operaciya == 3) rez = raznost(mnojestva[n1 - 1], mnojestva[n2 - 1]);
                if (operaciya == 5) rez = simmetrichRaznost(mnojestva[n1 - 1], mnojestva[n2 - 1]);
                pokazat(rez);   //печатаем (исходные множества НЕ МЕНЯЮТСЯ, функции работают с копиями)
            }
            else cout << "Неверно.\n";
        }
        // ---------- ПУНКТ 4: ФОРМУЛА ----------
        else if (deistvie == 4) {
            // Проверяем, что все три множества созданы
            bool vseGotovy = true;
            for (int i = 0; i < KOLVO_MNOJESTV; i++) {
                if (!mnojestva[i].sozdano) vseGotovy = false;
            }
            if (!vseGotovy) {
                cout << "Сначала задай все три множества (A, B, C)!\n";
                continue;
            }
            pokazatLegend();
            cout << "Введи формулу (например: A U B, ~A ^ C, (A + B) U C):\n";
            cout << "> ";

            string formula = vvodStroki();

            if (!proveritFormulu(formula)) {
                cout << "Ошибка: в формуле есть недопустимые символы\n";
                cout << "Допустимо: A B C U ^ \\ + ~ ( ) и пробелы\n";
                continue;
            }

            bool oshibka = false;
            Mnojestvo rez = vychislitFormulu(formula, mnojestva, KOLVO_MNOJESTV, oshibka);

            if (oshibka) {
                cout << "Ошибка при разборе формулы. Проверь написание.\n";
            } else {
                rez.imya = formula;   // для красоты покажем саму формулу как имя
                pokazat(rez);
            }
        }
    }
    //после любой команды программа доходит до конца тела while и цикл крутится снова
    //печатает меню, ждет ввода, так до тех пор, пока не введешь 0
    return 0;  // успешное завершение программы
}