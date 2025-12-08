#include <iostream>
using namespace std;
int main() {
    int n;
    cin>>n;
    if (n<=2){
        cout<<"нельзя построить"<<endl;
    }
    else{
    for (int i=1;i<=n;i++){
        for (int j=0;j<i;j++){
            cout<<"* ";
        }
        cout<<endl;
    }
    }
    return 0;
}