#include <iostream>
using namespace std;

int main() {
    int n;
    cin>>n;
    if (n>2){
        for (int i=0;i<n;i++){
            for (int j=1;j<=n-i;j++){
                cout<<" ";
            }
            for (int k=0;k<=i;k++){
                cout<<"*";
            }
            cout<<endl;
        }
    }
    else{
        cout<<"нельзя построить треугольник";
    }
    return 0;
}