#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr int N = 3e5 + 5;
static constexpr int mod = 1e9 + 7;
static LL inv[N], f[N], fi[N];

void precalc() {
    inv[1] = 1;
    for (int a = 2; a < N; ++a) {
        inv[a] = mod - (LL)(mod / a) * inv[mod % a] % mod;
    }
    f[0] = fi[0] = 1;
    for (int a = 1; a < N; ++a) {
        f[a] = f[a - 1] * a % mod;
        fi[a] = fi[a - 1] * inv[a] % mod;
    }
}

LL perm(int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0) return 0;
    LL ans = f[x + y + z];
    ans = ans * fi[x] % mod;
    ans = ans * fi[y] % mod;
    ans = ans * fi[z] % mod;
    return ans;
}

LL calc(int m, int b, int c) {
    // consider m empty containers to be filled with B,C
    if (m < 0) return 0;
    if (m == 0 && b == 0 && c == 0) return 1;
    // let's call even/odd container a cointainer with even/odd number of items
    LL ans = 0;
    LL pow2 = 1;
    for (int p = 0; p <= m; ++p, pow2 = 2 * pow2 % mod) {
        // let p be the number of even containers
        // let d be the number of odd containers
        // let db be the number of odd containers in the form BCB
        // let dc be the number of odd containers in the form CBC
        // db + dc = m - p
        // db - dc = b - c
        // -> db = (m - p + b - c) / 2
        // -> dc = m - p - db
        if ((m - p + b - c) % 2 != 0) {
            continue;
        }
        int db = (m - p + b - c) / 2;
        int dc = m - p - db;
        assert(db + dc == m - p);
        assert(db - dc == b - c);

        LL cur_ans = perm(p, db, dc);   // order of the containers
        cur_ans = cur_ans * pow2 % mod; // BCBC vs CBCB
        // then consider how you can distribute couples [BC] to the containers
        // so that the resulting string will have the right number of B,C
        int used = db + dc + 2*p;
        int left = b + c - used;
        if (left < 0) {
            continue;
        }
        cur_ans = cur_ans * perm(left/2, m-1, 0) % mod;

        ans = (ans + cur_ans) % mod;
    }
    return ans;
}

void solve() {
    int a; cin >> a;
    int b; cin >> b;
    int c; cin >> c;
    LL ans = 0;
    ans += calc(a - 1, b, c);
    ans += 2 * calc(a, b, c);
    ans += calc(a + 1, b, c);
    ans %= mod;
    cout << ans << "\n";
}

int main() {
    precalc();
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
