#include <iostream>
using namespace std;

class Pair{
private:
    int a;
    double b;
public:
    //конструктор без прараметров
    Pair(){
        a=0;
        b=0;
    }
    //конструкто с параметрами
    Pair(int x, double y){
        a=x;
        b=y;
    }
    //конструктор копирования
    Pair(const Pair &p){
        a=p.a;
        b=p.b;
    }
    //деструтор
    ~Pair(){
        cout<<"деструктор для "<<a<<" :"<<b<<endl;
    }
    //селекторы
    int getA(){
        return a;
    }
    double getB(){
        return b;
    }
    //модификаторы
    void setA(int x){
        a=x;
    }
    void setB(double y){
        b=y;
    }
    //присваивание
    void operator=(const Pair &p){
        a=p.a;
        b=p.b;
    }
    //перегрузка вычитания
    Pair operator-(const Pair &p){
        Pair rez;
        rez.a=a-p.a;
        rez.b=b-p.b;
        return rez;
    }
    //перегрузка сложения
    Pair operator+(int x){
        Pair rez;
        rez.a=a+x;
        rez.b=b;
        return rez;
    }
    Pair operator+(double y){
        Pair rez;
        rez.a=a;
        rez.b=b+y;
        return rez;
    }
    //перегрузка ввода
    friend istream& operator>>(istream& k, Pair& p){
        cout<<"введите целое число:";
        k>>p.a;
        cout<<"введите дробное число:";
        k>>p.b;
        return k;
    }
    //перегрузка вывода
    friend ostream& operator<<(ostream& l, const Pair& p){
        l<<p.a<<" :"<<p.b;
        return l;
    }
};

int main(){
    setlocale(LC_ALL, "Russian");

    Pair p1;
    cout<<"p1=" <<p1<<endl;

    Pair p2(5, 3.5);
    cout<<"p2= "<<p2<<endl;

    Pair p3=p2;
    cout<<"p3= "<<p3<<endl;

    cout<<"p2.a= "<<p2.getA()<<endl;
    cout<<"p2.b= "<<p2.getB()<<endl;

    p1.setA(10);
    p1.setB(2.5);
    cout<<"p1 после set= "<<p1<<endl;

    Pair p4;
    p4=p2;
    cout<<"p4= "<<p4<<endl;

    cout<<"p2= "<<p2<<endl;
    cout<<"p1= "<<p1<<endl;
    Pair p5=p2-p1;
    cout<<"p2-p1= "<<p5<<endl;

    cout<<"p2= "<<p2<<endl;
    Pair p6=p2+3;
    cout<<"p2+3= "<<p6<<endl;
    Pair p7=p2+5.2;
    cout<<"p2+5.2= "<<p7<<endl;

    Pair p8;
    cin>>p8;
    cout<<"ввели: "<<p8<<endl;
    return 0;
}