#include <iostream>
#include <string>
#include <fstream>
#include <windows.h> 
using namespace std;

struct Node{
    string data;
    Node*next;
};
Node*nachalo=NULL;
Node*konec=NULL;
            //создание узла
Node* sozdat(string stroka){
    Node*novie=new Node;
    novie->data=stroka;
    novie->next=NULL;
    return novie;
}

//добавление в конец
void dobavit(string stroka){
    Node*novie=sozdat(stroka);
    if(konec==NULL){
        konec=novie;
        nachalo=novie;
    }
    else{
        konec->next=novie;
        konec=novie;
    }
    cout<<stroka<<" добавлено в конец"<<endl;
}

//удаление из начала
void udalit(){
    if(nachalo==NULL){
        cout<<"очереедь пуста"<<endl;
        return;
    }
    Node*vrem=nachalo;
    string udalen=nachalo->data;
    nachalo=nachalo->next;
    if(nachalo==NULL){
        konec=NULL;
    }
    delete vrem;
    cout<<"удалено из начала- "<<udalen<<endl;
}

//печать очереди
void pechat(){
    if(nachalo==NULL){
        cout<<"очередь пуста"<<endl;
        return;
    }
    Node* tekushie=nachalo;
    int n=1;
    while(tekushie!=NULL){
        cout<<n<<" ."<<tekushie->data<<endl;
        tekushie=tekushie->next;
        n++;
    }
    cout<<"всего элементов: "<<n-1<<endl;
}

//запись в файл
void zapis(string imyafaila){
    ofstream fail(imyafaila);
    if(!fail){
        cout<<"ошибка создания файла"<<endl;
        return;
    }
    Node*tekushie=nachalo;
    int kolvo=0;
    while(tekushie!=NULL){
        fail<<tekushie->data<<endl;
        tekushie=tekushie->next;
        kolvo++;
    }
    fail.close();
    cout<<"всего записано: "<<kolvo<<" элементов в файл "<<imyafaila<<endl;
}

//уничтожение очереди
void unichtogit(){
    Node*tekushie=nachalo;
    int kolvo=0;
    while(tekushie!=NULL){
        Node*vrem=tekushie;
        tekushie=tekushie->next;
        delete vrem;
        kolvo++;
    }
    nachalo=NULL;
    konec=NULL;
    cout<<"уничтожено "<<kolvo<<" элементов"<<endl;
}

//восстановление из файла
void vosstanovlenie(string imyafaila){
    ifstream fail(imyafaila);
    if(!fail){
        cout<<"ошибка чтения файла"<<endl;
        return;
    }
    if(nachalo!=NULL){
        unichtogit();
    }
    string stroka;
    while(getline(fail,stroka)){
        dobavit(stroka);
    }
    fail.close();
    cout<<"очередь восстановлена из файла"<<imyafaila<<endl;
}

//добавление после ключа
void dobavitkluch(string kluch, string novaya){
    if(nachalo==NULL){
        cout<<"очередь пуста"<<endl;
        return;
    }
    Node*vremnachalo=NULL;
    Node*vremkonec=NULL;
    bool naiden=false;
    Node*tekushie=nachalo;
    while(tekushie!=NULL){
        if(tekushie->data==kluch && !naiden){
            naiden=true;
            Node*temp=sozdat(tekushie->data);
            if(vremkonec==NULL){
            vremnachalo=temp;
            vremkonec=temp;
            }
            else{
            vremkonec->next=temp;
            vremkonec=temp;
            }
            Node*novie=sozdat(novaya);
            vremkonec->next=novie;
            vremkonec=novie;
            cout<<"добавлено "<<novaya<<" после"<<kluch<<endl;
        }
        else{
            Node*temp=sozdat(tekushie->data);
            if(vremkonec==NULL){
                vremnachalo=temp;
                vremkonec=temp;
            }
            else{
                vremkonec->next=temp;
                vremkonec=temp;
            }
        }
        tekushie=tekushie->next;
    }
    if(!naiden){
        cout<<"ключ не найден"<<endl;
        while(vremnachalo!=NULL){
            Node*vrem=vremnachalo;
            vremnachalo=vremnachalo->next;
            delete vrem;
        }
        return;
    }
    while(nachalo!=NULL){
        Node*vrem=nachalo;
        nachalo=nachalo->next;
        delete vrem;
    }
    nachalo=vremnachalo;
    konec=vremkonec;
}

//удаление k элементов с конца
void udalitk(int k){
    if(nachalo==NULL){
        cout<<"очередь пуста"<<endl;
        return;
    }
    Node*tekushie=nachalo;
    int vsego=0;
    while(tekushie!=NULL){
        vsego++;
        tekushie=tekushie->next;
    }
    if(k>=vsego){
        unichtogit();
        cout<<"удалена вся очередь "<<vsego<<" элементов"<<endl;
        return;
    }
    int ost=vsego-k;
    tekushie=nachalo;
    for(int i=1;i<ost;i++){
        tekushie=tekushie->next;
    }
    Node*udal=tekushie->next;
    tekushie->next=NULL;
    konec=tekushie;
    int udaleno=0;
    while(udal!=NULL){
        Node*vrem=udal;
        udal=udal->next;
        delete vrem;
        udaleno++;
    }
    cout<<"удалено с конца "<<udaleno<<" элементов"<<endl;
}

int main(){
    SetConsoleCP(1251);      
    SetConsoleOutputCP(1251); 
    setlocale(LC_ALL,"Russian");
    int n,k;
    string stroka,kluch,novaya;
    cout<<"сколько строк добавить?"<<endl;
    cin>>n;
    cin.ignore();
    cout<<"введите строки: "<<endl;
    for(int i=0;i<n;i++){
        getline(cin,stroka);
        dobavit(stroka);
    }
    pechat();

    cout<<"после какого ключа добавить?"<<endl;
    getline(cin,kluch);
    cout<<"какую строку добавить?"<<endl;
    getline(cin,novaya);
    dobavitkluch(kluch,novaya);
    pechat();

    cout<<"сколько элементов удалить?"<<endl;
    cin>>k;
    udalitk(k);
    pechat();

    cout<<"ПЕЧАТЬ ОЧЕРЕДИ"<<endl;
    pechat();

    cout<<"ЗАПИСЬ В ФАЙЛ"<<endl;
    zapis("queue.txt");

    cout<<"УНИЧТОЖЕНИЕ"<<endl;
    unichtogit();
    pechat();

    cout<<"ВОССТАНОВЛЕНИЕ ИЗ ФАЙЛА"<<endl;
    vosstanovlenie("queue.txt");
    pechat();

    unichtogit();
    return 0;
}