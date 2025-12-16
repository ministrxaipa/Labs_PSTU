#include <iostream>
using namespace std;
#include <cmath>
int main(){
    float n,x,max;
    int i=2;
    int num=1;
    cin>>n;
    max=sin((n+1)/n);
    while(i<=n){
        x=sin((n+i)/n);
        if (x>max){
            max=x;
            num=i;
        }
        i++;
    }
    cout<<"максимальный элемент:"<<max<<"номер:"<<num<<endl;
    return 0;
}

