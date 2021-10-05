#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define all(x) x.begin(), x.end()

struct st {
    struct nd {
        LL sum = 0;
        LL cnt = 0;
        nd() {}
        nd(LL a, LL b) : sum(a), cnt(b) {}
    };
    nd join(nd a, nd b) { return nd(a.sum + b.sum, a.cnt + b.cnt); }
    vector<nd> t;
    int n;
    st(int _n) {
        for (n = 1; n < _n; n <<= 1); n <<= 1;
        t.resize(2 * n);
    }
    void upd(int i, LL v) {
        i += n;
        for (t[i] = join(t[i], nd(v, 1)); i > 1; i >>= 1)
            t[i >> 1] = join(t[i], t[i ^ 1]);
    }
    pair<LL,LL> low(LL s) {
        LL os = s, i = 1, ans = 0;
        for (; i < n;) {
            if (s < t[i << 1].sum) {
                i = i << 1;
            } else {
                ans += t[i << 1].cnt;
                s -= t[i << 1].sum;
                i = i << 1 | 1;
            }
        }
        return {ans, os - s};
    }
};

struct op {
    LL s, q, i;
    op() {}
    op(LL s, LL q) : s(s), q(q) {}
};

int main() {
#ifdef EVAL
    ifstream cin("input.txt");
    ofstream cout("output.txt");
#endif
    LL n, b; cin >> n >> b;
    vector<op> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].s >> v[i].q;
        v[i].i = i;
    }
    sort(all(v), [](op a, op b) { return a.q < b.q; });
    unordered_map<LL, LL> mp;
    for (int i = 0; i < n; ++i)
        mp[v[i].i] = i;

    sort(all(v), [](op a, op b) { return a.s*b.q < b.s*a.q; });

    st t(n);
    int ans = 0, pq = 0, idx = 0;
    for (int i = 0; i < n; ++i) {
        t.upd(mp[v[i].i], v[i].q);
        LL q = LL(b * v[i].q / v[i].s);
        auto [l, cq] = t.low(q);
        if (l > ans || (l==ans && pq*v[idx].s*v[i].q > cq*v[i].s*v[idx].q)) {
            ans = l;
            idx = i;
            pq = cq;
        }
    }

    cout << ans << "\n";
    
    sort(v.begin(), v.begin() + idx + 1, [](op a, op b){ return a.q < b.q; });
    for (int i = 0; i < ans; ++i)
        cout << v[i].i + 1 << "\n";
}
