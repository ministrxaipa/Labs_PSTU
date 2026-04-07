#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Car{
    string mark;
    int god;
    float cena;
    string cvet;
};

//формирование файла
void SozdatFail (char imayFaila[]){
    ofstream otkritFail(imayFaila, ios::binary);
    if(!otkritFail){
        cout<<"ОШИБКА"<<endl;
        return;
    }
    int kolvo;
    cout<<"сколько машин?"<<endl;
    cin>>kolvo;
    cin.ignore();
    for(int i=0;i<kolvo;i++){
        Car mashina;
        cout<<"машина "<<i+1<<": "<<endl;
        cout<<"марка: ";
        getline(cin,mashina.mark);
        cout<<"год: ";
        cin>>mashina.god;
        cout<<"цена: ";
        cin>>mashina.cena;
        cout<<"цвет: ";
        cin.ignore();
        getline(cin,mashina.cvet);

        otkritFail.write((char*)&mashina,sizeof(Car));
        if(!otkritFail){
            cout<<"ОШИБКА"<<endl;
            otkritFail.close();
            return;
        }
    }
    otkritFail.close();
    cout<<"файл создан"<<endl;
}

//печать файла
void PechatFaila(char imayFaila[]){
    ifstream chtenie(imayFaila, ios::binary);
    if(!chtenie){
        cout<<"ОШИБКА"<<endl;
        return;
    }
    Car mashina;
    int nomer=1;
    cout<<"Список авто"<<endl;
    while(chtenie.read((char*)&mashina, sizeof(Car))){
        cout<<nomer<<", "<<mashina.mark<<", "<<mashina.god<<"г. , "<<mashina.cena<<"руб. , "<<mashina.cvet<<endl;
        nomer++;
    }
    cout<<endl;
    chtenie.close();
}

//поиск удаление
bool NuzhnoUdalit(Car mashina, int minimalniyGod){
   if(mashina.god<minimalniyGod){
    return true;
   }
   else{
    return false;
   } 
}    

//поиск добавления
bool Dobavit(Car mashina){
    if(mashina.mark.empty()|| mashina.cvet.empty()){
        cout<<"ОШИБКА"<<endl;
        return false;
    }
    if(mashina.god<1886||mashina.god>2026){
        cout<<"ОШИБКА"<<endl;
        return false;
    }
    if(mashina.cena<0){
        cout<<"ошибка"<<endl;
        return false;
    }
    return true;
}

void Udalit(char imayFaila[], int minimalniyGod){    
    ifstream chtenie(imayFaila, ios::binary);
    if(!chtenie){
        cout<<"ОШИБКА"<<endl;
        return;
    }
    ofstream vremeno("temp.dat",ios::binary);
    if(!vremeno){
        cout<<"ОШИБКА"<<endl;
        chtenie.close();
        return;
    }
    Car mashina;
    int udaleno=0;

    while (chtenie.read((char*)&mashina,sizeof(Car))){
        if(!NuzhnoUdalit(mashina, minimalniyGod)){
            vremeno.write((char*)&mashina,sizeof(Car));
            if(!vremeno){
                cout<<"ОШИБКА"<<endl;
                chtenie.close();
                vremeno.close();
                return;
            }
        }
        else{
            udaleno++;
        }
    }
    chtenie.close();
    vremeno.close();

    if (remove (imayFaila)!=0){
        cout<<"ОШИБКА"<<endl;
        return;
    }
    if(rename("temp.dat",imayFaila)!=0){
        cout<<"ОШИБКА"<<endl;
        return;
    }
    cout<<"Удалено автомобидей: "<<udaleno<<endl;
}

//добавление в начало
void DobavNach(char imayFaila[]){
    ifstream chtenie(imayFaila, ios::binary);
    if(!chtenie){
        cout<<"ОШИБКА"<<endl;
        return;
    }
    ofstream vremeno("temp.dat", ios::binary);
    if(!vremeno){
        cout<<"ОШИБКА"<<endl;
        chtenie.close();
        return;
    }

    Car novaia;
    cin.ignore();
    cout<<"марка: ";
    getline(cin, novaia.mark);
    cout<<"год: ";
    cin>>novaia.god;
    cout<<"цена: ";
    cin>>novaia.cena;
    cin.ignore();
    getline(cin,novaia.cvet);

    if(Dobavit(novaia)){
        vremeno.write((char*)&novaia, sizeof(Car));
        if(!vremeno){
            cout<<"ОШИБКА"<<endl;
            chtenie.close();
            vremeno.close();
            return;
        }

        Car starie;
        while(chtenie.read((char*)&starie, sizeof(Car))){
            vremeno.write((char*)&starie, sizeof(Car));

            if(!vremeno){
                cout<<"ОШИБКА"<<endl;
                chtenie.close();
                vremeno.close();
                return;
            }
        }
    }
    else{
        cout<<"автомобиль не добавлен"<<endl;
        chtenie.close();
        vremeno.close();
        return;
    }
    chtenie.close();
    vremeno.close();

    if(remove(imayFaila)!=0){
        cout<<"ОШИБКА"<<endl;
        return;
    }
    if(rename("temp.dat",imayFaila)!=0){
        cout<<"ОШИБКА"<<endl;
        return;
    }
    cout<<"автомобиль добавлен"<<endl;
}

int main(){
    char imayFaila[]="auto.dat";

    int vibor;
    int minimalniyGod;
    while(true){
        cout<<"1- записать автомобили"<<endl;
        cout<<"2- показать файл"<<endl;
        cout<<"3- удалить автомобили"<<endl;
        cout<<"4- добавить автомобиль"<<endl;
        cout<<"0- выход"<<endl;
        cin>>vibor;

        if(vibor==0){
            cout<<"пока пока :("<<endl;
            break;
        }
        else if(vibor==1){
            SozdatFail(imayFaila);
        }
        else if(vibor==2){
            PechatFaila(imayFaila);
        }
        else if(vibor==3){
            cin>>minimalniyGod;
            Udalit(imayFaila, minimalniyGod);
            cout<<"результат: "<<endl;
            PechatFaila(imayFaila);
        }
        else if(vibor==4){
            DobavNach(imayFaila);
            cout<<"результат:"<<endl;
            PechatFaila(imayFaila);
        }
        else{
            cout<<"ОШИБКА"<<endl;
        }
    }
    return 0;
}
