#include <iostream>
using namespace std;
#include <cmath>
int main(){
    float n,k,max;
    int i=2;
    int c=1;
    cin>>n;
    max=sin(n+1/n);
    while (i<=n){
        k=sin(n+i/n);
        if (k>max){
            max=k;
            c=1;
        }
        else if (max=k){
            c++;
        }
        i++;
    }
    cout<<"максимальный элемент:"<<max<<endl;
    cout<<"количество таких элементов:"<<c<<endl;
    return 0;
}