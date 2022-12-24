#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int k; cin >> k;
    vector<int> v(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    LL ans = 0;
    while (k--) {
        int i; cin >> i;
        int q; cin >> q;
        if (v[i] + q > c[i]) {
            ans += c[i] - v[i];
            v[i] = 0;
        }
        v[i] += q;
    }
    for (int i = 0; i < n; ++i) {
        if (v[i]) {
            ans += c[i] - v[i];
        }
    }
    cout << ans << "\n";
}
