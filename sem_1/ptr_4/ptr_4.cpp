#include <iostream>
using namespace std;
int main() {
    int n, x, max, min; 
    cin >> n;
    int *c = &x;  
    cin >> *c;   
    max = *c;
    min = *c;
    for (int i = 2; i <= n; i++) {
        cin >> *c; 
        
        if (*c > max) {
            max = *c;
        }
        else if (*c < min) {  
            min = *c;
        }
    }
    cout << max << endl;
    cout << min << endl;
    return 0;
}