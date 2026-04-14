#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");  
    
    //создание f1
    ofstream f1("f1.txt");
    if (!f1) {
        cout << "ошибка: не создается f1" << endl;
        return 1;
    }
    string stroka[10];
    
    for (int i = 0; i < 10; i++) {
        cout << "строка " << i + 1 << ": ";
        getline(cin, stroka[i]);
        f1 << stroka[i] << endl;
    }
    f1.close();
    
    //проверка f1
    ifstream check("f1.txt");
    if(!check){
        cout<<"ошибка"<<endl;
        return 1;
    }
    string s;
    int num = 1;
    while (getline(check, s)) {
        cout << num << ") " << s << endl;
        num++;
    }
    check.close();
    
    //копируем в f2
    int n1, n2;
    cout << "введите n1: ";
    cin >> n1;
    cout << "введите n2: ";
    cin >> n2;
    cin.ignore();
    
    ifstream chtenie("f1.txt");
    ofstream f2("f2.txt");
    if (!f2) {
        cout << "ошибка: не создается f2" << endl;
        return 1;
    }
    
    string temp;
    int nomer = 1;
    int scop=0;
    while (getline(chtenie, temp)) {
        if (nomer >= n1 && nomer <= n2) {
            if (temp.length() > 0) {
                char posled=temp[temp.length()-1];
                if(posled=='А' || posled=='а'){
                    f2<<temp<<endl;
                    scop++;
                    cout<<"скопирована строка "<<nomer<<": "<<temp<<endl;
                } 
            }
        }
        nomer++;
    }
    chtenie.close();
    f2.close();
    cout<<"всего скопировано: "<<scop<<endl;

    //проверка f2
    ifstream chtenief2("f2.txt");
    if (!chtenief2) {
        cout << "файл пуст или не существует" << endl;
    }
    else {
        string strokaF2;
        int num2 = 1;
        while (getline(chtenief2, strokaF2)) {
            cout << num2 << ") " << strokaF2 << endl;
            num2++;
        }
        if (num2==1){
            cout<<"файл пуст"<<endl;
        }
    }
    chtenief2.close();
    
    //поикс строки с большим а
    ifstream analiz("f2.txt");
    if(!analiz){
        cout<<"файл не существует или пуст"<<endl;
        return 0;
    }
    string strokaf2;
    int numstrok=1;
    int maxA=0;
    int nomermax=0;
    int schet;
    while(getline(analiz,strokaf2)){
        schet=0;
        for(int i=0;i<strokaf2.length();i++){
            if(strokaf2[i]=='А'){
                schet++;
            }
        }
        if (schet>maxA){
            maxA=schet;
            nomermax=numstrok;
        }
        numstrok++;
    }
    analiz.close();

    //вывод результата
    if(nomermax>0 && maxA>0){
        cout<<"строка с наибольшим кол-вом букв 'А': "<<nomermax<<endl;
        cout<<"количество букв 'А' в ней: "<<maxA<<endl;
    }
    else if (nomermax>0 && maxA==0){
        cout<<"в файле f2 есть строки, но нет буквы 'А'"<<endl;
    }
    else{
        cout<<"файл пуст"<<endl;
    }

    return 0;
}