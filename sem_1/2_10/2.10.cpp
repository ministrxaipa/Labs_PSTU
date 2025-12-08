#include <iostream>
using namespace std;
int main() {
    int n, c,max;
    cout<<"введите кол-во чисел:"<<endl;
    cin>>n;
    cout<<"введите первое число:"<<endl;
    cin>>max;
    for (int i=1;i<n;i++){
        cout<<"введите следующее число:"<<endl;
        cin>>c;
        if (c>max){
            max=c;
        }
    }
    cout << "Максимальный элемент: " << max << endl;
    return 0;
}