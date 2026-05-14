#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//создание файла
void sozdat(string imyafaila, int kolvo){
    ofstream fzapis(imyafaila);
    cout<<"введите "<<kolvo<<" чисел:"<<endl;
    for(int i=0;i<kolvo;i++){
        int k;
        cin>>k;
        fzapis<<k<<" ";
    }
    fzapis.close();
    cout<<imyafaila<<" создан"<<endl;
}

//печать файла
void pechat(string imyafaila){
    ifstream fchtenie(imyafaila);
    int k;
    cout<<"содержимое "<<imyafaila<<":";
    while(fchtenie>>k){
        cout<<k<<" ";
    }
    cout<<endl;
    fchtenie.close();
}

//разбиваем на серии
void serii(string fvhod, string f1, string f2){
    ifstream failvhod(fvhod);
    ofstream fail1(f1);
    ofstream fail2(f2);
    int tekushie, predydushie;
    bool pervie=true;
    if(!(failvhod>>predydushie)){
        failvhod.close();
        fail1.close();
        fail2.close();
        return;
    }
    fail1<<predydushie<<" ";
    while(failvhod>>tekushie){
        if(tekushie<predydushie){
            pervie=!pervie;
        }
        if(pervie==true){
            fail1<<tekushie<<" ";
        }
        else{
            fail2<<tekushie<<" ";
        }
        predydushie=tekushie;
    }
    failvhod.close();
    fail1.close();
    fail2.close();
}

//сливаем 2 файла в 1
void slit(string fistok1, string fistok2, string frez){
    ifstream f1(fistok1);
    ifstream f2(fistok2);
    ofstream rez(frez);
    int k1,k2;
    if(!(f1>>k1)){
        while(f2>>k2){
            rez<<k2<<" ";
        }
        f1.close();
        f2.close();
        rez.close();
        return;
    }
    if(!(f2>>k2)){
        rez<<k1<<" ";
        while(f1>>k1){
            rez<<k1<<" ";
        }
        f1.close();
        f2.close();
        rez.close();
        return;
    }
    while(true){
        if(k1<k2){
            rez<<k1<<" ";
            if(!(f1>>k1)){
                rez<<k2<<" ";
                while(f2>>k2){
                    rez<<k2<<" ";
                }
                break;
            }
        }
        else{
            rez<<k2<<" ";
            if(!(f2>>k2)){
                rez<<k1<<" ";
                while(f1>>k1){
                    rez<<k1<<" ";
                }
                break;
            }
        }
    }
    f1.close();
    f2.close();
    rez.close();
}

//проверка
bool proverka(string imyafaila){
    ifstream f(imyafaila);
    int pred,tek;
    if(!(f>>pred)){
        f.close();
        return true;
    }
    while(f>>tek){
        if(tek<pred){
            f.close();
            return false;
        }
        pred=tek;
    }
    f.close();
    return true;
}

int main(){
    setlocale(LC_ALL,"Russian");
    string failishodni="естественная.txt";
    string fvremeno1="f1.txt";
    string fvremeno2="f2.txt";
    string fvremeno3="f3.txt";
    int kolvo;
    cout<<"сколько чисел будет?"<<endl;
    cin>>kolvo;
    sozdat(failishodni,kolvo);
    cout<<"исходный файл:"<<endl;
    pechat(failishodni);
    int p=1;
    while(!proverka(failishodni)){
        serii(failishodni,fvremeno1,fvremeno2);
        cout<<"f1.tzt:";
        pechat(fvremeno1);
        cout<<"f2.txt:";
        pechat(fvremeno2);
        slit(fvremeno1,fvremeno2,fvremeno3);
        cout<<"после слияния:";
        pechat(fvremeno3);
    
    
        ifstream f3(fvremeno3);
        ofstream f(failishodni);
        int k;
        while(f3>>k){
            f<<k<<" ";
        }
        f.close();
        f3.close();
        p++;
        if(p>50){
            break;
        }
    }
    cout<<"отсортированный файл:"<<endl;
    pechat(failishodni);
    return 0;
}