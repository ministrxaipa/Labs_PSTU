#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    if (n<=2){
        cout<<"нельзя построить"<<endl;
    }
    else{
    for (int k=0;k<n;k++){
        cout<<" * ";
    }
    cout<<endl;
    for (int i=0;i<n-2;i++){
            cout<<" * ";
        
        for (int j=0;j<n-2;j++){
            cout<<"   ";
        }
        cout<<" * "<<endl;
        }
    for (int k=0;k<n;k++){
        cout<<" * ";
    }
    cout<<endl;
    }
    return 0;
}