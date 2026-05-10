#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node{
    string data;
    Node*next;
};

Node* verh=NULL;

//сооздание 
Node*sozdat(string stroka){
    Node*novie=new Node;
    novie->data=stroka;
    novie->next=NULL;
    return novie;
}

//добавление элемента в верх
void dobavit(string stroka){
    Node*novie=sozdat(stroka);
    if(verh==NULL){
        verh=novie;
    }
    else{
        novie->next=verh;
        verh=novie;
    }
    cout<<"добавлено: "<<stroka<<endl;
}

//удаление элемента в верху
void udalit(){
    if(verh==NULL){
        cout<<"стек пуст"<<endl;
        return;
    }
    Node*vrem=verh;
    string udalen=verh->data;
    verh=verh->next;
    delete vrem;
    cout<<"удалено"<<udalen<<endl;
}

//печать стека
void pechat(){
    if(verh==NULL){
        cout<<"стек пуст"<<endl;
        return;
    }
    Node*tekushie=verh;
    int n=1;
    cout<<"стек (сверху вниз)"<<endl;
    while(tekushie!=NULL){
        cout<<n<<". "<<tekushie->data<<endl;
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
    Node*tekushie=verh;
    int kolvo=0;
    while(tekushie!=NULL){
        fail<<tekushie->data<<endl;
        tekushie=tekushie->next;
        kolvo++;
    }
    fail.close();
    cout<<"записано "<<kolvo<<" элементов в файл "<<imyafaila<<endl;
}

//уничтожение стека
void unichtogit(){
    Node*tekushie=verh;
    int kolvo=0;
    while(tekushie!=NULL){
        Node*vremeno=tekushie;
        tekushie=tekushie->next;
        delete vremeno;
        kolvo++;
    }
    verh=NULL;
    cout<<"уничтожено "<<kolvo<<" элементов"<<endl;
}

//восстановление из файла
void vosstanovlenie(string imyafaila){
    ifstream fail(imyafaila);
    if(!fail){
        cout<<"ошибка чтения файла"<<endl;
        return;
    }
    if(verh!=NULL){
        unichtogit();
    }
    string massiv[100];
    int kolvo=0;
    string stroka;
    while(getline(fail, stroka)){
        massiv[kolvo]=stroka;
        kolvo++;
    }
    for(int i=kolvo-1;i>=0;i--){
        dobavit(massiv[i]);
    }
    fail.close();
    cout<<"восстановлено"<<kolvo<<" элементов из файла "<<imyafaila<<endl;
}

//добавление после заданного ключа
void dobavitkluch(string kluch, string novayastroka){
    if(verh==NULL){
        cout<<"стек пуст"<<endl;
        return;
    }
    Node*vspom=NULL;
    bool naiden=false;
    while(verh!=NULL){
        string tekushie=verh->data;
        udalit();
        Node*temp=sozdat(tekushie);
        temp->next=vspom;
        vspom=temp;
        if(tekushie==kluch){
            naiden=true;
            break;
        }
    }
    if(!naiden){
        cout<<"колюч не найден"<<endl;
        while(vspom!=NULL){
            dobavit(vspom->data);
            Node*vremeno=vspom;
            vspom=vspom->next;
            delete vremeno;
        }
        return;
    }
    dobavit(novayastroka);
    while(vspom!=NULL){
        dobavit(vspom->data);
        Node*vremeno=vspom;
        vspom=vspom->next;
        delete vremeno;
    }
    cout<<"добавлено "<<novayastroka<<" после ключа"<<kluch<<endl;
}

//удаление с конца
void udalitk(int k){
    if(verh==NULL){
        cout<<"стек пуст"<<endl;
        return;
    }
    Node*tekushie=verh;
    int vsego=0;
    while(tekushie!=NULL){
        vsego++;
        tekushie=tekushie->next;
    }
    if(k>=vsego){
        unichtogit();
        cout<<"удален весь стек"<<endl;
        return;
    }
    Node*vspom=NULL;
    while(verh!=NULL){
        string s=verh->data;
        udalit();
        Node*temp=sozdat(s);
        temp->next=vspom;
        vspom=temp;
    }
    int ost=vsego-k;
    Node*newverh=NULL;
    Node*posl=NULL;
    for(int i=0;i<ost;i++){
        string s=vspom->data;
        Node*vrem=vspom;
        vspom=vspom->next;
        delete vrem;
        Node* nod=sozdat(s);
        if(newverh==NULL){
            newverh=nod;
            posl=nod;
        }
        else{
            posl->next=nod;
            posl=nod;
        }
    }
    int udaleno=0;
    while(vspom!=NULL){
        Node*vremeno=vspom;
        vspom=vspom->next;
        delete vremeno;
        udaleno++;
    }
    verh=NULL;
    while(newverh!=NULL){
        dobavit(newverh->data);
        Node*vremeno=newverh;
        newverh=newverh->next;
        delete vremeno;
    }
    cout<<"удалено "<<udaleno<<" элементов с конца"<<endl;
}

int main(){
    setlocale(LC_ALL,"Russian");
    int n;
    string stroka;

    cout<<"сколько строк будет в стеке?"<<endl;
    cin>>n;
    cin.ignore();
    string massiv[100];
    cout<<"введите строки: "<<endl;
    for(int i=0;i<n;i++){
        getline(cin,stroka);
        massiv[i]=stroka;
    }
    for(int i=n-1;i>=0;i++){
        dobavit(massiv[i]);
    }
    pechat();

    string kluch, novayastroka;
    cout<<"после какого ключа добавить?"<<endl;
    getline(cin,kluch);
    cout<<"какую строку добавиьт?"<<endl;
    getline(cin,novayastroka);
    dobavitkluch(kluch,novayastroka);
    pechat();

    int k;
    cout<<"сколько элементов удалить?"<<endl;
    cin>>k;
    udalitk(k);
    pechat();

    cout<<"запись в файл"<<endl;
    zapis("11(3).txt");

    cout<<"уничтожение"<<endl;
    unichtogit();
    pechat();

    cout<<"восстановление"<<endl;
    vosstanovlenie("11(3).txt");
    pechat();

    unichtogit();
    return 0;
}














