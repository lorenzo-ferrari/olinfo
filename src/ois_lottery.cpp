#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static bool psb(int l, int n, int a = -1, int b = -1) {
    // exists? string s of l digits with sum n s.t. ab[s] is valid?
    if (l == 0) return n == 0;
    if (l == 1) {
        return 0 <= n && n <= 9 && (n != a || n != b);
    }
    int mx = 9*l - l/3;
    if (b == 9 && a != 9) mx = 9*l - ((l+1) / 3);
    if (b == 9 && a == 9) mx = 9*l - ((l+2) / 3);
    int mn = l/3;
    if (b == 0 && a != 0) mn = (l+1) / 3;
    if (b == 0 && a == 0) mn = (l+2) / 3;
    return mn <= n && n <= mx;
}

static bool build(int l, int n, int a, int b) {
    assert(psb(l, n, a, b));
    if (l == 0) return true;
    for (int d = 0; d <= 9; ++d) {
        if ((b != d || a != d) && psb(l-1, n-d, b, d)) {
            cout << d;
            assert(build(l-1, n-d, b, d));
            return true;
        }
    }

    return false;
}

static void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int l = s.size();

    for (char c : s) n -= c - '0';

    vector<bool> good(l, true);
    for (int i = 2; i < l; ++i) {
        good[i] = good[i-1];
        if (s[i] == s[i-1] && s[i] == s[i-2]) {
            good[i] = false;
        }
    }

    if (!n && good[l-1]) {
        cout << s << "\n";
        return;
    }

    for (int prf = l-1; prf >= 0; --prf) {
        n += s[prf] - '0';
        if (prf && !good[prf-1]) continue;
        for (int d = s[prf]-'0'+1; d <= 9; ++d) {
            int a = (prf >= 2 ? s[prf-2]-'0' : -1);
            int b = (prf >= 1 ? s[prf-1]-'0' : -1);
            if (a == d && b == d) continue;
            if (psb(l-prf-1, n - d, b, d)) {
                for (int i = 0; i < prf; ++i) {
                    cout << s[i];
                }
                cout << d;
                assert(build(l-prf-1, n - d, b, d));
                cout << "\n";
                return;
            }
        }
    }

    for (++l; l < 20000; ++l) {
        if (psb(l, n, 0, 0)) {
            assert(build(l, n, 0, 0));
            cout << "\n";
            return;
        }
    }

    cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        solve();
    }
}
