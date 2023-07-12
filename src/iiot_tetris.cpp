#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int m; cin >> m;
    if (n * m % 4 != 0) {
        cout << "-1\n";
    } else {
        cout << n * m / 4 << "\n";
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
            if (n % 4 == 0) cout << m * (i / 4) + j;
            else if (m % 4 == 0) cout << n * (j / 4) + i;
            else cout << (m/2) * (i/2) + j/2;
            cout << " \n"[j == m-1];
        }
    }
}
