#include <iostream>
using namespace std;

int main() {
	int const n=9;
	int a[n]={},max,min;
	for (int i=0;i<n;i++){
	    cin>>a[i];
	}
	max=a[0];
	min=a[0];
	for (int i=0;i<n;i++){
	    if (a[i]>max){
	        max=a[i];
	    }
	    if (a[i]<min){
	        min=a[i];
	    }
	}
	cout<<"максимальный элемент: "<<max<<endl;
	cout<<"минимальный элемент: "<<min<<endl;
	return 0;
}
