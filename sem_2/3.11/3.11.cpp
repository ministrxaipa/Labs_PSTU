#include <iostream>
using namespace std;

int main() {
	const int n=3,m=3;
	int arr[n][m]={};
	int k=0;
	for (int i=0;i<n;i++){
	    for (int j=0;j<m;j++){
	        cin>>arr[i][j];
	    }
	    cout<<endl;
	}
	for (int i=0;i<n;i++){
	    for(int j=0;j<m;j++){
	        if (i==j){
	            arr[i][j]=k;
	        }
	        cout<<arr[i][j]<<" ";
	    }
	    cout<<endl;
	}
	cout<<endl;
	return 0;
}
