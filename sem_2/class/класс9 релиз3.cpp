#include <iostream>
#include <string>
using namespace std;

//классы для исключений
//базовый класс для всех ошибок
class Oshibka{
protected:
    string text;
public:
    Oshibka(string t){
        text=t;
    }
    string chto(){
        return text;
    }
};
//ошибка: выход за границы
class Zagranici:public Oshibka{
public:
    Zagranici(int index, int razmer):Oshibka("ошибка, индекс выходит за границы"){}
};
//ошибка: разные размеры списков при умножении
class Raznie:public Oshibka{
public:
    Raznie(int r1, int r2):Oshibka("ошибка, разные размеры"){}
};
//ошибка: неверный шаг
class Shag:public Oshibka{
public:
    Shag(int p, int s, int r):Oshibka("ошибка, неверный шаг"){}
};

//класс список
class Spisok{
private:
    int*arr;
    int size;
public:
    Spisok(){
        size=0;
        arr=new int[0];
    }
    Spisok(int n){
        size=n;
        arr=new int[size];
        for(int i=0;i<size;i++){
            arr[i]=0;
        }
    }
    Spisok(const Spisok& s){
        size=s.size;
        arr=new int[size];
        for(int i=0;i<size;i++){
            arr[i]=s.arr[i];
        }
    }
    ~Spisok(){
        delete[] arr;
    }

    //присваивание
    void operator=(const Spisok&s){
        if(this!=&s){
            delete[] arr;
            size=s.size;
            arr=new int[size];
            for(int i=0;i<size;i++){
                arr[i]=s.arr[i];
            }
        }
    }
    //доступ по индексу
    int& operator[](int index){
        if(index<0 ||index>=size){
            throw Zagranici(index,size);
        }
        return arr[index];
    }
    //размер
    operator int() const{
        return size;
    }
    //умножение списков
    Spisok operator*(const Spisok&s){
        if(size!=s.size){
            throw Raznie(size,s.size);
        }
        Spisok rez(size);
        for(int i=0;i<size;i++){
            rez.arr[i]=arr[i]*s.arr[i];
        }
        return rez;
    }
    //итератор
    class Iterator{
    private:
        Spisok*list;
        int pos;
    public:
        Iterator(Spisok*l,int p){
            list=l;
            pos=p;
        }
        int operator*(){
            return list->arr[pos];
        }
        void operator++(){
            pos++;
        }
        //переход вправо
        Iterator operator+(int n){
            int newpos=pos+n;
            if(newpos<0 ||newpos>=list->size){
                throw Shag(pos,n,list->size);
            }
            return Iterator(list, newpos);
        }
        bool operator!=(const Iterator&it){
            return pos!=it.pos;
        }
    };
    Iterator nachalo(){
        return Iterator(this,0);
    }
    Iterator konec(){
        return Iterator(this,size);
    }
};

int main(){
    setlocale(LC_ALL,"Russian");
    cout<<"НОРМАЛЬНАЯ РАБОТА"<<endl;
    try{
        Spisok a(5);
        Spisok b(5);
        for(int i=0;i<(int)a;i++){
            a[i]=i+1;
            b[i]=(i+1)*2;
        }
        cout<<"размер a= "<<(int)a<<endl;
        cout<<"a[2]= "<<a[2]<<endl;
        Spisok c=a*b;
        cout<<"a*b= ";
        for(int i=0;i<(int)c;i++){
            cout<<c[i]<<" ";
        }
        cout<<endl;
        Spisok::Iterator it=a.nachalo();
        Spisok::Iterator it2=it+3;
        cout<<"it= "<<*it<<endl;
        cout<<"int+3= "<<*it2<<endl;
    }
    catch(Oshibka&o){
        cout<<o.chto()<<endl;
    }
    
    cout<<"ОШИБКА 1: ЗА ГРАНИЦЕЙ"<<endl;
    try{
        Spisok a(3);
        a[0]=10;
        a[1]=20;
        a[2]=30;
        int x=a[10];
    }
    catch(Zagranici&o){
        cout<<o.chto()<<endl;
    }

    cout<<"ОШИБКА 2: РАЗНЫЕ РАЗМЕРЫ"<<endl;
    try{
        Spisok a(3);
        Spisok b(5);
        Spisok c=a*b;
    }
    catch(Raznie&o){
        cout<<o.chto()<<endl;
    }

    cout<<"ОШИБКА 3:НЕПРАВИЛЬНЫЙ ШАГ"<<endl;
    try{
        Spisok a(4);
        Spisok::Iterator it=a.nachalo();
        Spisok::Iterator it2=it+10;
    }
    catch(Shag&o){
        cout<<o.chto()<<endl;
    }
    return 0;
}























































