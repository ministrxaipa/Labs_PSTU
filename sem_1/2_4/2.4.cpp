#include <iostream>
using namespace std;

int main() {
	int n;
	cin>>n;
	int sp=n/2;
	int st =1;
	if (n>3 && n%2==0){
	    cout<<"нельзя построить треугольник"<<endl;
	}
	else{
	    for (int i=0; i<(n+1)/2;i++){
	        for (int j=0;j<sp;j++){
	            cout<<" ";
	        }
	        sp --;
	        for (int j=0;j<st;j++){
	            cout<<"*";
	        }
	        st+=2;
	        cout<<endl;
	    }
	}
	return 0;
}
