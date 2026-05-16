#include <iostream>
#include <string>
using namespace std;

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
            throw 1;
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
            throw 2;
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
                throw 3;
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
        cout<<"размер a "<<(int)a<<endl;
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
        cout<<"it+3- "<<*it2<<endl;
    }
    catch(int k){
        if(k==1){
            cout<<"индекс за границей"<<endl;
        }
        else if(k==2){
            cout<<"разные размеры списков"<<endl;
        }
        else if(k==3){
            cout<<"переход итератора за границы"<<endl;
        }
        else{
            cout<<"неизвестная ошибка"<<endl;
        }
    }

    cout<<"ОШИБКА 1"<<endl;
    try{
        Spisok a(3);
        a[0]=10;
        a[1]=20;
        a[2]=30;
        int x=a[10];
    }
    catch(int k){
        if(k==1){
            cout<<"ОШИБКА 1:индекс за границей"<<endl;
        }
        else{
            cout<<"ОШИБКА ДРУГАЯ:"<<k<<endl;
        }
    }

    cout<<"ОШИБКА 2"<<endl;
    try{
        Spisok a(3);
        Spisok b(5);
        Spisok c=a*b;
    }
    catch(int k){
        if(k==2){
            cout<<"ОШИБКА 2:разные размеры"<<endl;
        }
        else{
            cout<<"ОШИБКА ДРУГАЯ:"<<k<<endl;
        }
    }

    cout<<"ОШИБКА 3"<<endl;
    try{
        Spisok a(4);
        for(int i=0;i<4;i++){
            a[i]=(i+1)*10;
        }
        Spisok::Iterator it=a.nachalo();
        cout<<"текущий элемент: "<<*it<<endl;
        Spisok::Iterator it2=it+10;
    }
    catch(int k){
        if(k==3){
            cout<<"ОШИБКА 3:переход за границы"<<endl;
        }
        else{
            cout<<"ОШИБКА ДРУГАЯ:"<<k<<endl;
        }
    }
    return 0;
}

