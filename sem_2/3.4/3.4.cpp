#include <iostream>
using namespace std;

int main(){
    const int n=8;
    int arr[n];
    bool k=true;
    for (int i=0;i<n;i++){
        cin>>arr[i];
    }
    for (int i=1;i<n;i++){
        if (arr[i]<arr[i-1]){
            k=false;
            break;
        }
    }
    if (k==true){
        cout<<"массив упорядочен"<<endl;
    }
    else{
        cout<<"массив неупорядочен"<<endl;
    }
    return 0;
}