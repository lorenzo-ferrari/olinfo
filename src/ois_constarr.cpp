#include <bits/stdc++.h>
using namespace std;
using LL = unsigned long long;

static constexpr LL mod = 1e9 + 7;

int main() {
    LL n, m, l, r, k;
    cin >> n >> m >> l >> r >> k;
    k = (k + m - (l * (n % m)) % m) % m;
    r -= l;

    auto combine = [&](vector<LL> a, vector<LL> b) -> vector<LL> {
        vector<LL> ans(m);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                ans[i] += a[j] * b[i>=j ? i-j : i-j+m];
                ans[i] %= mod;
            }
        }
        return ans;
    };

    vector<LL> base(m);
    for (LL i = 0; i < m && i <= r; ++i) {
        base[i] = (r - i) / m + 1;
        base[i] %= mod;
    }

    vector<LL> ans(m); ans[0] = 1;
    while (n) {
        if (n & 1) {
            ans = combine(ans, base);
        }
        base = combine(base, base);
        n >>= 1;
    }

    cout << ans[k] << "\n";
}
