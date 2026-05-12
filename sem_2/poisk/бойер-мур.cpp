#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

void tablitsa(string obraz, int smest[256]){
    int m=obraz.length();
    for(int i=0;i<256;i++){
        smest[i]=m;
    }
    for(int i=0;i<m-1;i++){
        smest[obraz[i]]=m-1-i;
    }
}

int poisk(string text, string obraz){
    int n=text.length();
    int m=obraz.length();
    if(m>n){
        return -1;
    }
    int smest[256];
    tablitsa(obraz,smest);
    int pos=0;
    while(pos<=n-m){
        int j=m-1;
        while(j>=0 && obraz[j]==text[pos+j]){
            j--;
        }
        if(j<0){
            return pos;
        }
        int sdvig=smest[text[pos+j]];
        if(sdvig<1){
            sdvig=1;
        }
        pos=pos+sdvig;
    }
    return -1;
}

int main(){
    SetConsoleCP(1251);      
    SetConsoleOutputCP(1251); 
    setlocale(LC_ALL,"Russian");
    string text,obraz;
    cout<<"введите текст: "<<endl;
    getline(cin,text);
    cout<<"что искать?"<<endl;
    getline(cin,obraz);
    int rez=poisk(text,obraz);
    if(rez==-1){
        cout<<"не найдено("<<endl;
    }
    else{
        cout<<"найдено на позиции "<<rez<<endl;
    }
    return 0;
}