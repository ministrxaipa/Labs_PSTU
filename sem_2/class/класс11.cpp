#include <iostream>
#include <list>
#include <queue>
#include <vector>
using namespace std;

//пользовательский класс (для задач 2 и4)
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
    //1.1-пользовательский контейнер
    list<double> lst;
    //1.2-заполняем элементами стандартного типа(double)
    int n;
    cout<<"сколько добавить?";
    cin>>n;
    for(int i=0;i<n;i++){
        double x;
        cin>>x;
        //1.3-добавляем в конец
        lst.push_back(x);
    }
    //1.3-добавляем еще один в конец
    double novie;
    cout<<"добавить в конец";
    cin>>novie;
    lst.push_back(novie);
    //1.4-удаляем из начала
    if(lst.empty()==false){     //если список не пуст
        cout<<"удален: "<<lst.front()<<endl;
        lst.pop_front();
    }
    //1.5-среднее арифметическое и добавить в конец
    if(lst.empty()==true){
        cout<<"список пуст"<<endl;
        return;
    }
    double sum=0;
    int c=0;
    for(double x:lst){  //перебираем все элементы списка
        sum=sum+x;
        c++;
    }
    double sred=sum/c;
    cout<<"сумма: "<<sum<<endl;
    cout<<"кол-во+ "<<c<<endl;
    cout<<"среднее арифм= "<<sred<<endl;
    lst.push_back(sred);
    cout<<"список итог:"<<endl;
    for(double x:lst){
        cout<<x<<" ";
    }
    cout<<endl;
}

//ЗАДАЧА 2- ПОЛЬЗОВАТЕЛЬСКИЙ КОНТЕЙНЕР(СПИСОК)
void zadacha2(){
    //2.1-пользовательский контейнер
    list<Pair> lst;
    //2.2-заполняем элементами
    int n;
    cout<<"сколько добавить?";
    cin>>n;
    for(int i=0;i<n;i++){
        Pair p;
        cin>>p;
        //2.3-добавляем в конец
        lst.push_back(p);
    }
    //2.3-добавляем еще один в конец
    Pair novie;
    cout<<"добавить в конец";
    cin>>novie;
    lst.push_back(novie);
    //2.4-удаляем из начала
    if(lst.empty()==false){     //если список не пуст
        cout<<"удален: "<<lst.front()<<endl;
        lst.pop_front();
    }
    //2.5
    if(lst.empty()==true){
        cout<<"список пуст"<<endl;
        return;
    }
    int suma=0;
    int c=0;
    for(Pair p:lst){  //перебираем все элементы списка
        suma=suma+p.getA();
        c++;
    }
    double sred=suma/c;
    cout<<"сумма: "<<suma<<endl;
    cout<<"среднее арифм= "<<sred<<endl;
    Pair newpair(sred,0.0);
    lst.push_back(newpair);
    cout<<"новая пара "<<newpair<<endl;
    cout<<"итог:"<<endl;
    for(Pair p:lst){
        cout<<p<<" ";
    }
    cout<<endl;
}

//ЗАДАЧА 3- ПАРАМЕТРИЗИРОВАННЫЙ КЛАСС(СПИСОК)
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
    //3.5
    void variant(){
        if(data.empty()==true){
            cout<<"список пуст"<<endl;
            return;
        }
        T suma=0;
        int c=0;
        for(T p:data){  //перебираем все элементы списка
            suma=suma+p;
            c++;
        }
        T sred=suma/c;
        cout<<"среднее арифм= "<<sred<<endl;
        data.push_back(sred);
    }
    void pokazat(){
        cout<<"итог:"<<endl;
        for(T x:data){
            cout<<x<<" ";
        }
        cout<<endl;
    }
};

//ЗАДАЧА 4- АДАПТЕР КОНТЕЙНЕРА- ОЧЕРЕДЬ С ПРИОРИТЕТАМИ
void zadacha4(){
    //4.1-создание
    priority_queue<Pair> pq;
    //4.2-заполняем элементами
    int n;
    cout<<"сколько добавить?";
    cin>>n;
    for(int i=0;i<n;i++){
        Pair p;
        cin>>p;
        //4.3-добавляем в очередь
        pq.push(p);
    }
    //4.3-добавляем еще один 
    Pair novie;
    cin>>novie;
    pq.push(novie);
    //4.4-удаляем из начала
    if(pq.empty()==false){     //если список не пуст
        cout<<"удален: "<<pq.top()<<endl;
        pq.pop();
    }
    //4.5-удаляем с ключами
    int mink, maxk;
    cout<<"введите нижнюю границу";
    cin>>mink;
    cout<<"введите верхнюю границу";
    cin>>maxk;
    vector<Pair> temp; //очередь нельзя перебрать->сохраняем во временный вектрор
    while(pq.empty()==false){
        temp.push_back(pq.top());
        pq.pop();
    }
    //удаляем те, у котрых ключ (первое число)
    int udaleno=0;
    for(int i=0;i<temp.size();i++){
        int key=temp[i].getA();
        if(key>=mink &&key<=maxk){
            cout<<"удалено "<<temp[i]<<endl;
            udaleno++;
        }
        else{
            pq.push(temp[i]);
        }
    }
    cout<<"удалено пар: "<<udaleno<<endl;
    //вывод оставшихся
    vector<Pair> ost;
    while(pq.empty()==false){
        ost.push_back(pq.top());
        pq.pop();
    }
    for(int i=0;i<ost.size();i++){
        cout<<ost[i]<<" ";
    }
    cout<<endl;
}

//ЗАДАЧА 5- ПАРАМЕТРИЗИРОВАННЫЙ КЛАСС С АДАПТЕРОМ
template <class T>
class Mypriority{
private:
    priority_queue<T> data;
public:
    //5.1+5.2
    void sozdat(){
        int n;
        cout<<"сколько добавить?";
        cin>>n;
        for(int i=0;i<n;i++){
            T x;
            cin>>x;
            //5.3-добавляем 
            data.push(x);
        }
    }
    //5.3-добавить 
    void dobavit(){
        T x;
        cin>>x;
        data.push(x);
    }
    //5.4-удаляем из начала
    void udalit(){
        if(data.empty()==false){     //если список не пуст
        cout<<"удален: "<<data.top()<<endl;
        data.pop();
        }
        else{
            cout<<"очередь пуста"<<endl;
        }
    }
    //5.5- к каждому добавить сумму мин и макс
    void variant(){
        if(data.empty()==true){
            cout<<"очередб пуста"<<endl;
            return;
        }
        //сохраняем во временный вектор
        vector<T> temp;
        while(data.empty()==false){
            temp.push_back(data.top());
            data.pop();
        }
        T minel=temp[0];
        T maxel=temp[0];
        for(int i=0;i<temp.size();i++){
            if(temp[i]<minel){
                minel=temp[i];
            }
            if(temp[i]>maxel){
                maxel=temp[i];
            }
        }
        T sum=minel+maxel;
        cout<<"max= "<<maxel<<endl;
        cout<<"min= "<<minel<<endl;
        cout<<"max+min= "<<sum<<endl;
        for(int i=0;i<temp.size();i++){
            temp[i]=temp[i]+sum;
        }
        for(int i=0;i<temp.size();i++){
            data.push(temp[i]);
        }
    }
    void pokazat(){
        vector<T> temp;
        while(data.empty()==false){
            temp.push_back(data.top());
            data.pop();
        }
        for(int i=0;i<temp.size();i++){
            cout<<temp[i]<<" ";
        }
        cout<<endl;
        for(int i=0;i<temp.size();i++){
        data.push(temp[i]);
        }
    }
};

int main(){
    setlocale(LC_ALL,"Russian");
    int c=-1;
    Mylist<double> mylist;    //для задачи 3
    Mypriority<double> mypq;  //для задачи 5
    while(c!=0){
        cout<<"1.задача 1"<<endl;
        cout<<"2.задача 2"<<endl;
        cout<<"3.задача 3"<<endl;
        cout<<"4.задача 4"<<endl;
        cout<<"5.задача 5"<<endl;
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
        else if(c==4){
            zadacha4();
        }
        else if(c==5){
            mypq.sozdat();
            mypq.dobavit();
            mypq.udalit();
            mypq.pokazat();
            mypq.variant();
            mypq.pokazat();
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