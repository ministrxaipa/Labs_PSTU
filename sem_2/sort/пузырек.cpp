#include <iostream>
using namespace std;

int main() {
	const int n=9;
	int arr[n]={6,3,8,9,6,8,2,5,7};
	int tmp;
	for (int i=0;i<n;i++){
	    cout<<arr[i]<<" ";
	}
	cout<<endl;
	for (int i=0;i<n-1;i++){
	    for(int j=0;j<n-i-1;j++){
	        if (arr[j]>arr[j+1]){
	            tmp=arr[j];
	            arr[j]=arr[j+1];
	            arr[j+1]=tmp;
	        }
	    }
	}
	for (int i=0;i<n;i++){
	    cout<<arr[i]<<" ";
	}
    cout<<endl;
    return 0;
}
