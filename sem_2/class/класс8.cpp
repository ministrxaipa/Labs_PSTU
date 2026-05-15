#include <iostream>
#include <string>
using namespace std;

//абстрактный класс
class Print{
protected:
    string name;
    string author;
public:
    Print(){
        name="не известно";
        author="не известно";
    }
    Print(string n,string a){
        name=n;
        author=a;
    }
    Print(const Print&p){
        name=p.name;
        author=p.author;
    }
    virtual ~Print(){}

    void operator=(const Print&p){
        name=p.name;
        author=p.author;
    }
    string getname(){
        return name;
    }
    string getauthor(){
        return author;
    }
    void setname(string n){
        name=n;
    }
    void setauthor(string a){
        author=a;
    }
    virtual void input()=0;
    virtual void print()=0;
};

//произвольный класс
class Magazin:public Print{
private:
    int pages;
public:
    Magazin():Print(){
        pages=0;
    }
    Magazin(string n, string a, int p):Print(n,a){
        pages=p;
    }
    Magazin(const Magazin&m):Print(m){
        pages=m.pages;
    }
    ~Magazin(){}

    void operator=(const Magazin&m){
        Print::operator=(m);
        pages=m.pages;
    }
    int getpages(){
        return pages;
    }
    void setpages(int p){
        pages=p;
    }
    virtual void input(){
        cout<<"введите название:";
        cin.ignore();
        getline(cin,name);
        cout<<"введите автора:";
        getline(cin,author);
        cout<<"введите кол-во стр:";
        cin>>pages;
    }
    virtual void print(){
        cout<<"название: "<<name<<" ,автор: "<<author<<" , страниц: "<<pages<<endl;
    }
    void printn(){
        cout<<name<<endl;
    }
};

//класс-группа
class Tree{
protected:
    Magazin**arr; //массив указателей на журнал
    int size;     //сколько сейчас элементов
    int k;        //сколько можно вместить
public:
    Tree(){
        k=10;
        size=0;
        arr=new Magazin*[k];
    }
    Tree(int n){
        k=n*2;
        size=n;
        arr=new Magazin*[k];
        for(int i=0;i<size;i++){
            arr[i]=new Magazin();
            arr[i]->input();
        }
    }
    Tree(const Tree&t){
        k=t.k;
        size=t.size;
        arr=new Magazin*[k];
        for(int i=0;i<size;i++){
            arr[i]=new Magazin(*t.arr[i]);
        }
    }
    virtual ~Tree(){
        for(int i=0;i<size;i++){
            delete arr[i];
        }
        delete[] arr;
    }

    Tree& operator=(const Tree&t){
        if(this!=&t){
            for(int i=0;i<size;i++){
                delete arr[i];
            }
            delete[] arr;
            k=t.k;
            size=t.size;
            arr=new Magazin*[k];
            for(int i=0;i<size;i++){
                arr[i]=new Magazin(*t.arr[i]);
            }
        }
        return *this;
    }
    void add(){
        if(size>=k){
            k=k*2;
            Magazin** newarr=new Magazin*[k];
            for(int i=0;i<size;i++){
                newarr[i]=arr[i];
            }
            delete[] arr;
            arr=newarr;
        }
        arr[size]=new Magazin();
        cout<<"введите новый элемент:"<<endl;
        arr[size]->input();
        size++;
    }
    void remove(){
        if(size==0){
            cout<<"пусто"<<endl;
            return;
        }
        int index;
        cout<<"(1-"<<size<<")"<<endl;
        cin>>index;
        index--;
        if(index<0 ||index>=size){
            cout<<"неверно"<<endl;
            return;
        }
        delete arr[index];
        for(int i=index;i<size-1;i++){
            arr[i]=arr[i+1];
        }
        size--;
    }
    void showvse(){
        if(size==0){
            cout<<"пусто"<<endl;
            return;
        }
        for(int i=0;i<size;i++){
            cout<<i+1<<". ";
            arr[i]->print();
        }
        cout<<"всего: "<<size<<" элементов"<<endl;
    }
    void showname(){
        if(size==0){
            cout<<"пусто"<<endl;
            return;
        }
        for(int i=0;i<size;i++){
            cout<<i+1<<". ";
            arr[i]->printn();
        }
    }
    operator int() const{
        return size;
    }
    Magazin* get(int index){
        if(index>=0 &&index<size){
            return arr[index];
        }
        return nullptr;
    }
};

//класс диалог
class Dialog:public Tree{
public:
    Dialog():Tree(){};
    Dialog& operator=(const Tree&t){
        Tree::operator=(t);
        return *this;
    }
    void start(){
        char com;
        while (true){
            cout<<"введите команду:";
            cin>>com;
            if(com=='m'){
                int n;
                cin>>n;
                Tree newtree(n);  //создаем новую группу из n элементов
                *this = newtree;
            }
            else if(com=='+'){
                add();
                break;
            }
            else if(com=='-'){
                remove();
            }
            else if(com=='s'){
                showvse();
            }
            else if(com=='z'){
                showname();
            }
            else if(com=='q'){
                cout<<"пока пока"<<endl;
                return;
            }
            else{
                cout<<"неправильная команда"<<endl;
            }
        }
    }
};

int main(){
    setlocale(LC_ALL,"Russian");
    Dialog d;  //создание объектов диалога
    d.start(); //обработка команд
    return 0;
}