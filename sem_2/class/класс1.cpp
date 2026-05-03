#include <iostream>
using namespace std;

struct Progressia{
    float a0;
    int r;

    //метод для заполнения данными
    void Init(float a, int b){
        if(b<=0){
            cout<<"r должен быть больше 0"<<endl;
            a0=0;
            r=1;
        }
        else{
            a0=a;
            r=b;
        }
    }

    //метод для ввода с клавиатуры
    void Read(){
        cout<<"введите a0: "<<endl;
        cin>>a0;
        cout<<"введите r: "<<endl;
        cin>>r;
        if(r<=0){
            cout<<"r должен быть больше 0"<<endl;
            r=1;
        }
    }

    //метод для вывода на экран
    void Show(){
        cout<<"a0= "<<a0<<", r= "<<r<<endl;
    }

    //метод для вычесления j
    float element(int j){
        float rez=a0;
        for(int i=0;i<j;i++){
            rez=rez*r;
        }
        return rez;
    }
};

Progressia make_Progressia(float a0, int r){
    Progressia p;
    p.a0=a0;
    p.r=r;
    return p;
}

int main() {
    setlocale(LC_ALL, "Russian");

    //способ 1: создаем объект
    Progressia prog1;
    prog1.Init(2.5, 3);
    prog1.Show();
    cout<<"какой элемент найти"<<endl;
    int j;
    cin>>j;
    cout<<j<<"-й элемент= "<<prog1.element(j)<<endl;
    cout<<endl;

    //способ 2: пользователь сам вводит данные
    Progressia prog2;
    prog2.Read();
    prog2.Show();
    cout<<"какой элемент найти"<<endl;
    cin>>j;
    cout<<j<<"-й элемент= "<<prog2.element(j)<<endl;
    cout<<endl;

    //способ 3: без Init
    Progressia prog3;
    prog3.a0=1.5;
    prog3.r=4;
    prog3.Show();
    cout<<"какой элемент найти"<<endl;
    cin>>j;
    cout<<j<<"-й элемент= "<<prog3.element(j)<<endl;
    cout<<endl;

    //массив объектов
    Progressia massiv[3];
    massiv[0].Init(3,5);
    massiv[1].Read();
    massiv[2].a0=0.5;
    massiv[2].r=4;
    cout<<"какой элемет найти для всех объектов массива"<<endl;
    cin>>j;
    for(int i=0;i<3;i++){
        massiv[i].Show();
        cout<<j<<"-й элемент= "<<massiv[i].element(j)<<endl;
    }
    return 0;
}