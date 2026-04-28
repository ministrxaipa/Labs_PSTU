#include <iostream>
using namespace std;

void puzirek(int massiv[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(massiv[j]>massiv[j+1]){
                int vremeno=massiv[j];
                massiv[j]=massiv[j+1];
                massiv[j+1]=vremeno;
            }
        }
    }
}

int binarniy(int massiv[], int levo, int pravo, int k){
    while(levo<=pravo){
        int seredina=levo+(pravo-levo)/2;
        if(massiv[seredina]==k){
            return seredina;
        }
        if(massiv[seredina]<k){
            levo=seredina+1;
        }
        else{
            pravo=seredina-1;
        }
    }
    return -1;
}

void vivod(int massiv[], int n){
    for(int i=0;i<n;i++){
        cout<<massiv[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int n;
    cout<<"сколько чисел будет в массиве?"<<endl;
    cin>>n;
    int massiv[n];
    cout<<"введите числа: "<<endl;
    for(int i=0;i<n;i++){
        cin>>massiv[i];
    }
    cout<<"исходный массив: "<<endl;
    vivod(massiv,n);
    puzirek(massiv,n);
    cout<<"отсортированный массив: "<<endl;
    vivod(massiv,n);
    int k;
    cout<<"какое число искать?"<<endl;
    cin>>k;
    int rez=binarniy(massiv,0,n-1,k);
    if(rez==-1){
        cout<<"число "<<k<<" не найдено"<<endl;
    }
    else{
        cout<<"число "<<k<<" найдено, это"<<rez<<"-й элемент"<<endl;
    }
    return 0;
}