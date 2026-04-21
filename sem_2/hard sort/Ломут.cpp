#include <iostream>
using namespace std;

int Lomut(int massiv[], int niz, int verh){
    int opora=massiv[verh];
    int granica=niz-1;
    for(int i=niz;i<verh;i++){
        if(massiv[i]<=opora){
            granica++;
            swap(massiv[granica],massiv[i]);
        }
    }
    swap(massiv[granica+1],massiv[verh]);
    return granica+1;
}

void Sort(int massiv[],int niz,int verh){
    if(niz<verh){
        int oporaIndex=Lomut(massiv,niz,verh);
        Sort(massiv,niz,oporaIndex-1);
        Sort(massiv,oporaIndex+1,verh);
    }
}

void vivod(int massiv[],int razmer){
    for(int i=0;i<razmer;i++){
        cout<<massiv[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int massiv[]={7,2,1,6,8,5,3,4,2,6,5,1};
    int razmer=sizeof(massiv)/sizeof(massiv[0]);
    cout<<"Исходный: ";
    vivod(massiv,razmer);
    Sort(massiv,0,razmer-1);
    cout<<"Отсортированный: ";
    vivod(massiv,razmer);
    return 0;
}