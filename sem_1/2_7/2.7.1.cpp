#include <iostream>
using namespace std;
#include <cmath>
int main() {
    int n,k;
    cin>>n;
    k=sqrt(n);
    if (k*k!=n){
        cout<<"нельзя построить квадрат"<<endl;
    }
    else{
    for (int i=0;i<k;i++){
        for (int j=0;j<k;j++){
            cout<<" * ";
        }
        cout<<endl;
    }
    }
    return 0;
}