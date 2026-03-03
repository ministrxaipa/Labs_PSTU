#include <iostream>

using namespace std;

int nod(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == b) {
        return a;
    }
    if (a > b) {
        return nod(a - b, b);
    }
    return nod(a, b - a);
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << "НОД: " << nod(a, b) << endl;
    return 0;
}

