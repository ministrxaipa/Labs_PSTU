#include <iostream>
using namespace std;

int main(){
    const int n=8;
    int arr[n]={1,2,3,4,5,6,7,8};
    int k;
    cin>>k;
    for (int i=k;i<n;i++){
        cout<<arr[i]<<" ";
    }
    for (int i=0;i<k;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}