#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
using LL = long long;

constexpr LL mod = 666013;

int main() {
    int x; cin >> x;
    int k; cin >> k;
    vector<LL> c(k); c[0] = 1;
    for (int i = 1; i < k; ++i) {
        c[i] = 10 * c[i-1] % mod;
    }

    int l = (k + 1) / 2;
    vector<int> v(l, 0);
    v[0] = 1;

    auto cc = [&](int i) -> LL {
        if ((k & 1) && i == k/2) {
            return c[i];
        } else {
            return (c[i] + c[k - 1 - i]) % mod;
        }
    };

    auto add = [&]() -> LL {
        LL ans = 0;
        bool rip = true;
        for (int i = l-1; rip; --i) {
            if (v[i] + 1 < 10) {
                ans += cc(i);
                ++v[i];
                rip = 0;
            } else {
                assert(v[i] == 9);
                ans += cc(i) * (mod - 9);
                v[i] = 0;
            }
        }
        return ans;
    };

    LL ans = 0;
    LL cur = cc(0);
    for (int i = 0; i < x; ++i) {
        // for (int j : v) cout << j << " ";
        ans += cur;
        cur += add();
        ans %= mod;
        cur %= mod;
    }
    cout << ans << "\n";
}
