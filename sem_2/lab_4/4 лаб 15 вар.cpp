// вариант 15
#include <iostream>
using namespace std;

int main() {
	int n;
	cin>>n;
	int* arr= new int[n];
	int nac=0;
	int d=1;
	int k;
	cout<<"исходный массив:"<<endl;
	for (int i=0;i<n;i++){
	    cin>>arr[i];
	    cout<<arr[i]<<" ";
	}
	cout<<endl;
	
	//движение вперед-назад (1)
	while (d!=0){
	    cout<<"элемент arr["<<nac<<"] = "<<arr[nac]<<endl;
	    cout<<"введите направление(1-вперед, -1-назад, 0-выход):";
	    cin>>d;
	    if(d==0){
	        break;
	    }
	    else if (d==1){
	        nac=(nac+1)%n;
	    }
	    else if (d==-1){
	        nac=(nac-1+n)%n;
	    }
	}
	cout<<"введите элемент:"<<endl;
	cin>>k;
	//массив по кольцу влево (2)
	cout<<"массив по кольцу влево:"<<endl;
	for (int i=0;i<n;i++){
	    int vr=(k-i+n)%n;
	    cout<<arr[vr]<<" ";
	}
	cout<<endl;
	
	//создаем массив без первого и последнего элемента (3)
	int newm=n-2;
	int* att= new int[newm];
	for (int i=0;i<newm;i++){
	    int vr=(k-(i+1)+n)%n;
	    att[i]=arr[vr];
	}
	cout<<"массив без первого и последнего элемента:"<<endl;
	for (int i=0;i<newm;i++){
	    cout<<att[i]<<" ";
	}
	cout<<endl;
	
	//массив по кольцу вправо (4)
	cout<<"массив по кольцу вправо:"<<endl;
	for (int i=0;i<newm;i++){
	    int vr=(k-i+newm)%newm;
	    cout<<att[vr]<<" ";
	}
	cout<<endl;
	delete[] att;
    return 0;
}



    
