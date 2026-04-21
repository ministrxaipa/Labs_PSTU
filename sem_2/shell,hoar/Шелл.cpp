#include <iostream>
using namespace std;

void shell(int massiv[], int razmer){
    for(int gap=razmer/2; gap>0; gap/=2){
        for(int i=gap;i<razmer;i++){
            int temp=massiv[i];
            int j=i;

            while(j>=gap && massiv[j-gap]>temp){
                massiv[j]=massiv[j-gap];
                j-=gap;
            }
            massiv[j]=temp;
        }
    }
}

void vivod(int massiv[], int razmer){
    for(int i=0;i<razmer;i++){
        cout<<massiv[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int massiv[]={7,2,1,6,8,5,3,4};
    int razmer=sizeof(massiv)/sizeof(massiv[0]);
    cout<<"исходный: ";
    vivod(massiv,razmer);
    shell(massiv,razmer);
    cout<<"результат: ";
    vivod(massiv,razmer);
    return 0;
}