#include <iostream>
using namespace std;

int main() {
	int n,s;
	bool j=false;
	cin>>n;
	cin>>s;
	while (n>0 && !j){
	    int d=n%10;
	    if (d==s){
	        j=true;
	        cout<<"цифра найдена"<<endl;
	    }
	    else {
	        n=n/10;
	    }
	}
	if (j==false){
	    cout<<"цифра не найдена"<<endl;
	}
	return 0;
}
