#include <iostream>
using namespace std;

void sliyanie(int arr[], int levo, int sered, int pravo){
    int razmerL=sered-levo+1;
    int razmerP=pravo-sered;
    int L[razmerL], P[razmerP];

    for(int i=0;i<razmerL; i++){
        L[i]=arr[levo+i];
    }
    for(int j=0; j<razmerP; j++){
        P[j]=arr[sered+1+j];
    }

    int i=0;
    int j=0;
    int k=levo;

    while (i<razmerL && j<razmerP){
        if (L[i]<=P[j]){
            arr[k]=L[i];
            i++;
        }
        else{
            arr[k]=P[j];
            j++;
        }
        k++;
    }

    while(i<razmerL){
        arr[k]=L[i];
        i++;
        k++;
    }
    while(j<razmerP){
        arr[k]=P[j];
        j++;
        k++;
    }
}

void sortSliyanie(int arr[], int levo, int pravo){
    if(levo>=pravo){
        return;
    }
    int sered=(levo+pravo+1)/2;
    sortSliyanie(arr,levo,sered-1);
    sortSliyanie(arr,sered,pravo);
    sliyanie(arr,levo,sered-1,pravo);
}

void vivod(int arr[], int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main(){
    setlocale(LC_ALL, "Russian");
    int arr[]={56, 3,4,89,2,1,56,90,54,3,2,12,67,5,34};
    int n=sizeof(arr)/sizeof(arr[0]);
    cout<<"Исходный: ";
    vivod(arr,n);
    sortSliyanie(arr,0,n-1);
    cout<<"Отсортированный: ";
    vivod(arr,n);
    return 0;
}