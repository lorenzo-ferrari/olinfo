#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr int N = 1e5 + 5;
static constexpr LL mod = 1e9 + 7;

LL fxp(LL x, LL y) {
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
LL inv(LL x) { return fxp(x, mod - 2); }

LL f[N], fi[N];

LL choose(int n, int k) {
    LL ans = f[n];
    ans = ans * fi[k] % mod;
    ans = ans * fi[n - k] % mod;
    return ans;
}

int main() {
    f[0] = fi[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = f[i - 1] * i % mod;
        fi[i] = inv(f[i]);
    }
    int n; cin >> n;
    map<int, int> frq;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        ++frq[x];
    }
    vector<int> fc;
    for (auto [_, cnt] : frq) {
        fc.push_back(cnt);
    }
    sort(begin(fc), end(fc), greater<int>());
    LL ans = 1;
    for (int i = 1; !fc.empty(); ++i) {
        while (!fc.empty() && fc.back() < i) {
            fc.pop_back();
        }
        if (fc.empty()) {
            break;
        }
        LL cur = 1;
        for (int j : fc) {
            cur *= choose(j, i) + 1;
            cur %= mod;
        }
        ans += cur - 1;
        ans %= mod;
    }
    cout << ans << "\n";
}
