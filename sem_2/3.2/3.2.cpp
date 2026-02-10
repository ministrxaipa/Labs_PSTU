#include <iostream>
using namespace std;

int main(){
    const int n=8;
    int arr[n];
    int p,q, tmp;
    cin>>p>>q;
    for (int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<"исходный массив: ";
    for (int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    for (int i=p;i<q;i++){
        tmp=arr[i];
        arr[i]=arr[q];
        arr[q]=tmp;
        q--;
    }
    cout<<"исправленный код:";
    for (int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}