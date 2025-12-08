#include <iostream>
using namespace std;

int main() {
	int n, t, sum=0;
	cin>>n;
	for (int i=1;i<=n;i++){
	    t=1;
	    for (int j=i;j<=2*i;j++){
	        t*=j;
	    }
	    sum+=t;
	}
	cout<<sum<<endl;
	return 0;
}
