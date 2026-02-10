#include <iostream>
using namespace std;

int main() {
	const int n=7;
	int arr[n];
	for (int i=0;i<n;i++){
	    cin>>arr[i];
	}
	cout<<"исходный массив:";
	for (int i=0;i<n;i++){
	    cout<<arr[i]<<" ";
	}
	cout<<endl;
	cout<<"перевернутый массив:";
	for (int i=n-1;i>=0;i--){
	    cout<<arr[i]<<" ";
	}
	cout<<endl;
	return 0;
}
