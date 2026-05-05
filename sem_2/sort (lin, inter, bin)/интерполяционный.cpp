#include <iostream>
using namespace std;

void puzirek(int arr[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(arr[j]>arr[j+1]){
                int vremeno=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=vremeno;
            }
        }
    }
}

int interpol(int arr[], int n,int x){
    int levo=0;
    int pravo=n-1;
    while(levo<=pravo && x>=arr[levo] && x<=arr[pravo]){
        if(levo==pravo){
            if(arr[levo]==x){
                return levo;
            }
            else{
                return -1;
            }
        }
        int pos=levo+(pravo-levo)*(x-arr[levo])/(arr[pravo]-arr[levo]);
        if(arr[pos]==x){
            return pos;
        }
        if(arr[pos]<x){
            levo=pos+1;
        }
        if(arr[pos]>x){
            pravo=pos-1;
        }
    }
    return -1;
}

void vivod(int arr[], int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main(){
    setlocale(LC_ALL,"Russian");
    int n;
    cout<<"сколько чисел в массиве?"<<endl;
    cin>>n;
    int chisla[n];
    cout<<"введите числа:"<<endl;
    for(int i=0;i<n;i++){
        cin>>chisla[i];
    }
    cout<<"исходный массив:"<<endl;
    vivod(chisla,n);
    puzirek(chisla,n);
    cout<<"отсортированный массив:"<<endl;
    vivod(chisla,n);
    int poisk;
    cout<<"какое число ищем?"<<endl;
    cin>>poisk;
    int rez=interpol(chisla,n,poisk);
    if(rez==-1){
        cout<<"число "<<poisk<<" не найдено("<<endl; 
    }
    else{
        cout<<"число "<<poisk<<" найдено на позиции "<<rez<<endl;
    }
    return 0;
}