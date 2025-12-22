
#include <iostream>
using namespace std;
#include <cmath>
int main(){
    float n,s,a;
    int i=1;
    bool fg =false;
    cin>>n>>s;
    while (i<=n && !fg){
        a=sin(n+i/n);
        a=round(a*10)/10;
        cout<<n+i/n<<"|"<<a<<endl;
        if (a==s){
            fg=true;
        }
        else {
            i++;
        }
    }
    if (fg==true){
        cout<<"Элемент найден"<<endl;
    }
    else{
        cout<<"Элемент не найден"<<endl;
    }
    return 0;
}