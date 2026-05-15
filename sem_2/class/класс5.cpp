#include <iostream>
#include <string>
using namespace std;

//абстрактный класс (нельзя создать объект)
class Person{
protected:
    string name;
    int age;
public:
    Person(string n, int a){
        name=n;
        age=a;
    }
    virtual ~Person(){}
    void setname(string n){
        name=n;
    }
    void setage(int a){
        age=a;
    }
    virtual void show()=0;
};

//произвольный класс
class Student:public Person{
private:
    string predmet;
    int ocenka;
public:
    Student(string n, int a,string p, int o):Person(n,a){
        predmet=p;
        ocenka=o;
    }
    void setpredmet(string p){
        predmet=p;
    }
    void setocenka(int o){
        ocenka=o;
    }
    void proverka(){
        if(ocenka<3){
               cout<<"у "<<name<<" неудовлетворительная оценка ("<<ocenka<<") по"<<predmet<<endl;
        }
        else{
            cout<<name<<" сдал "<<predmet<<" на "<<ocenka<<endl;
        }
    }
    virtual void show(){
        cout<<"студент: "<<name<<" , "<<age<<" лет,"<<predmet<<" - "<<ocenka<<endl;
    }
};

//класс вектор
class Vector{
private:
    Person**arr;
    int size;
    int k;
public:
    Vector(){
        k=5;
        size=0;
        arr=new Person*[k];
    }
    ~Vector(){
        delete[] arr;
    }
    void add(Person*p){
        if(size>=k){
            k=k*2;
            Person**newarr=new Person*[k];
            for(int i=0;i<size;i++){
                newarr[i]=arr[i];
            }
            delete[] arr;
            arr=newarr;
        }
        arr[size]=p;
        size++;
    }
    int getsize(){
        return size;
    }
    Person* get(int index){
        if(index>=0 &&index<size){
            return arr[index];
        }
        return nullptr;
    }
    friend ostream& operator<<(ostream&k, Vector&v){
        k<<"всего"<<v.size<<"элементов"<<endl;
        for(int i=0;i<v.size;i++){
            k<<i+1<<".";
            v.arr[i]->show();
        }
        return k;
    }
};

int main(){
    setlocale(LC_ALL,"Russian");
    Student s1("Крид",30,"математика",4);
    Student s2("Артур", 20,"физика",2);
    Student s3("Персиков",19,"программирование",5);
    cout<<endl;
    //создание вектора и добаление студентов
    Vector v;
    v.add(&s1);
    v.add(&s2);
    v.add(&s3);
    cout<<endl;
    cout<<"вывод вектора"<<endl;
    cout<<v<<endl;
    cout<<"проверка оценок"<<endl;
    s1.proverka();
    s2.proverka();
    s3.proverka();
    cout<<endl;
    cout<<"полиморфизм"<<endl;
    Person*ptr=&s1; //указатель на Person указывает на Student
    ptr->show(); //вызовется Stident::show()
    cout<<endl;
    cout<<"добавление нового студента"<<endl;
    string name,predmet;
    int age, ocenka;
    cout<<"введите имя";
    cin>>name;
    cout<<"введите возраст";
    cin>>age;
    cout<<"введите предмет";
    cin>>predmet;
    cout<<"введите оценку";
    cin>>ocenka;
    Student s4(name,age,predmet,ocenka);
    v.add(&s4);
    cout<<endl;
    cout<<"вектор после добавления:"<<endl;
    cout<<v<<endl;
    return 0;
}