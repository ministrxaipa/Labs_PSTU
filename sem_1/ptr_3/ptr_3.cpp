#include <iostream>
using namespace std;
int main(){
    float a,b,sum;
    cin>>a>>b;
    float *c=&a;
    float *c1=&b;
    sum=*c+*c1;
    cout<<sum<<endl;
    return 0;
}