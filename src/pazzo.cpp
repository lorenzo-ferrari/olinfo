#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    int m; cin >> m;
    int cur = 0;
    for (int a, b; m--;) {
        cin >> a >> b;
        if (a == cur || b == cur) {
            cur = a ^ b ^ cur;
        }
    }
    cout << cur << "\n";
}
