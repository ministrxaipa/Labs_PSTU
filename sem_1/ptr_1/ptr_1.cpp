#include <iostream>
using namespace std;
int main(){
    int a,b;
    cin>>a;
    int *ptr=&a;
    cin>>b;
    *ptr=b;
    cout<<a<<endl;
    return 0;
}