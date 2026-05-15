#include <iostream>
using namespace std;

class Spisok{
private:
    int*arr;
    int size;
    int k;
public:
    Spisok(){
        k=10;
        size=0;
        arr=new int[k];
    }
    Spisok(int i){
        k=i*2;
        size=i;
        arr=new int[k];
        for(int i=0;i<size;i++){
            arr[i]=0;
        }
    }
    Spisok(const Spisok&s){
        k=s.k;
        size=s.size;
        arr=new int[k];
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
        arr=new int[k];
        for(int i=0;i<size;i++){
            arr[i]=s.arr[i];
        }
    }
    friend istream& operator>>(istream& n, Spisok&s){
        cout<<"введите размер списка:";
        n>>s.size;
        if(s.size>s.k){
            delete[] s.arr;
            s.k=s.size*2;
            s.arr=new int[s.k];
        }
        cout<<"введите "<<s.size<<" элементов";
        for(int i=0;i<s.size;i++){
            n>>s.arr[i];
        }
        return n;
    }
    friend ostream& operator<<(ostream&l, Spisok&s){
        for(int i=0;i<s.size;i++){
            l<<s.arr[i];
            if(i<s.size-1){
                l<<",";
            }
        }
        return l;
    }
    int& operator[](int index){
        return arr[index];
    }
    operator int() const{
        return size;
    }
    Spisok operator*(const Spisok&b){
        int newsize;
        if(size<b.size){
            newsize=size;
        }
        else{
            newsize=b.size;
        }
        Spisok rez(newsize);
        for(int i=0;i<newsize;i++){
            rez.arr[i]=arr[i]*b.arr[i];
        }
        return rez;
    }
    void add(int d){
        if(size>=k){
            k=k*2;
            int*newarr=new int[k];
            for(int i=0;i<size;i++){
                newarr[i]=arr[i];
            }
            delete[] arr;
            arr=newarr;
        }
        arr[size]=d;
        size++;
    }
    int get(int index){
        return arr[index];
    }
    //класс-итеротор
    class Iterator{
    private:
        Spisok*list;
        int pos;
    public:
        Iterator(Spisok*l, int p){
            list=l;
            pos=p;
        }
        int operator*(){
            return list->get(pos);
        }
        void operator++(){
            pos=pos+1;
        }
        bool operator!=(const Iterator& i){
            return pos!=i.pos;
        }
        Iterator operator+(int n){
            Iterator rez(list,pos+n);
            return rez;
        }
    };
    Iterator begin(){
        Iterator it(this,0);
        return it;
    }
    Iterator end(){
        Iterator it(this,size);
        return it;
    }
};

int main(){
    setlocale(LC_ALL,"Russian");
    //конструкторы
    Spisok l1;
    Spisok l2(5);
    Spisok l3=l2;
    cout<<endl;
    //заполнение списков
    l1.add(10);
    l1.add(20);
    l1.add(30);
    l1.add(40);
    cout<<"l1= "<<l1<<endl;
    for(int i=0;i<5;i++){
        l2[i]=i+1;
    }
    cout<<"l2= "<<l2<<endl;
    cout<<endl;

    cout<<"l2[0]= "<<l2[0]<<endl;
    cout<<"l2[2]= "<<l2[2]<<endl;
    l2[1]=100;
    cout<<"l2= "<<l2<<endl;
    cout<<endl;

    int r1=l1;
    int r2=(int)l2;
    cout<<"размер l1= "<<r1<<endl;
    cout<<"размер l2= "<<r2<<endl;
    cout<<endl;

    Spisok l4=l1*l2;
    cout<<"l1*l2= "<<l4<<endl;
    cout<<endl;

    Spisok l5;
    cin>>l5;
    cout<<"ввели: "<<l5<<endl;

    Spisok l6;
    l6=l1;
    cout<<"l6= "<<l6<<endl;

    cout<<"обход l1 с помощью итератора"<<endl;
    for(Spisok::Iterator it=l1.begin();it!=l1.end();++it){
        cout<<*it<<" ";
    }
    cout<<endl;

    Spisok::Iterator it1=l1.begin();
    cout<<"первый элемент: "<<*it1<<endl;
    Spisok::Iterator it2=it1+2;
    cout<<"после +2: "<<*it2<<endl;
    Spisok::Iterator it3=it1+3;
    cout<<"после +3: "<<*it3<<endl;

    return 0;
}