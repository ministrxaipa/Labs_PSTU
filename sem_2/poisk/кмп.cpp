#include <iostream>
#include <string>
using namespace std;

void prefiks(string obraz, int pref[]){
    int m=obraz.length();
    pref[0]=0;
    int dlina=0;
    for(int i=1;i<m;i++){
        while(dlina>0 && obraz[i]!=obraz[dlina]){
            dlina=pref[dlina-1];
        }
        if(obraz[i]==obraz[dlina]){
            dlina++;
        }
        pref[i]=dlina;
    }
}

void kmp(string text, string obraz, int &pervoe, int vse[], int &kolvo){
    int n=text.length();
    int m=obraz.length();
    pervoe=-1;
    kolvo=0;
    if(m>n){
        return;
    }
    int pref[m];
    prefiks(obraz,pref);
    int j=0;
    for(int i=0;i<n;i++){
        while(j>0 && text[i]!=obraz[j]){
            j=pref[j-1];
        }
        if(text[i]==obraz[j]){
            j++;
        }
        if(j==m){
            int pozicia=i-m+1;
            vse[kolvo]=pozicia;
            kolvo++;
            if(pervoe==-1){
                pervoe=pozicia;
            }
            j=pref[j-1];
        }
    }
}

int main(){
    setlocale(LC_ALL, "Russian");
    string text, obraz;
    cout<<"введите строку: "<<endl;
    getline(cin,text);
    cout<<"что ищем: "<<endl;
    getline(cin,obraz);
    cout<<endl;
    int vsepozicii[100];
    int pervoevhoj;
    int k;
    kmp(text, obraz, pervoevhoj, vsepozicii, k);
    cout<<"поиск первого вхождения "<<endl;
    if(pervoevhoj==-1){
        cout<<"не найдено ("<<endl;
    }
    else{
        cout<<"первое вхождение на позиции: "<<pervoevhoj<<endl;
    }
    cout<<endl;
    cout<<"поиск всех вхождений"<<endl;
    if(k==0){
        cout<<"не найдено ("<<endl;
    }
    else{
        cout<<"найдено на позициях: ";
        for (int i=0;i<k;i++){
            cout<<vsepozicii[i]<<" ";
        }
        cout<<endl;
        cout<<"всего найдено: "<<k<<endl;
    }
    return 0;
}