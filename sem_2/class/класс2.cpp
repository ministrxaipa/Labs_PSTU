#include <iostream>
#include <string>
using namespace std;

//пользовательский класс
class zarplata{
    private:
        string FIO;
        double oklad;
        int premia;
    public:
        //конструктор без параметров
        zarplata(){
            FIO="не известно";
            oklad=0;
            premia=0;
        }
        //конструктор с параметрами
        zarplata(string f,double o, int p){
            FIO=f;
            oklad=o;
            premia=p;
        }
        //конструктор копирования
        zarplata(const zarplata &original){
            FIO=original.FIO;
            oklad=original.oklad;
            premia=original.premia;
        }
        //деструктор
        ~zarplata(){
            cout<<"сработал деструктор для: "<<FIO<<endl;
        }
        //селекторы
        string getFIO(){
            return FIO;
        }
        double getoklad(){
            return oklad;
        }
        int getpremia(){
            return premia;
        }
        //модификаторы
        void setFIO(string f){
            FIO=f;
        }
        void setoklad(double o){
            oklad=o;
        }
        void setpremia(int p){
            premia=p;
        }
};

zarplata vremeno(){
    zarplata temp("временно",30000,10);
    cout<<"Возвращаем temp из функции"<<endl;
    return temp;
}

void kopirka(zarplata kopia){
    cout<<"ФИО у копии: "<<kopia.getFIO()<<endl;
}

int main(){
    setlocale(LC_ALL,"Russian");
    string fio;
    double oklad;
    int premia;
    //конструктор без парметров
    zarplata obj1;
    cout<<"ФИО: "<<obj1.getFIO()<<endl;
    cout<<"оклад: "<<obj1.getoklad()<<endl;
    cout<<"премия: "<<obj1.getpremia()<<endl;
    //конструктор с параметрами
    cout<<"введите фио: "<<endl;
    cin.ignore();
    getline(cin,fio);
    cout<<"введите оклад:"<<endl;
    cin>>oklad;
    cout<<"введите премию:"<<endl;
    cin>>premia;
    zarplata obj2(fio,oklad,premia);
    cout<<"ФИО: "<<obj2.getFIO()<<endl;
    cout<<"оклад: "<<obj2.getoklad()<<endl;
    cout<<"премия: "<<obj2.getpremia()<<endl;
    //конструктор копирования
    zarplata obj3=obj2;
    cout<<"фио как у obj2: "<<obj3.getFIO()<<endl;
    kopirka(obj2);
    zarplata obj4=vremeno();
    cout<<"Получили obj4 с ФИО: "<< obj4.getFIO()<<endl;
    //модификаторы
    cout<<"Было у obj1: "<<obj1.getFIO()<<", "<<obj1.getoklad()<<", "<<obj1.getpremia()<<endl;
    cout<<"Введите новые данные для obj1:"<<endl;
    cout<<"Новое ФИО: ";
    cin.ignore();
    getline(cin, fio);
    cout<<"Новый оклад: ";
    cin>>oklad;
    cout<<"Новая премия: ";
    cin>>premia;
    obj1.setFIO(fio);
    obj1.setoklad(oklad);
    obj1.setpremia(premia);
    cout<<"Стало у obj1: "<<obj1.getFIO()<<", "<<obj1.getoklad()<<", "<<obj1.getpremia()<<endl;
    //селеторы
    cout<<"getFIO()= "<<obj2.getFIO()<<endl;
    cout<<"getOklad()= "<<obj2.getoklad()<<endl;
    cout<<"getPremiya()= "<<obj2.getpremia()<<endl;
}