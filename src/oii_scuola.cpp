#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    int p; cin >> p;
    if (p == 1) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << j+1 << " " << (i+j)%n+1 << " ";
            }
            cout << "\n";
        }
    } else {
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((j^i) > j) {
                    cout << j+1 << " " << (j^i)+1 << " ";
                }
            }
            cout << "\n";
        }
    }
}
