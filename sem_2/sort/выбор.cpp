#include <iostream>
using namespace std;

int main() {
	const int n=9;
	int arr[n]={6,3,8,9,6,8,2,5,7};
	int tmp, min;
	for (int i=0;i<n;i++){
	    cout<<arr[i]<<" ";
	}
	cout<<endl;
	for (int i=0;i<n-1;i++){
	    min=i;
	    for(int j=i+1;j<n;j++){
	        if (arr[j]<arr[min]){
	            min=j;
	        }
	    }
	   tmp=arr[min];
	   arr[min]=arr[i];
	   arr[i]=tmp;
	        
	    
	}
	for (int i=0;i<n;i++){
	    cout<<arr[i]<<" ";
	}
    cout<<endl;
    return 0;
}
