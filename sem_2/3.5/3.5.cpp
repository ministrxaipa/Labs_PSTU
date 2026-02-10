#include <iostream>
using namespace std;

int main(){
    const int n=8;
    int arr[n], max;
    for (int i=0;i<n;i++){
        cin>>arr[i];
    }
    max=arr[0];
    for (int i=0;i<n;i++){
        if (arr[i]>max){
            max=arr[i];
        }
    }
    cout<<"максимальный элемент: "<<max<<endl;
    return 0;
}