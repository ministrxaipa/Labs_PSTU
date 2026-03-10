// вариант 15
#include <iostream>
using namespace std;

int main() {
	int n,m,max,stolb,stroka;
	//1 вводим размер
	cin>>n>>m;
	//2 сформировываем массив
	int**arr=new int*[n];
	for(int i=0;i<n;i++){
	    arr[i]=new int[m];
	}
	//3 заполняем массив
	cout<<"исходный массив: "<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>arr[i][j];
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    max=arr[0][0];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if (arr[i][j]>max){
                max=arr[i][j];
                stolb=j;
                stroka=i;
            }
        }
    }
    cout<<"максимальный элемент: "<<max<<endl<<"столбец: "<<stolb+1<<endl<<"строка: "<<stroka+1<<endl;
    
    int newn=n-1;
    int newm=m-1;
    int** newarr=new int*[newn];
    for(int i=0;i<newn;i++){
        newarr[i]= new int[newm];
    }
    for (int i=0, ni=0;i<n;i++){
        if (i==stroka){
            continue;
        }
        for (int j=0, mj=0;j<m;j++){
            if (j==stolb){
                continue;
            }
            newarr[ni][mj]=arr[i][j];
            mj++;
        }
        ni++;
    }
    //5 печатаем новый массив
    cout<<"новый массив: "<<endl;
    for (int i=0;i<newn;i++){
        for(int j=0;j<newm;j++){
            cout<<newarr[i][j]<<" ";
        }
        cout<<endl;
    }
    //6 удаляем массив
    for (int i=0;i<n;i++){
        delete[] arr[i];
    }
    delete[] arr;
    for (int i=0;i<newn;i++){
        delete[] newarr[i];
    }
    delete[] newarr;
    return 0;
}
