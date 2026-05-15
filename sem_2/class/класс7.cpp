#include <iostream>
using namespace std;

//шаблон класса-контейнера
template <class T>
class Spisok{
private:
    T*arr;
    int size;
    int k;
public:
    Spisok(){
        k=10;
        size=0;
        arr=new T[k];
    }
    Spisok(int n){
        k=n*2;
        size=n;
        arr=new T[k];
        for(int i=0;i<size;i++){
            arr[i]=T();
        }
    }
    Spisok(const Spisok&s){
        k=s.k;
        size=s.size;
        arr=new T[k];
        for(int i=0;i<size;i++){
            arr[i]=s.arr[i];
        }
    }
    ~Spisok(){
        delete[] arr;
    }
    void operator=(const Spisok&s){
        delete[] arr;
        k=s.k;
        size=s.size;
        arr=new T[k];
        for(int i=0;i<size;i++){
            arr[i]=s.arr[i];
        }
    }
    friend istream& operator>>(istream& n, Spisok<T>&s){
        cout<<"введите размер списка:";
        n>>s.size;
        if(s.size>s.k){
            delete[] s.arr;
            s.k=s.size*2;
            s.arr=new T[s.k];
        }
        cout<<"введите "<<s.size<<" элементов";
        for(int i=0;i<s.size;i++){
            n>>s.arr[i];
        }
        return n;
    }
    friend ostream& operator<<(ostream&l, Spisok<T>&s){
        for(int i=0;i<s.size;i++){
            l<<s.arr[i];
            if(i<s.size-1){
                l<<",";
            }
        }
        return l;
    }
    T& operator[](int index){
        return arr[index];
    }
    operator int() const{
        return size;
    }
    Spisok<T> operator*(const Spisok<T>&b){
        int newsize;
        if(size<b.size){
            newsize=size;
        }
        else{
            newsize=b.size;
        }
        Spisok<T> rez(newsize);
        for(int i=0;i<newsize;i++){
            rez.arr[i]=arr[i]*b.arr[i];
        }
        return rez;
    }
};

//пользовательский класс
class Pair{
private:
    int a;
    double b;
public:
    Pair(){
        a=0;
        b=0;
    }
    Pair(int x, double y){
        a=x;
        b=y;
    }
    Pair(const Pair&p){
        a=p.a;
        b=p.b;
    }
    void operator=(const Pair&p){
        a=p.a;
        b=p.b;
    }
    Pair operator*(const Pair&p){
        Pair res;
        res.a=a*p.a;
        res.b=b*p.b;
        return res;
    }
    friend istream& operator>>(istream&k, Pair&p){
        cout<<"введите целое число:";
        k>>p.a;
        cout<<"введите дробное число:";
        k>>p.b;
        return k;
    }
    friend ostream& operator<<(ostream&l, const Pair&p){
        l<<p.a<<" : "<<p.b;
        return l;
    }
};

int main(){
    setlocale(LC_ALL,"Russian");
    //тест на int
    Spisok<int> l1(4);
    l1[0]=10;
    l1[1]=20;
    l1[2]=30;
    l1[3]=40;

    Spisok<int> l2(5);
    l2[0]=1;
    l2[1]=2;
    l2[2]=3;
    l2[3]=4;
    l2[4]=5;

    cout<<"list1= "<<l1<<endl;
    cout<<"list2= "<<l2<<endl;
    cout<<"размер list1= "<<(int)l1<<endl;
    cout<<"list1[2]= "<<l1[2]<<endl;
    Spisok<int> l3=l1*l2;
    cout<<"list1*list2= "<<l3<<endl;
    //тест на float
    Spisok<float> lf1(3);
    lf1[0]=1.5;
    lf1[1]=2.5;
    lf1[2]=3.5;

    Spisok<float> lf2(3);
    lf2[0]=2.0;
    lf2[1]=3.0;
    lf2[2]=4.0;
    cout<<"listf1= "<<lf1<<endl;
    cout<<"listf2= "<<lf2<<endl;
    Spisok<float> lf3=lf1*lf2;
    cout<<"listf1*listf2= "<<lf3<<endl;
    cout<<endl;
    //тест на double
    Spisok<double> ld1(3);
    ld1[0]=1.1;
    ld1[1]=2.2;
    ld1[2]=3.3;

    Spisok<double> ld2(3);
    ld2[0]=2.0;
    ld2[1]=3.0;
    ld2[2]=4.0;
    cout<<"listd1= "<<ld1<<endl;
    cout<<"listd2= "<<ld2<<endl;
    Spisok<double> ld3=ld1*ld2;
    cout<<"listd1*listd2= "<<ld3<<endl;
    cout<<endl;

    Spisok<Pair> lp1(3);
    lp1[0]=Pair(10,1.2);
    lp1[1]=Pair(20,2.5);
    lp1[2]=Pair(30,3.5);

    Spisok<Pair> lp2(3);
    lp2[0]=Pair(1,0.5);
    lp2[1]=Pair(2,1.5);
    lp2[2]=Pair(3,2.5);
    cout<<"listpair1= "<<lp1<<endl;
    cout<<"listpair2= "<<lp2<<endl;
    Spisok<Pair> lp3=lp1*lp2;
    cout<<"lp1*lp2= "<<lp3<<endl;

    cout<<"ввод списка"<<endl;
    Spisok<int> lp4;
    cin>>lp4;
    cout<<"введи: "<<lp4<<endl;
    return 0;
}