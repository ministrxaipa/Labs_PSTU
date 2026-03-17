//вариант 15
#include <iostream>
using namespace std;

int perevod(int chislo){
    int otv=0, mnog=1;
    while (chislo>0){
        int zifra=chislo%10;
        otv+=zifra*mnog;
        mnog*=8;
        chislo/=10;
    }
    return otv;
}

void visov (int kolvo, int* p){
    cout<<"результаты перевода: "<<endl;
    for (int i=0;i<kolvo;i++){
        int rez=perevod(*p);
        cout<<*p<<"(8)= "<<rez<<"(10)"<<endl;
        p++;
    }
}

int main() {
    int n;
    cin>>n;
    int*arr=new int [n];
    cout<<"восьмиричные числа:"<<endl;
    for (int i=0;i<n;i++){
        cin>>arr[i];
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    visov (n,arr);
    
    delete[] arr;
    return 0;
}


