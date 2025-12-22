#include <iostream>
using namespace std;
int main() {
    int n,f=1;
    cin>>n;
    int *c=&f;
    for (int i=1;i<=n;i++){
        *c*=i;
    }
    cout<<*c<<endl;
    return 0;
}