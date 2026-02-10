#include <iostream>
using namespace std;

int main(){
    const int n=8;
    int arr[n]={1,2,3,4,5,6,7,8};
    for (int i=0;i<n;i++){
        if (arr[i]%2==0){
            cout<<"-1 "<<arr[i]<<" ";
        }
        else{
            cout<<arr[i]<<" ";
        }
    }
    cout<<endl;
    return 0;
}