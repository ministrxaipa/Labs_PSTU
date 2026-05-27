#include <iostream>
#include <list>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <ctime>

using namespace std;

class Pair {
private:
    int first;
    int second;
    
public:
    Pair() : first(0), second(0) {}
    Pair(int f, int s) : first(f), second(s) {}
    
    int getFirst() const { return first; }
    int getSecond() const { return second; }
    
    void setFirst(int f) { first = f; }
    void setSecond(int s) { second = s; }
    
    bool operator<(const Pair& other) const {
        return first < other.first;
    }
    
    bool operator>(const Pair& other) const {
        return first > other.first;
    }
    
    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }
    
    Pair& operator=(const Pair& other) {
        if (this != &other) {
            first = other.first;
            second = other.second;
        }
        return *this;
    }
    
    friend ostream& operator<<(ostream& os, const Pair& p) {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }
};

void task1_List() {
    cout << "\n========== ЗАДАЧА 1: СПИСОК (list) ==========\n" << endl;
    
    list<Pair> myList;
    
    myList.push_back(Pair(10, 100));
    myList.push_back(Pair(25, 250));
    myList.push_back(Pair(30, 300));
    myList.push_back(Pair(15, 150));
    myList.push_back(Pair(40, 400));
    myList.push_back(Pair(20, 200));
    myList.push_back(Pair(35, 350));
    
    cout << "Исходный список: ";
    for (list<Pair>::iterator it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    replace_if(myList.begin(), myList.end(), 
               [](const Pair& p) { return p.getFirst() % 2 == 0; }, 
               Pair(0, 0));
    
    cout << "После замены четных first на (0,0): ";
    for (list<Pair>::iterator it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    myList.remove_if([](const Pair& p) { return p.getFirst() == 0; });
    
    cout << "После удаления (0,0): ";
    for (list<Pair>::iterator it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    myList.sort();
    cout << "Сортировка по возрастанию: ";
    for (list<Pair>::iterator it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    myList.sort(greater<Pair>());
    cout << "Сортировка по убыванию: ";
    for (list<Pair>::iterator it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    list<Pair>::iterator found = find_if(myList.begin(), myList.end(), 
                         [](const Pair& p) { return p.getFirst() == 25; });
    if (found != myList.end()) {
        cout << "Элемент с first=25 найден: " << *found << endl;
    } else {
        cout << "Элемент с first=25 не найден" << endl;
    }
    
    int count25 = count_if(myList.begin(), myList.end(), 
                           [](const Pair& p) { return p.getFirst() == 25; });
    cout << "Количество элементов с first=25: " << count25 << endl;
    
    int sumFirst = 0, sumSecond = 0, cnt = 0;
    for_each(myList.begin(), myList.end(), [&](const Pair& p) {
        sumFirst += p.getFirst();
        sumSecond += p.getSecond();
        cnt++;
    });
    
    if (cnt > 0) {
        Pair average(sumFirst / cnt, sumSecond / cnt);
        cout << "Среднее арифметическое: " << average << endl;
        myList.push_back(average);
    }
    
    cout << "Список после добавления среднего: ";
    for (list<Pair>::iterator it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void task2_PriorityQueue() {
    cout << "\n========== ЗАДАЧА 2: ОЧЕРЕДЬ С ПРИОРИТЕТАМИ ==========\n" << endl;
    
    priority_queue<Pair, vector<Pair>, less<Pair> > pq;
    
    pq.push(Pair(10, 100));
    pq.push(Pair(50, 500));
    pq.push(Pair(30, 300));
    pq.push(Pair(40, 400));
    pq.push(Pair(20, 200));
    
    vector<Pair> temp;
    while (!pq.empty()) {
        temp.push_back(pq.top());
        pq.pop();
    }
    
    cout << "Элементы из очереди: ";
    for (int i = 0; i < (int)temp.size(); i++) {
        cout << temp[i] << " ";
    }
    cout << endl;
    
    vector<Pair> replacedVec;
    replace_copy_if(temp.begin(), temp.end(), back_inserter(replacedVec),
                   [](const Pair& p) { return p.getFirst() > 30; }, Pair(999, 999));
    
    cout << "После замены (first>30 на 999,999): ";
    for (int i = 0; i < (int)replacedVec.size(); i++) {
        cout << replacedVec[i] << " ";
    }
    cout << endl;
    
    vector<Pair> removedVec;
    remove_copy_if(temp.begin(), temp.end(), back_inserter(removedVec),
                  [](const Pair& p) { return p.getFirst() < 30; });
    
    cout << "После удаления (first<30): ";
    for (int i = 0; i < (int)removedVec.size(); i++) {
        cout << removedVec[i] << " ";
    }
    cout << endl;
    
    sort(removedVec.begin(), removedVec.end());
    cout << "Сортировка по возрастанию: ";
    for (int i = 0; i < (int)removedVec.size(); i++) {
        cout << removedVec[i] << " ";
    }
    cout << endl;
    
    sort(removedVec.begin(), removedVec.end(), greater<Pair>());
    cout << "Сортировка по убыванию: ";
    for (int i = 0; i < (int)removedVec.size(); i++) {
        cout << removedVec[i] << " ";
    }
    cout << endl;
    
    vector<Pair>::iterator found = find_if(removedVec.begin(), removedVec.end(), 
                         [](const Pair& p) { return p.getFirst() == 40; });
    if (found != removedVec.end()) {
        cout << "Элемент с first=40 найден: " << *found << endl;
    } else {
        cout << "Элемент с first=40 не найден" << endl;
    }
    
    int minRange = 20, maxRange = 40;
    vector<Pair> finalVec;
    remove_copy_if(removedVec.begin(), removedVec.end(), back_inserter(finalVec),
                  [minRange, maxRange](const Pair& p) {
                      return p.getFirst() >= minRange && p.getFirst() <= maxRange;
                  });
    
    cout << "После удаления элементов с first в [" << minRange << "," << maxRange << "]: ";
    for (int i = 0; i < (int)finalVec.size(); i++) {
        cout << finalVec[i] << " ";
    }
    cout << endl;
}

void task3_Map() {
    cout << "\n========== ЗАДАЧА 3: СЛОВАРЬ (map) ==========\n" << endl;
    
    map<int, Pair> myMap;
    
    myMap[10] = Pair(10, 100);
    myMap[25] = Pair(25, 250);
    myMap[30] = Pair(30, 300);
    myMap[15] = Pair(15, 150);
    myMap[40] = Pair(40, 400);
    myMap[20] = Pair(20, 200);
    
    cout << "Исходный словарь:" << endl;
    for (map<int, Pair>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
        cout << "  Ключ: " << it->first << " -> Значение: " << it->second << endl;
    }
    
    vector<Pair> values;
    for (map<int, Pair>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
        values.push_back(it->second);
    }
    
    replace_if(values.begin(), values.end(),
              [](const Pair& p) { return p.getSecond() > 300; }, Pair(1, 1));
    
    cout << "\nПосле замены (second>300 на (1,1)): ";
    for (int i = 0; i < (int)values.size(); i++) {
        cout << values[i] << " ";
    }
    cout << endl;
    
    vector<Pair>::iterator newEnd = remove_if(values.begin(), values.end(),
                           [](const Pair& p) { return p.getFirst() < 20; });
    values.erase(newEnd, values.end());
    
    cout << "После удаления (first<20): ";
    for (int i = 0; i < (int)values.size(); i++) {
        cout << values[i] << " ";
    }
    cout << endl;
    
    sort(values.begin(), values.end());
    cout << "Сортировка по возрастанию: ";
    for (int i = 0; i < (int)values.size(); i++) {
        cout << values[i] << " ";
    }
    cout << endl;
    
    sort(values.begin(), values.end(), greater<Pair>());
    cout << "Сортировка по убыванию: ";
    for (int i = 0; i < (int)values.size(); i++) {
        cout << values[i] << " ";
    }
    cout << endl;
    
    vector<Pair>::iterator found = find_if(values.begin(), values.end(), 
                         [](const Pair& p) { return p.getFirst() == 30; });
    if (found != values.end()) {
        cout << "Элемент с first=30 найден: " << *found << endl;
    } else {
        cout << "Элемент с first=30 не найден" << endl;
    }
    
    int count30 = count_if(values.begin(), values.end(), 
                           [](const Pair& p) { return p.getFirst() == 30; });
    cout << "Количество элементов с first=30: " << count30 << endl;
    
    if (!values.empty()) {
        vector<Pair>::iterator minIt = min_element(values.begin(), values.end());
        vector<Pair>::iterator maxIt = max_element(values.begin(), values.end());
        
        int minFirst = minIt->getFirst();
        int maxFirst = maxIt->getFirst();
        int sumToAdd = minFirst + maxFirst;
        
        cout << "Минимальный first: " << minFirst << endl;
        cout << "Максимальный first: " << maxFirst << endl;
        cout << "Сумма для добавления: " << sumToAdd << endl;
        
        for_each(values.begin(), values.end(), [sumToAdd](Pair& p) {
            p.setFirst(p.getFirst() + sumToAdd);
            p.setSecond(p.getSecond() + sumToAdd);
        });
        
        cout << "После добавления суммы: ";
        for (int i = 0; i < (int)values.size(); i++) {
            cout << values[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "================================================" << endl;
    cout << "   ЛАБОРАТОРНАЯ РАБОТА: STL АЛГОРИТМЫ" << endl;
    cout << "   Вариант: Контейнеры list, priority_queue, map" << endl;
    cout << "================================================" << endl;
    
    task1_List();
    task2_PriorityQueue();
    task3_Map();
    
    cout << "\n================================================" << endl;
    cout << "   ВСЕ ЗАДАЧИ ВЫПОЛНЕНЫ" << endl;
    cout << "================================================" << endl;
    
    return 0;
}