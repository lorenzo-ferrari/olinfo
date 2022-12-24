#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int sa = 0, ma = 1e9;
    int sb = 0, mb = 1e9;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        sa += x;
        ma = min(ma, x);
    }
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        sb += x;
        mb = min(mb, x);
    }
    cout << (sa < sb ? "Hamilton" : "Verstappen") << "\n";
    cout << (ma < mb ? "Hamilton" : "Verstappen") << "\n";
}
