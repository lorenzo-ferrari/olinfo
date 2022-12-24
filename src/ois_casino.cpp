#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr LL mod = 1e9 + 7;
static constexpr LL p = 29;

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

LL proc(string s) {
    int n = s.size();
    LL ip = inv(p);
    LL bp = fxp(p, n-1);
    LL h = 0;
    for (LL i = 0, pp = 1; i < n; ++i) {
        h = (h + s[i] * pp) % mod;
        pp = pp * p % mod;
    }
    LL minh = h;
    for (int i = 0; i < n-1; ++i) {
        h = (h - s[i] + mod) % mod;
        h = ip * h % mod;
        h = (h + bp*s[i]) % mod;
        minh = min(minh, h);
    }
    return minh;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int m; cin >> m;
    vector<string> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    map<LL, LL> mp;
    for (string& s : v) {
        mp[proc(s)]++;
    }
    LL ans = 0;
    for (auto& [_, x] : mp) {
        ans += x * (x-1) / 2;
    }
    cout << ans << "\n";
    return 0;
}

