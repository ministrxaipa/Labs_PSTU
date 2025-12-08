#include <iostream>
using namespace std;
int main() {
    int n, c,max,min,sum=0;
    cin>>n;
    cin>>c;
    max=c;
    min=c;
    for(int i=1;i<n;i++){
        cin>>c;
        if(c>max){
            max=c;
        }
        else if (c<min){
            min=c;
        }
    }
    sum=min+max;
    cout<<sum<<endl;
    return 0;
}