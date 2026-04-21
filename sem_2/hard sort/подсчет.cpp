#include <iostream>
using namespace std;

void Podschet(int arr[],int n){
    int max=arr[0];
    for(int i=0;i<n;i++){
        if(arr[i]>max){
            max=arr[i];
        }
    }
    int count[max+1];
    for(int i=0;i<=max;i++){
        count[i]=0;
    }
    for(int i=0;i<n;i++){
        count[arr[i]]++;
    }
    for(int i=0;i<n;i++){
        count[i]=count[i]+count[i-1];
    }
    int vremeno[n];
    for(int i=n-1;i>=0;i--){
        int chislo=arr[i];
        int pozicia=count[chislo]-1;
        vremeno[pozicia]=chislo;
        count[chislo]--;
    }
    for(int i=0;i<n;i++){
        arr[i]=vremeno[i];
    }
}

void vivod(int arr[],int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int arr[]={4,2,2,8,3,3,1,4,5,8};
    int n=sizeof(arr)/sizeof(arr[0]);
    cout<<"Исходный: ";
    vivod(arr,n);
    Podschet(arr,n);
    cout<<"Отсортированный: ";
    vivod(arr,n);
    return 0;
}