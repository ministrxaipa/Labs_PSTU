//вариант 15
#include <iostream>
#include <cmath>
using namespace std;
//а
int stepen (int chislo, int stepen){
    int o=1;
    for (int i=0;i<stepen;i++){
        o*=chislo;
    }
    return o;
}
//б
double koren(double chislo, int koren){
    double o= pow(chislo, 1.0/koren);
    return o;
}

int main() {
    int h;
    cout<<"выберите, что сделать (1- возведение в степень, 2-извлечь корень из десятичного числа:"<<endl;
    cin>>h;
	if (h==1){
	    int n,c;
	    cout<<"введите число:"<<endl;;
	    cin>>n;
	    cout<<"введите степень:"<<endl;
	    cin>>c;
	    int rez=stepen(n,c);
	    cout<<"число: "<<n<<" в степени: "<<c<<" = "<<rez<<endl;
	}
	else if (h==2){
	    double n;
	    int k;
	    cout<<"введите число: "<<endl;
	    cin>>n;
	    cout<<"введите степень: "<<endl;
	    cin>>k;
	    double rez= koren(n,k);
	    cout<<"корень: "<<k<<" степень: "<<n<<" = "<<rez<<endl;
	    
	}
	else{
	    cout<<"неправильное число"<<endl;
	}
    return 0;
}


