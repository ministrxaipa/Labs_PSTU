#include <iostream>
using namespace std;

int lineyniy(int massiv[], int n, int chislo){
    for(int i=0;i<n;i++){
        if(massiv[i]==chislo){
            return i;
        }
    }
    return -1;
}

void vivod(int massiv[], int n){
    for(int i=0;i<n;i++){
        cout<<massiv[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int n;
    cout<<"Сколько чисел будет в массиве? "<<endl;
    cin>>n;
    int massiv[n];
    cout<<"введите числа"<<endl;
    for(int i=0;i<n;i++){
        cin>>massiv[i];
    }
    cout<<"массив: ";
    vivod(massiv,n);
    int k;
    cout<<"какое число искать?"<<endl;
    cin>>k;
    int rez=lineyniy(massiv,n,k);
    if(rez==-1){
        cout<<"число "<<k<<" не найдено в массиве"<<endl;
    }
    else{
        cout<<"число "<<k<<" найдено, это "<<rez+1<<" -й элемент в массиве"<<endl;
    }
    return 0;
}