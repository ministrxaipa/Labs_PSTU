#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Node{
    string a;
    Node*b;
};

//создание нового узла
Node* sozdat(string s){
    Node* odin=new Node;
    odin->a=s;
    odin->b=NULL;
    return odin;
}

//добавление элемента после заданного ключа
void dobavit(Node*g, string k, string s){
    Node*t=g;
    while(t!=NULL){
        if(t->a==k){
            Node* nod=sozdat(s);
            nod->b=t->b;
            t->b=nod;
            cout<<"добавдено"<<endl;
            return;
        }
        t=t->b;
    }
    cout<<"ключ не найден("<<endl;
}

//удаление элементов с конца
void udalit(Node*&g, int k){
    if(g==NULL){
        cout<<"список пуст"<<endl;
        return;
    }
    int vsego=0;
    Node*t=g;
    while(t!=NULL){
        vsego++;
        t=t->b;
    }
    if (k>=vsego){
        t=g;
        while(t!=NULL){
            Node*v=t;
            t=t->b;
            delete v;
        }
        g=NULL;
        return;
    }
    int ost=vsego-k;
    t=g;
    for(int i=1;i<ost;i++){
        t=t->b;
    }
    Node*udal=t->b;
    t->b=NULL;
    while(udal!=NULL){
        Node*v=udal;
        udal=udal->b;
        delete v;
    }
    cout<<"удалено "<<k<<"элементов"<<endl;
}

//печать списка
void pechat(Node*g){
    if(g==NULL){
        cout<<"список пуст("<<endl;
        return;
    }
    Node*t=g;
    int n=1;
    while(t!=NULL){
        cout<<n<<". "<<t->a<<endl;
        t=t->b;
        n++;
    }
    cout<<"всего: "<<n-1<<endl;
}

//запись в файл
void zapis(Node*g, string imya){
    ofstream f(imya);
    if(!f){
        cout<<"ошибка открытий файла"<<endl;
        return;
    }
    Node*t=g;
    int c=0;
    while(t!=NULL){
        f<<t->a<<endl;
        t=t->b;
        c++;
    }
    f.close();
    cout<<c<<" строк в файле"<<endl;
}

//уничтожение списка
void unichtozh(Node*&g){
    Node* t=g;
    int c=0;
    while (t!=NULL){
        Node*v=t;
        t=t->b;
        delete v;
        c++;
    }
    g=NULL;
    cout<<"уничтожено "<<c<<" элементов"<<endl;
}

//восстановление
void vosstanov(Node*& g, string imya){
    ifstream f(imya);
    if(!f){
        cout<<"ошибка открытия файла"<<endl;
        return;
    }
    if(g!=NULL){
        unichtozh(g);
    }
    string s;
    g=NULL;
    Node*posl=NULL;
    while (getline(f,s)){
        Node*nod=sozdat(s);
        if(g==NULL){
            g=nod;
            posl=nod;
        }
        else{
            posl->b=nod;
            posl=nod;
        }
    }
    f.close();
    cout<<"восстановлено из файла"<<imya<<endl;
}

//главная функция
int main(){
    setlocale(LC_ALL,"Russian");
    Node*golova=NULL;
    string stroka, kluch;
    int kol, n;

    cout<<"SOZDANIE SPISKA"<<endl;
    cout<<"skolko strok budet?"<<endl;
    cin>>n;
    cin.ignore();
    Node*posl=NULL;
    for(int i=0;i<n;i++){
        cout<<"vvod stroki:";
        getline(cin,stroka);
        Node*nod=sozdat(stroka);
        if(golova==NULL){
            golova=nod;
            posl=nod;
        }
        else{
            posl->b=nod;
            posl=nod;
        }
    }
    cout<<"СОЗДАННЫЙ СПИСОК"<<endl;
    pechat(golova);

    cout<<"ДОБАВЛЕНИЕ ЭЛЕМЕНТА"<<endl;
    cout<<"posle kakogo kluca dobavit?"<<endl;
    getline(cin,kluch);
    cout<<"kakye stroky?"<<endl;
    getline(cin,stroka);
    dobavit(golova,kluch,stroka);
    cout<<"список после добавления"<<endl;
    pechat(golova);

    cout<<"УДАЛЕНИЕ ЭЛЕМЕНТОВ"<<endl;
    cout<<"skoka udalit?"<<endl;
    cin>>kol;
    udalit(golova,kol);
    cout<<"список после удаления"<<endl;
    pechat(golova);

    cout<<"ЗАПИСЬ В ФАЙЛ"<<endl;
    zapis(golova,"spisok.txt");

    cout<<"УНИЧТОЖЕНИЕ СПИСКА"<<endl;
    unichtozh(golova);
    cout<<"список после уничтожения"<<endl;
    pechat(golova);

    cout<<"ВОССТАНОВЛЕНИЕ"<<endl;
    vosstanov(golova,"spisok.txt");
    cout<<"восстановленный список"<<endl;
    pechat(golova);

    cout<<"ОКОНЧАТЕЛЬНОЕ УНИЧТОЖЕНИЕ"<<endl;
    unichtozh(golova);
    
    return 0;
}