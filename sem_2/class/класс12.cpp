#include <iostream>
#include <set>     //для multiset (задача 1 и 2)
#include <list>    //для list(задача 3)
#include <vector>  //для временного хранения
using namespace std;

//пользовательский класс Pair (для задачи 2)
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
    bool operator<(const Pair& p) const{ //задача 4
        return a < p.a;
    }
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
};

//ЗАДАЧА 1
void zadacha1(){
    //1.1-ассоциативный контейнер
    multiset<double> ms;
    //1.2-заполняем элементами
    int n;
    cout<<"сколько добавить?";
    cin>>n;
    for(int i=0;i<n;i++){
        double x;
        cin>>x;
        ms.insert(x);
    }
    //1.3-добавляем элемент
    double novie;
    cout<<"добавить элемент:";
    cin>>novie;
    ms.insert(novie);
    //1.4-удаляем
    double udalit;
    cout<<"какой удаляем?";
    cin>>udalit;
    ms.erase(udalit);
    //1.5-ЗАДАНИЕ 3- среднее арифметическое+ добавить
    if(ms.empty()==true){
        cout<<"контейнер пуст"<<endl;
        return;
    }
    double sum=0;
    int c=0;
    for(double x:ms){
        sum=sum+x;
        c++;
    }
    double sred=sum/c;
    cout<<"среднее арифметическое= "<<sred<<endl;
    ms.insert(sred);
    //1.6-вывод
    for(double x:ms){
        cout<<x<<" ";
    }
    cout<<endl;
}

//ЗАДАЧА 2- multiset<Pair>
void zadacha2(){
    //2.1-ассоциативный контейнер
    multiset<Pair> ms;
    //2.2-заполняем элементами
    int n;
    cout<<"сколько добавить?";
    cin>>n;
    for(int i=0;i<n;i++){
        Pair p;
        cin>>p;
        ms.insert(p);
    }
    //2.3-добавляем элемент
    Pair novie;
    cout<<"добавить элемент:";
    cin>>novie;
    ms.insert(novie);
    //2.4-удаляем (по ключу)
    int k;
    cout<<"какой удаляем?";
    cin>>k;
    Pair udalit(k,0);
    ms.erase(udalit);
    //2.5-ЗАДАНИЕ 4- удалить элемент из диапазона
    if(ms.empty()==true){
        cout<<"контейнер пуст"<<endl;
        return;
    }
    int mink, maxk;
    cout<<"введите нижнюю границу:";
    cin>>mink;
    cout<<"введите верхнюю границу:";
    cin>>maxk;
    vector<Pair> temp;  //сохраняем во временный вектор
    for(Pair p:ms){
        temp.push_back(p);
    }
    ms.clear();
    int udalen=0;
    for(int i=0;i<temp.size();i++){
        int k=temp[i].getA();
        if(k>=mink && k<=maxk){
            udalen++;
        }
        else{
            ms.insert(temp[i]);
        }
    }
    cout<<"удалено пар: "<<udalen<<endl;
    //1.6-вывод
    cout<<"оставшиеся: "<<endl;
    for(Pair p:ms){
        cout<<p<<" ";
    }
    cout<<endl;
}

//ЗАДАЧА 5- ПАРМЕТРИЗИРОВАННЫЙ КЛАСС=СПИСОК
template <class T>
class Mylist{
private:
    list<T> data;
public:
    //3.1+3.2
    void sozdat(){
        int n;
        cout<<"сколько добавить?";
        cin>>n;
        for(int i=0;i<n;i++){
            T x;
            cin>>x;
            //3.3-добавляем в конец
            data.push_back(x);
        }
    }
    //3.3-добавить в конец
    void dobavit(){
        T x;
        cin>>x;
        data.push_back(x);
    }
    //3.4-удаляем из начала
    void udalit(){
        if(data.empty()==false){     //если список не пуст
        cout<<"удален: "<<data.front()<<endl;
        data.pop_front();
        }
        else{
            cout<<"список пуст"<<endl;
        }
    }
    //3.5- ЗАДАНИЕ 5- к каждому элементу добавить сумму мин+макс
    void variant(){
        if(data.empty()==true){
            cout<<"список пуст"<<endl;
            return;
        }
        T minel=data.front();
        T maxel=data.front();
        for(T x:data){
            if(x<minel){
                minel=x;
            }
            if(x>maxel){
                maxel=x;
            }
        }
        T sum=maxel+minel;
        cout<<"max= "<<maxel<<endl;
        cout<<"min= "<<minel<<endl;
        cout<<"max+min= "<<sum<<endl;
        vector<T> temp;
        for(T x:data){
            temp.push_back(x+sum);
        }
        data.clear();
        for(int i=0;i<temp.size();i++){
            data.push_back(temp[i]);
        }
    }
    void pokazat(){
        cout<<"итог:"<<endl;
        for(T x:data){
            cout<<x<<" ";
        }
        cout<<endl;
    }
};

int main(){
    setlocale(LC_ALL,"Russian");
    int c=-1;
    Mylist<double> mylist;    //для задачи 3
    while(c!=0){
        cout<<"1.задача 1-задание 3"<<endl;
        cout<<"2.задача 2-задание 4"<<endl;
        cout<<"3.задача 3-задани 5"<<endl;
        cout<<"0.выход"<<endl;
        cin>>c;
        if(c==1){
            zadacha1();
        }
        else if(c==2){
            zadacha2();
        }
        else if(c==3){
            mylist.sozdat();
            mylist.dobavit();
            mylist.udalit();
            mylist.pokazat();
            mylist.variant();
            mylist.pokazat();
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