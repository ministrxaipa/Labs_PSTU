#include <iostream>
using namespace std;
//f'(x)=3-(4/x);
#include <cmath>
int main(){
    //lamb=-1/r т.к f'(x)>0
    ////r=max(|f'(a)|, |f'(b)|)
    //lamb=-1/4=-0.25
    float x,x0;
    double eps=0.000001;
    double lamb=-0.25;
    x=4;
    x0=2;
    while (abs(x-x0)>eps){
        x0=x;
        x=lamb*(3*x0-4*log(x0)-5)+x0;
    }
    cout<<"корень:"<<x<<endl;
    return 0;
}

