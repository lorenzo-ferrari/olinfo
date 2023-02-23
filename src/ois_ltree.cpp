#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr LL mod = 1e9 + 7;
static constexpr int N = 2e6 + 5;

LL fxp(LL x, int y) {
    LL ans = 1;
    while (y) {
        if (y & 1) {
            ans = ans * x % mod;
        }
        x = x * x % mod;
        y >>= 1;
    }
    return ans;
}
LL inv(LL x) { return fxp(x, mod-2); }

int main() {
    vector<LL> f(N), fi(N);
    f[0] = fi[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = i*f[i-1] % mod;
        fi[i] = inv(f[i]);
    }
    auto c = [&](int n) -> LL {
        LL ans = f[2*n];
        ans = ans * fi[n] % mod;
        ans = ans * fi[n] % mod;
        ans = ans * inv(n+1) % mod;
        return ans;
    };
    int n; cin >> n;
    LL ans = 0;
    for (int i = n-1; 2*i > n-1; --i) {
        ans += c(i) * c(n-1-i);
        ans %= mod;
    }
    cout << ans << "\n";
}
