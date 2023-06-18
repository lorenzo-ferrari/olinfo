#include "bits/stdc++.h"
using namespace std;
using LL = long long;

struct FT {
    int n;
    vector<LL> t;
    FT(int n) : n(n), t(n+1) {}
    void upd(int p, int v = 1) {
        for (++p; p <= n; p += (p&-p)) {
            t[p] += v;
        }
    }
    LL sum(int p) {
        LL ans = 0;
        for (++p; p; p -= (p&-p)) {
            ans += t[p];
        }
        return ans;
    }
};

void solve() {
    int n; cin >> n;
    vector<int> p(n), ip(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i]; --p[i];
        ip[p[i]] = i;
    }

    FT ft(n);
    LL cur = 0;
    for (int i = n-1; i >= 0; --i) {
        cur += ft.sum(p[i]);
        ft.upd(p[i]);
    }

    LL ans = cur;
    for (int i = n-1; i >= 0; --i) {
        cur += ip[i] - (n - 1 - ip[i]);
        ans = min(ans, cur);
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
