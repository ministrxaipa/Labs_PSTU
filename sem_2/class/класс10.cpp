#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Pair {
private:
    int a;      
    double b;   

public:
    Pair(){
        a = 0;
        b = 0;
    }
    Pair(int x, double y){
        a = x;
        b = y;
    }
    Pair(const Pair& p){
        a = p.a;
        b = p.b;
    }
    ~Pair() {}
    int getA(){ 
        return a; 
    }
    double getB(){
         return b; 
        }
    void setA(int x){
         a = x; 
        }
    void setB(double y){ 
        b = y; 
    }
    //вычитание
    Pair operator-(const Pair& p){
        Pair res;
        res.a = a - p.a;
        res.b = b - p.b;
        return res;
    }
    //добавление
    Pair operator+(int x){
        Pair res;
        res.a = a + x;
        res.b = b;
        return res;
    }
    Pair operator+(double y){
        Pair res;
        res.a = a;
        res.b = b + y;
        return res;
    }
    //меньше(для удаления)
    bool operator<(const Pair& p) {
        return a < p.a;
    }
    //равно(для поиска)
    bool operator==(const Pair& p) {
        return a == p.a;
    }
    //перегрузка ввода
    friend istream& operator>>(istream&k,Pair&p){
        cout<<"введите число:";
        k>>p.a;
        cout<<"введите дробное число:";
        k>>p.b;
        return k;
    }
    //перегрузка вывода 
    friend ostream& operator<<(ostream&l, const Pair&p){
        l<<p.a<<":"<<p.b;
        return l;
    }

    //запись в файл
    void zapis(ofstream&file){
        file.write((char*)&a,sizeof(a));
        file.write((char*)&b,sizeof(b));
    }
    //чтение
    void chtenie(ifstream&file){
        file.read((char*)&a,sizeof(a));
        file.read((char*)&b,sizeof(b));
    }
};

void sozdatf(){
    ofstream f("10.dat",ios::binary);
    if(!f){
        cout<<"ошибка"<<endl;
        return;
    }
    int n;
    cout<<"сколько добавить пар?";
    cin>>n;
    for(int i=0;i<n;i++){
        Pair p;
        cin>>p;
        p.zapis(f);
    }
    f.close();
}

void prosmotrf(){
    ifstream fail("10.dat",ios::binary);
    if(!fail){
        cout<<"ошибка"<<endl;
        return;
    }
    int k=1;
    while(true){
        Pair p;
        p.chtenie(fail);
        if(fail.eof()){
            break;
        }
        cout<<k<<". "<<p<<endl;
        k++;
    }
    fail.close();
}

void udalit(){
    ifstream fail("10.dat",ios::binary);
    if(!fail){
        cout<<"ошибка"<<endl;
        return;
    }
    const int max=100;
    Pair arr[max];
    int size=0;
    while(true){
        Pair p;
        p.chtenie(fail);
        if (fail.eof()) break;
        arr[size] = p;
        size++;
    }
    fail.close();
    cout<<"введите сравнение:";
    int srav;
    cin>>srav;
    Pair porog(srav,0);
    int newsize=0;
    for(int i=0;i<size;i++){
        if(!(arr[i]<porog)){
            arr[newsize]=arr[i];
            newsize++;
        }
    }
    ofstream f("10.dat",ios::binary);
    for(int i=0;i<newsize;i++){
        arr[i].zapis(f);
    }
    f.close();
    cout<<size-newsize<<" удалено записей"<<endl;
}

//увеличить все записи с заданным знчаением на l
void uvelichit(){
    ifstream fail("10.dat",ios::binary);
    if(!fail){
        cout<<"ошибка"<<endl;
        return;
    }
    const int max=100;
    Pair arr[max];
    int size=0;
    while(true){
        Pair p;
        p.chtenie(fail);
        if (fail.eof()) break;
        arr[size] = p;
        size++;
    }
    fail.close();
    cout<<"введите число поиск:";
    int s;
    cin>>s;
    Pair iskomoe(s,0);
    cout<<"введите l";
    int l;
    cin>>l;
    int kolvo=0;
    for(int i=0;i<size;i++){
        if(arr[i]==iskomoe){
            arr[i]=arr[i]+l;
            kolvo++;
        }
    }
    ofstream f("10.dat",ios::binary);
    for(int i=0;i<size;i++){
        arr[i].zapis(f);
    }
    f.close();
    cout<<kolvo<<" записей изменено"<<endl;
}

//добавить k записей после номера
void dobavitn(){
    ifstream fail("10.dat",ios::binary);
    if(!fail){
        cout<<"ошибка"<<endl;
        return;
    }
    const int max=100;
    Pair arr[max];
    int size=0;
    while(true){
        Pair p;
        p.chtenie(fail);
        if (fail.eof()) break;
        arr[size] = p;
        size++;
    }
    fail.close();
    if(size==0){
        cout<<"файл пуст"<<endl;
        return;
    }
    cout<<"введите номер элемента";
    int n;
    cin>>n;
    n--;
    if(n<0 ||n>=size){
        cout<<"неверно"<<endl;
        return;
    }
    cout<<"сколько записей добавить?";
    int k;
    cin>>k;
    for(int i=size-1;i>n;i--){
        arr[i+k]=arr[i];
    }
    size=size+k;
    for(int i=0;i<k;i++){
        cout<<"ввод новой пары"<<endl;
        Pair p;
        cin>>p;
        arr[n+1+i]=p;
    }
    ofstream f("10.dat",ios::binary);
    for(int i=0;i<size;i++){
        arr[i].zapis(f);
    }
    f.close();
    cout<<k<<" записей добавлено"<<endl;
}

//изменение по номеру
void izmenit(){
    ifstream fail("10.dat",ios::binary);
    if(!fail){
        cout<<"ошибка"<<endl;
        return;
    }
    const int max=100;
    Pair arr[max];
    int size=0;
    while(true){
        Pair p;
        p.chtenie(fail);
        if (fail.eof()) break;
        arr[size] = p;
        size++;
    }
    fail.close();
    if(size==0){
        cout<<"файл пуст"<<endl;
        return;
    }
    cout<<"введите номер элемента";
    int n;
    cin>>n;
    n--;
    if(n<0 ||n>=size){
        cout<<"неверно"<<endl;
        return;
    }
    cout<<"текущий элемент"<<arr[n]<<endl;
    cout<<"введите новый"<<endl;
    Pair p;
    cin>>p;
    arr[n]=p;
    ofstream f("10.dat",ios::binary);
    for(int i=0;i<size;i++){
        arr[i].zapis(f);
    }
    f.close();
    cout<<"элемент изменен"<<endl;
}

int main(){
    setlocale(LC_ALL,"Russian");
    int c=-1;
    while(c!=0){
        cout<<"1.создать файл и добавить записи"<<endl;
        cout<<"2.просмотреть все записи"<<endl;
        cout<<"3.удалить записи меньше заданного"<<endl;
        cout<<"4.увеличить записи с заданным значением на l"<<endl;
        cout<<"5.добавить k записей после элемента"<<endl;
        cout<<"6.изменить запись по номеру"<<endl;
        cout<<"0.выход"<<endl;
        cin>>c;
        if(c==1){
            sozdatf();
        }
        else if(c==2){
            prosmotrf();
        }
        else if(c==3){
            udalit();
        }
        else if(c==4){
            uvelichit();
        }
        else if(c==5){
            dobavitn();
        }
        else if(c==6){
            izmenit();
        }
        else if(c==0){
            cout<<"пока пока"<<endl;
        }
        else{
            cout<<"неверный номер"<<endl;
        }
    }
    return 0;
}