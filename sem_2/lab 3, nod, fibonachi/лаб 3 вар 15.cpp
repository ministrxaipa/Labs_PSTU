#include <iostream>
#include <cmath>
using namespace std;

int main(){
    //входные данные
    double a=0.1;
    double b=1.0;
    int k=10;
    int n=30;
    double eps=0.0001;
    //шаг
    double shag=(b-a)/k;
    double x=a;
    while(x<=b+0.0001){
        //точное значеник
        double arctg=atan(x);
        double tochno=((1+x*x)/2.0)*arctg-(x/2.0);
        //ряд для заданного n
        double sumn=0;
        for(int i=1;i<=n;i++){
            //вычисляем знак
            double znak;
            if(i%2==1){
                znak=1;
            }
            else{
                znak=-1;
            }
            //степень
            double step=2*i+1;
            double xstep=pow(x,step);
            //знаменатель
            double znamen=4*i*i-1;
            //член ряда
            double ch=znak*xstep/znamen;
            //добавляем к сумме
            sumn=sumn+ch;
        }
        //ряд для точности
        double sumeps=0;
        int i=1;
        while(true){
            //знак
            double znak;
            if(i%2==1){
                znak=1;
            }
            else{
                znak=-1;
            }
            //степень
            double step=2*i+1;
            double xstep=pow(x,step);
            //знаменатель
            double znamen=4*i*i-1;
            //член ряда
            double ch=znak*xstep/znamen;
            if(abs(ch)<eps){   //если член ряда очень маленький-выходим
                break;
            }
            //добавляем к сумме
            sumeps=sumeps+ch;
            i=i+1;
        }
        cout<<x<<" | "<<tochno<<" | "<<sumn<<" | "<<sumeps<<endl;
        x=x+shag;  //переходим к следующему x
    }
    return 0;
}