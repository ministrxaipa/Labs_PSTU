#include <iostream>
using namespace std;

int main() {
    int n, k;
    cin >> n;
    bool d = true;
    while (n != 0) {
        cin >> k;
        if (k == 0) {
            break; 
        }
        else if (k <= n) { 
            d = false; 
        }
        n = k;
    }
    if (d == true) {
        cout << "числа упорядочены по возрастанию" << endl;
    } else {
        cout << "числа не упорядочены по возрастанию" << endl;
    }
    
    return 0;
}