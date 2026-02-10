#include <iostream>
using namespace std;

int main(){
    const int n=9;
    int arr[n];
    int max, k=1;
    for (int i=0;i<n;i++){
        cin>>arr[i];
    }
    max=arr[0];
    for (int i=1;i<n;i++){
        if (arr[i]>max){
            max=arr[i];
            k=1;
        }
        else if (arr[i]==max){
            k++;
        }
    }
    cout<<"максимальный элемент: "<<max<<endl;
    cout<<"кол-во макс элементиов: "<<k<<endl;
    return 0;
}