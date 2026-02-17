#include <iostream>
using namespace std;

int main() {
    const int n = 3, m = 3;
    int k=1, tmp;
    int arr[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
    cin >> k;
    if (k > n || k < 0) {
        k = n-1;
    }
    cout << "Исходная матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < m-1-i; j++) {
            if (arr[k-1][j] > arr[k-1][j + 1]) {
                for (int r = 0; r < n; r++) {
                    tmp = arr[r][j];
                    arr[r][j] = arr[r][j + 1];
                    arr[r][j + 1] = tmp;
                }
            }
        }
    }
    cout << "Исправленная матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}