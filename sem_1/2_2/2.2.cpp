#include <iostream>
using namespace std;

int main() {
    int n, pr=1;
    cin>>n;
    if (n<=0){
        cout<<"нельзя посчитать";
    }
    else{
        for (int i=1;i<=n;i++){
            pr*=i;
        }
    }
    cout<<pr<<endl;
    return 0;
}
