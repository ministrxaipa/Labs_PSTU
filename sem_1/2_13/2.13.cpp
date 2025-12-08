#include <iostream>
using namespace std;
#include <cmath>
int main() {
    int a,b,c,d,x1,x2;
    cin>>a>>b>>c;
    d=pow(b,2)-4*a*c;
    if (d>0){
        x1=(-b+sqrt(d))/(2*a);
        x2=(-b-sqrt(d))/(2*a);
        cout<<"x1="<<x1<<"; x2="<<x2<<endl;
    }
    else if (d==0){
        x1=(-b)/(2*a);
        cout<<"x1=x2="<<x1<<endl;
    }
    else{
        cout<<"корней нет"<<endl;
    }
    return 0;
}
