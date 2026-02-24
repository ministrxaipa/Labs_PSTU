#include <iostream>
using namespace std;

int main() {
	const int n=8;
	int k;
	int arr[n]={7,4,9,6,8,3,5,1};
	for(int i=0;i<n;i++){
	    cout<<arr[i]<<" ";
	}
	cout<<endl;
	for (int i=1;i<n;i++){
	    k=arr[i];
	    int j=i-1;
	    while (j>=0 && arr[j]>k){
	        arr[j+1]=arr[j];
	        j--;
	    }
	    arr[j+1]=k;
	}
	for (int i=0;i<n;i++){
	    cout<<arr[i]<<" ";
	}
	cout<<endl;
	return 0;
}
