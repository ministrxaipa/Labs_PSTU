#include <iostream>
#include <string>
using namespace std;

//базовый класс
class Person{
private:
    string name;
    int age;
public:
    Person(){
        name="не известно";
        age=0;
    }
    Person(string n, int a){
        name=n;
        age=a;
    }
    Person(const Person& p){
        name=p.name;
        age=p.age;
    }
    ~Person(){
        cout<<"деструктор для "<<name<<endl;
    }
    string getname(){
        return name;
    }
    int getage(){
        return age;
    }
    void setname(string n){
        name=n;
    }
    void setage(int a){
        age=a;
    }
    void operator=(const Person&p){
        cout<<"оператор= "<<endl;
        name=p.name;
        age=p.age;
    }
    friend istream& operator>>(istream&k, Person&p){
        cout<<"введите имя:";
        k>>p.name;
        cout<<"введите возраст:";
        k>>p.age;
        return k;
    }
    friend ostream& operator<<(ostream&l,const Person&p){
        l<<p.name<<" ("<<p.age<<" лет)";
        return l;
    }
};

//произвольный класс
class Student :public Person{
private:
    string predmet;
    int ocenka;
public:
    Student():Person(){
        predmet="не известно";
        ocenka=0;
    }
    Student(string n, int a, string p, int o):Person(n,a){
        predmet=p;
        ocenka=o;
    }
    Student(const Student&s):Person(s){
        predmet=s.predmet;
        ocenka=s.ocenka;
    }
    ~Student(){
        cout<<"Student: деструктор для "<<getname()<<endl;
    }
    string getpredmet(){
        return predmet;
    }
    int getocenka(){
        return ocenka;
    }
    void setpredmet(string p){
        predmet=p;
    }
    void setocenka(int o){
        ocenka=o;
    }
    void proverka(){
        if(ocenka<3){
            cout<<"у "<<getname()<<"неудовлетворительная оценка ("<<ocenka<<") по"<<predmet<<endl;
        }
        else{
            cout<<getname()<<" сдал "<<predmet<<" на "<<ocenka<<endl;
        }
    }
    void operator=(const Student&s){
        cout<<"Student: оператор= "<<endl;
        Person::operator=(s);
        predmet=s.predmet;
        ocenka=s.ocenka;
    }
    friend istream& operator>>(istream&k, Student&s){
        k>>(Person&)s;
        cout<<"введите пердмет:";
        k>>s.predmet;
        cout<<"введите оценку:";
        k>>s.ocenka;
        return k;
    }
    friend ostream& operator<<(ostream&l, const Student&s){
        l<<(const Person&)s;
        l<<" , пердмет: "<<s.predmet<<" , оценка: "<<s.ocenka;
        return l;
    }
};
    //принцип подстановки
void func(Person p){
    cout<<"func получила "<<p<<endl;
}
Person func2(){
    Student s("Крид",30,"программирование",5);
    return s;
}


int main(){
    setlocale(LC_ALL,"Russian");
    string name,predmet;
    int age, ocenka;
    Person p0;
    cout<<"p0= "<<p0<<endl;
    cout<<"введите имя:"<<endl;
    cin>>name;
    cout<<"введите возраст: "<<endl;
    cin>>age;
    Person p1(name, age);
    cout<<"p1= "<<p1<<endl;

    cout<<"введите имя студента: "<<endl;
    cin>>name;
    cout<<"введите возраст студента: "<<endl;
    cin>>age;
    cout<<"введите предмет: "<<endl;
    cin>>predmet;
    cout<<"введите оценку: "<<endl;
    cin>>ocenka;
    Student s1(name,age,predmet,ocenka);
    cout<<"s1= "<<s1<<endl;

    Person p2=p1;
    cout<<"p2= "<<p2<<endl;
    Student s2=s1;
    cout<<"s2= "<<s2<<endl;

    cout<<" у p2 имя- "<<p2.getname()<<" , возраст- "<<p2.getage()<<endl;
    cout<<"у s1 предмет- "<<s1.getpredmet()<<" , оценка= "<<s1.getocenka()<<endl;

    cout<<"введите новые данные для p2:"<<endl;
    cout<<"имя:"<<endl;
    cin>>name;
    cout<<"возраст:"<<endl;
    cin>>age;
    p2.setname(name);
    p2.setage(age);
    cout<<"p2= "<<p2<<endl;

    Person p3;
    p3=p2;
    cout<<"p3= "<<p3<<endl;
    Student s3;
    s3=s1;
    cout<<"s3= "<<s3<<endl;

    Person p4;
    cout<<"введите данные для p4:"<<endl;
    cin>>p4;
    cout<<"ввели: "<<p4<<endl;

    s1.proverka();

    func(s1);
    Person p6=func2();
    cout<<"получили: "<<p6<<endl;
    return 0;
}