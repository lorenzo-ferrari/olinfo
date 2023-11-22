#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    for (int i = 0; i <= n; ++i) {
        if ((n-2*i) % 3 == 0) {
            cout << string(i, '1');
            cout << string(n-i, '5');
            cout << "\n";
            return 0;
        }
    }
    cout << "-1\n";
}
