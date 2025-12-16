#include <iostream>
using namespace std;
#include <cmath>
//f'(x)=3-(4/x);
//f"(x)=4/x^2;
int main(){
    float x, x0;
    //f(b)*f"(b)>0
    //(3*4-4*ln(4)-5)*(4/4^2)>0 => x0=b
    x=4;
    x0=2;
    double eps=0.000001;
    while(abs(x-x0)>eps){
        x0=x;
        x=x0-((3*x0)-4*log(x0)-5)/(3-(4/x0));
    }
    cout<<"корень: "<<x<<endl;
    return 0;
}