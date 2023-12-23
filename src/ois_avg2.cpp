#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    LL k; cin >> k;
    vector<LL> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    auto works = [&](LL c) -> bool {
        LL mn = 0, mx = 0;
        for (int i = 0; i < n; ++i) {
            mx += p[i] + c;
            mn += max(p[i] - c, 1LL);
        }
        return mn <= k * n && k * n <= mx;
    };
    LL l = -1, r = 1e9;
    while (r - l > 1) {
        LL m = (l + r) / 2;
        if (works(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r << "\n";
}
