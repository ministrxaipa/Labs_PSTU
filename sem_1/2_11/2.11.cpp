#include <iostream>
using namespace std;

int main() {
	int n,k;
	cin>>n;
	bool plus=false;
	bool minus=false;
	for (int i=1;i<=n;i++){
	    cin>>k;
	    if (!plus && !minus){
	        if (k>0){
	            plus=true;
	        }
	        else{
	            minus=true;
	        }
	    }
	}
	if (plus==true){
	    cout<<"сначала ввели положительное число";
	}
	else if (minus==true){
	    cout<<"сначала ввели отрицательное число";
	}
	else{
	    cout<<"все элементы были нулевыми";
	}
	cout<<endl;
    return 0;
}
