#include <iostream>
using namespace std;

int main() {
	const int n=3,m=3;
	int arr[n][m]={};
	for (int i=0;i<n;i++){
	    for (int j=0;j<m;j++){
	        cin>>arr[i][j];
	    }
	    cout<<endl;
	}
	for (int i=0;i<n;i++){
	    for (int j=0;j<m;j++){
	        cout<<arr[i][j]<<" ";
	    }
	    cout<<endl;
	}
	cout<<"перевернутая:"<<endl;
	for (int i=0;i<n;i++){
	    for (int j=0;j<m;j++){
	        cout<<arr[j][i]<<" ";
	    }
	    cout<<endl;
	}
	return 0;
}
