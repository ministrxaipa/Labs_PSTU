#include <iostream>
using namespace std;

//сортировка пузырьком для сортировки одного ведра
void puzirek(float sort[], int razmer){
    for(int i=0;i<razmer-1;i++){
        for(int j=0;j<razmer-i-1;j++){
            if(sort[j]>sort[j+1]){
                float vremeno=sort[j];
                sort[j]=sort[j+1];
                sort[j+1]=vremeno;
            }
        }
    }
}

//блочная сортировка
void blochnaya(float massiv[], int n){
    float vedra[10][10];
    int razmervedra[10];
    for(int i=0;i<n;i++){
        razmervedra[i]=0;
    }

    for(int i=0;i<n;i++){
        float element=massiv[i];
        int nomer=(int)(element*10);
        if(nomer==10){
            nomer=9;
        }
        vedra[nomer][razmervedra[nomer]]=element;
        razmervedra[nomer]++;
    }

    for(int i=0;i<10;i++){
        if(razmervedra[i]>0){
            puzirek(vedra[i], razmervedra[i]);
        }
    }

    int index=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<razmervedra[i];j++){
            massiv[index]=vedra[i][j];
            index++;
        }
    }
}

//вывод массива
void vivod(float massiv[], int n){
    for(int i=0;i<n;i++){
        cout<<massiv[i]<<" ";
    }
    cout<<endl;
}

int main(){
    float massiv[]={0.42,0.83,0.56,0.18,0.23,0.1,0.98,0.67,0.34,0.76};
    int n=sizeof(massiv)/sizeof(massiv[0]);
    cout<<"Исходный массив: ";
    vivod(massiv,n);
    blochnaya(massiv,n);
    cout<<"Отсортированный массив: ";
    vivod(massiv,n);
    return 0;
}