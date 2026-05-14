#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//создание файла с числами
void sozdatfail(string imyafaila, int kolvo){
    ofstream fzapis(imyafaila);
    cout<<"введите "<<kolvo<<" чисел:"<<endl;
    for(int i=0;i<kolvo;i++){
        int k;cin>>k;
        fzapis<<k<<" ";
    }
    fzapis.close();
    cout<<imyafaila<<" создан"<<endl;
}

//показать файл
void pechat(string imyafaila){
    ifstream fchtenie(imyafaila);
    int k;
    cout<<"содержимое "<<imyafaila<<" :";
    while(fchtenie>>k){
        cout<<k<<" ";
    }
    cout<<endl;
    fchtenie.close();
}

//разбиваем на два файла
void razbit(string imyafaila, string frez1, string frez2){
    ifstream fvhod(imyafaila);
    ofstream fvihod1(frez1);
    ofstream fvihod2(frez2);
    int massiv[100];
    int kolvo=0;
    while (fvhod>>massiv[kolvo]){
        kolvo++;
    }
    fvhod.close();
    int seredina=kolvo/2;
    for(int i=0;i<seredina;i++){
        fvihod1<<massiv[i]<<" ";
    }
    for(int i=seredina;i<kolvo;i++){
        fvihod2<<massiv[i]<<" ";
    }
    fvihod1.close();
    fvihod2.close();
}

//сортировка пузырьком
void sortirovka(string imyafaila){
    int massiv[100];
    int kolvo=0;
    ifstream fchtenie(imyafaila);
    while(fchtenie>>massiv[kolvo]){
        kolvo++;
    }
    fchtenie.close();
    for(int i=0;i<kolvo-1;i++){
        for(int j=0;j<kolvo-1-i;j++){
            if(massiv[j]>massiv[j+1]){
                int vrem=massiv[j];
                massiv[j]=massiv[j+1];
                massiv[j+1]=vrem;
            }
        }
    }
    ofstream fzapis(imyafaila);
    for(int i=0;i<kolvo;i++){
        fzapis<<massiv[i]<<" ";
    }
    fzapis.close();
}

//сливаем 2 отсортированных в один
void slit(string f1, string f2, string frez){
    ifstream fvhod1(f1);
    ifstream fvhod2(f2);
    ofstream fvihod(frez);
    int k1, k2;
    if (!(fvhod1 >> k1)){
        return;
    }
    if (!(fvhod2 >> k2)){
        return;
    }
    while (true) {
        if (k1 < k2) {
            fvihod << k1 << " ";
            if (!(fvhod1 >> k1)){
                break;
            }
        } 
        else {
            fvihod << k2 << " ";
            if (!(fvhod2 >> k2)){
                break;
            }
        }
    }
    fvihod << k1 << " ";
    while (fvhod1 >> k1){
        fvihod << k1 << " ";
    }
    fvihod << k2 << " ";
    while (fvhod2 >> k2){
        fvihod << k2 << " ";
    }
    fvhod1.close();
    fvhod2.close();
    fvihod.close();
}

int main(){
    setlocale(LC_ALL,"Russian");
    string failishodni="chisla.txt";
    string fvremeno1="f1.txt";
    string fvremeno2="f2.txt";
    string fvremeno3="f3.txt";
    int kolvo,k;
    cout<<"сколько чисел будет?"<<endl;
    cin>>kolvo;
    sozdatfail(failishodni,kolvo);
    cout<<"исходный файл:"<<endl;
    pechat(failishodni);
    razbit(failishodni, fvremeno1, fvremeno2);
    cout<<"сортируем первый файл:"<<endl;
    sortirovka(fvremeno1);
    pechat(fvremeno1);
    cout<<"сортируем второй файл:"<<endl;
    sortirovka(fvremeno2);
    pechat(fvremeno2);
    slit(fvremeno1, fvremeno2, fvremeno3);
    ifstream f1(fvremeno3);
    ofstream f2(failishodni);
    while(f1>>k){
        f2<<k<<" ";
    }
    f1.close();
    f2.close();
    cout<<"отсортированный файл:"<<endl;
    pechat(failishodni);
    return 0;
}
