#include <iostream>
using namespace std;
#include <cmath>

int main() {
	int n;
	float x,d,f;
	cin>>n>>x;
	d=1+x;
	f=1;
	for (int i=2;i<=n;i++){
	    f=f*i;
	    d+=(pow(x,i)/f);
	}
	cout<<d<<endl;
	return 0;
}
