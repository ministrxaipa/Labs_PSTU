#include <iostream>
using namespace std;

int Hoar(int massiv[],int niz, int verh){
    int opora=massiv[(niz+verh)/2];
    int i=niz;
    int j=verh;
    while(i<=j){
        while(massiv[i]<opora){
            i++;
        }
        while(massiv[j]>opora){
            j--;
        }
        if(i<=j){
            swap(massiv[i],massiv[j]);
            i++;
            j--;
        }
    }
    return i;
}

void quickSort(int massiv[],int niz, int verh){
    if(niz<verh){
        int granica=Hoar(massiv,niz,verh);
        quickSort(massiv,niz,granica-1);
        quickSort(massiv,granica,verh);
    }
}

void vivod(int massiv[], int razmer){
    for(int i=0;i<razmer;i++){
        cout<<massiv[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int massiv[]={7,2,1,6,8,5,3,4};
    int razmer=sizeof(massiv)/sizeof(massiv[0]);
    cout<<"исходный: ";
    vivod(massiv,razmer);
    quickSort(massiv,0,razmer-1);
    cout<<"результат: ";
    vivod(massiv,razmer);
    return 0;
}