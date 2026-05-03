#include <iostream>
#include <string>
using namespace std;

int main(){
    setlocale(LC_ALL,"Russia");
    string text;
    string poisk;
    cout<<"введите строку: "<<endl;
    getline(cin, text);
    cout<<"что ищем: "<<endl;
    getline(cin, poisk);
    cout<<endl;
    
    //первое вхождение
    int pervoe=-1;
    for(int i=0;i<=text.length()-poisk.length();i++){
        bool ok=true;
        for(int j=0;j<poisk.length();j++){
            if(text[i+j] != poisk[j]){
                ok=false;
                break;
            }
        }
        if (ok==true){
            pervoe=i;
            break;
        }
    }
    if(pervoe==-1){
        cout<<"не найдуно ("<<endl;
    }
    else{
        cout<<"найдено на позиции "<<pervoe<<endl;
    }
    cout<<endl;

    //все вхождения
    if(poisk.length()>text.length()){
        cout<<"искомое длиннее текста"<<endl;
    }
    else{
        cout<<"найдено на позициях: "<<endl;
        int k=0;
        for(int i=0;i<=text.length()-poisk.length();i++){
            bool ok=true;
            for(int j=0;j<poisk.length();j++){
                if(text[i+j]!=poisk[j]){
                    ok=false;
                    break;
                }
            }
            if (ok==true){
                cout<<i<<" ";
                k++;
            }
        }
        cout<<endl;
        if(k==0){
            cout<<"ничего не нашли ("<<endl;
        }
        else{
            cout<<"всего нашли: "<<k<<" штук"<<endl;
        }
    }
    return 0;
}