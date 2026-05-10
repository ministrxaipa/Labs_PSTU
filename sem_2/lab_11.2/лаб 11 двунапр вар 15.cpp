#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Node{
    string data;
    Node* next;
    Node* prev;
};

//создание узла
Node* sozdat(string stroka){
    Node*novie=new Node;
    novie->data=stroka;
    novie->next=NULL;
    novie->prev=NULL;
    return novie;
}

//добавление после заданного ключа
void dobavit(Node*&golova,string kluch,string novayaStroka){
    if(golova==NULL){
        cout<<"список пуст("<<endl;
        return;
    }
    Node*tekushie=golova;
    while(tekushie!=NULL){
        if(tekushie->data==kluch){
            Node*novie=sozdat(novayaStroka);
            novie->next=tekushie->next;
            novie->prev=tekushie;
            if(tekushie->next!=NULL){
                tekushie->next->prev=novie;
            }
            tekushie->next=novie;
            cout<<"добавлено после элемента "<<kluch<<endl;
            return;
        }
        tekushie=tekushie->next;
    }
    cout<<"ключ "<<kluch<<"не найден("<<endl;
}

//удаление элементов с конца
void udalit(Node*&golova, int k){
    if(golova==NULL){
        cout<<"список пуст("<<endl;
        return;
    }
    int vsego=0;
    Node*tekushie=golova;
    while(tekushie!=NULL){
        vsego++;
        tekushie=tekushie->next;
    }
    if(k>=vsego){
        tekushie=golova;
        while(tekushie!=NULL){
            Node*vremeno=tekushie;
            tekushie=tekushie->next;
            delete vremeno;
        }
        golova=NULL;
        cout<<"удалено "<<vsego<<" элементов"<<endl;
        return;
    }
    int ost=vsego-k;
    Node*newposledniy=golova;
    for(int i=1;i<ost;i++){
        newposledniy=newposledniy->next;
    }
    Node*udalaem=newposledniy->next;
    newposledniy->next=NULL;
    int udaleno=0;
    while(udalaem!=NULL){
        Node*vremeno=udalaem;
        udalaem=udalaem->next;
        delete vremeno;
        udaleno++;
    }
    cout<<"удалено "<<udaleno<<" элементов с конца"<<endl;
}

//печать списка
void pechat(Node*golova){
    if(golova==NULL){
        cout<<"список пуст"<<endl;
        return;
    }
    Node*tekushie=golova;
    int n=1;
    while(tekushie!=NULL){
        cout<<n<<". "<<tekushie->data<<endl;
        tekushie=tekushie->next;
        n++;
    }
    cout<<"всего элементов: "<<n-1<<endl;
}

//запись списка в файл
void zapis(Node*golova, string imyafaila){
    ofstream fail(imyafaila);
    if (!fail){
        cout<<"ошибка создания файла"<<endl;
        return;
    }
    Node*tekushie=golova;
    int kolvo=0;
    while(tekushie!=NULL){
        fail<<tekushie->data<<endl;
        tekushie=tekushie->next;
        kolvo++;
    }
    fail.close();
    cout<<"записано "<<kolvo<<" эдементов в файл "<<imyafaila<<endl;
}

//уничтожение списка
void unichtogit(Node*&golova){
    Node*tekushie=golova;
    int kolvo=0;
    while(tekushie!=NULL){
        Node*vremeno=tekushie;
        tekushie=tekushie->next;
        delete vremeno;
        kolvo++;
    }
    golova=NULL;
    cout<<"уничтожено "<<kolvo<<" элементов"<<endl;
}

//восстановление
void vosstanovlenie(Node*&golova, string imyafaila){
    ifstream fail(imyafaila);
    if(!fail){
        cout<<"ошибка открытия файла"<<endl;
        return;
    }
    if(golova!=NULL){
        unichtogit(golova);
    }
    string stroka;
    Node*posledniy=NULL;
    while(getline(fail, stroka)){
        Node*novie=sozdat(stroka);
        if(golova==NULL){
            golova=novie;
            posledniy=novie;
        }
        else{
            posledniy->next=novie;
            novie->prev=posledniy;
            posledniy=novie;
        }
    }
    fail.close();
    cout<<"список восстановлен)"<<endl;
}

int main(){
    setlocale(LC_ALL,"Russian");
    Node*golova=NULL;
    string stroka,kluch;
    int n,k;

    cout<<"сколько строк будет?"<<endl;
    cin>>n;
    cin.ignore();
    Node*posledniy=NULL;
    cout<<"введите строки: "<<endl;
    for(int i=0;i<n;i++){
        getline(cin,stroka);
        Node*novie=sozdat(stroka);
        if(golova==NULL){
            golova=novie;
            posledniy=novie;
        }
        else{
            posledniy->next=novie;
            novie->prev=posledniy;
            posledniy=novie;
        }
    }
    cout<<"список создан: "<<endl;
    pechat(golova);

    cout<<"после какого ключа добавить?"<<endl;
    getline(cin,kluch);
    cout<<"какую строку добавть?"<<endl;
    getline(cin,stroka);
    dobavit(golova,kluch,stroka);
    cout<<"список после добавления: "<<endl;
    pechat(golova);

    cout<<"сколько удалить?"<<endl;
    cin>>k;
    udalit(golova,k);
    cout<<"список после удаления: "<<endl;
    pechat(golova);

    zapis(golova,"11(2).txt");

    unichtogit(golova);
    cout<<"список после уничтожения: "<<endl;
    pechat(golova);

    vosstanovlenie(golova,"11(2).txt");
    cout<<"список после восстановления: "<<endl;
    pechat(golova);

    unichtogit(golova);
    return 0;
}







