// вариант 15
#include <iostream>
using namespace std;

int main() {
	int n,m;
	int max=0,k=0;
	int prop;
	cin>>n>>m;
	//выделение памяти
	int** arr= new int*[n];
	for (int i=0;i<n;i++){
	   arr[i]=new int[m];
	}
	cout<<"вывод матрицы:"<<endl;
    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>arr[i][j];
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    for (int i=0;i<m-1;i++){
        k=0;
        prop=i+1;
        for (int j=0;j<n-prop;j++){
            k=k+arr[j][i];
        }
        cout<<"сумма "<<i+1<<"-го столбца без "<<prop<<" последних элементов:"<<k<<endl;
        if (k>max){
            max=k;
        }
    }
    cout<<""<<max<<endl;
    //освыобождение памяти
    for (int i=0;i<n;i++){
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}



