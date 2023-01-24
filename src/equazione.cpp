#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL s(LL x) {
    LL ans = 0;
    while (x) {
        ans += x % 10;
        x /= 10;
    }
    return ans;
}

int main() {
    // x^2 + s(x)*x - n = 0
    LL n; cin >> n;
    LL l = 1, r = 1e9+1;
    while (r - l > 1) {
        LL m = l + (r - l) / 2;
        if (m*m <= n) {
            l = m;
        } else {
            r = m;
        }
    }
    LL ans = -1;
    clock_t t0 = clock();
    for (LL i = l; clock() - t0 < CLOCKS_PER_SEC && i > 0; --i) {
        if (i * (i + s(i)) == n) {
            ans = i;
        }
    }
    cout << ans << "\n";
}
