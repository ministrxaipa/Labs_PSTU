#include <iostream>
using namespace std;
#include <cmath>
int main() {
    float a,b,c;
    float fA,fB,fC;
    double eps=0.000001;
    a=2;
    b=4;
    fA=(3*a-4*log(a)-5);
    fB=(3*b-4*log(b)-5);
    while (b-a>eps){
        c=(a+b)/2;
        fC=(3*c-4*log(c)-5);
        if (fabs(fC)<eps){
            break;
        }
        else if (fA*fC<0){
            b=c;
            fB=fC;
        }
        else if (fC*fB<0){
            a=c;
            fA=fC;
        }
    }
	cout<<"корни:"<<a<<";"<<b<<endl;
    return 0;
}