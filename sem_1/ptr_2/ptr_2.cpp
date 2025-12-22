#include <iostream>
using namespace std;
int main(){
    int a,b;
    cin>>a>>b;
    int *c1=&a;
    int *c2=&b;
    int k=*c1;
    *c1=*c2;
    *c2=k;
    cout<<"a="<<a<<"b="<<b<<endl;
    return 0;
}