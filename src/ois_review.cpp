#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")
#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr int N = 1e6 + 1;

LL xgcd(LL a, LL b, LL& x, LL& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    LL nx, ny;
    LL g = xgcd(b, a % b, nx, ny);
    x = ny;
    y = nx - ny*(a / b);
    return g;
}

LL inv(LL a, LL m) {
    // x*a + y*m == 1 (mod m)
    LL x, y;
    LL g = xgcd(a, m, x, y);
    x = (x % m + m) % m;
    return x;
}

int main() {
    int n; cin >> n;
    int m; cin >> m;
    int d; cin >> d;
    vector<LL> s(n);
    for (LL& i : s) cin >> i;
    LL mod = 1;
    for (int _ = 0; _ < d; ++_) mod *= 10;

    for (LL k = 1; k < N; ++k) {
        LL gcd = __gcd(mod, k);
        LL p = k / gcd;
        LL pmod = mod / gcd;
        bool works = true;
        LL i = inv(p, pmod);
        LL cur = 0;
        for (LL x : s) {
            if (x % gcd) { works = false; break; }
            LL a_i = (x / gcd) * i % pmod;
            while (a_i <= cur && a_i <= m) {
                a_i += pmod;
            }
            if (a_i > m) { works = false; break; }
            cur = a_i;
        }
        if (works) {
            cout << k << "\n";
            return 0;
        }
    }
    assert(false);
}
