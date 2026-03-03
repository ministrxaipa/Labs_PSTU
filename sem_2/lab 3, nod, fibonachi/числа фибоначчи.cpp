#include <iostream>
using namespace std;

int fibonachi (int n){
    if (n<=1){
        return 0;
    }
    else if (n==2){
        return 1;
    }
    return fibonachi(n-2)+fibonachi(n-1);
}

int main() {
    int a;
    cin>>a;
	for (int i=1;i<=a;i++){
	    cout<<fibonachi(i)<<" ";
	}
	return 0;
}






