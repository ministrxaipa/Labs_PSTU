// вариант 15
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s, r="", w="";
    getline(cin, s);

    cout << "Введенная строка: " << s << endl;
    s = s + " ";
    int h = s.length();
    
    for (int i = 0; i < h; i++){  
        char c = s[i];
        
        if (c == ' '){  
            if (w.length() > 0){
                bool ok = true;
                for (int j = 0; j < w.length(); j++){
                    char d = w[j];  
                    bool slovo = (d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z');
                    bool zifra = (d >= '0' && d <= '9');
                    
                    if(!slovo && !zifra){
                        ok = false;
                        break;
                    }
                }
                if (ok){
                    if(r.length() > 0){
                        r = r + " ";
                    }
                    r = r + w;
                }
            }
            w = "";  
        } else {
            w = w + c;
        }
    }
    
    cout << "Новая строка: " << r << endl;
    
    return 0;
}