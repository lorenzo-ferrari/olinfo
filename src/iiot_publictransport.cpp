#include "bits/stdc++.h"
using namespace std;
using LL = long long;

struct fn {
    LL m, q;
    explicit fn(LL _m, LL _q) : m(_m), q(_q) {}
    LL eval(LL x) const { return m*x + q; }
};

struct LCT {
    int n;
    vector<fn> t;
    explicit LCT(int _n) {
        for (n = 1; n < _n; n <<= 1);
        t.assign(2 * n, fn(0, 1e15));
    }
    void add_fn(fn f) {
        add_fn(f, 1, 0, n);
    }
    void add_fn(fn f, int i, int l, int r) {
        int m = (l + r) / 2;
        bool lf = f.eval(l) < t[i].eval(l);
        bool md = f.eval(m) < t[i].eval(m);
        if (md) {
            swap(t[i], f);
        }
        if (r - l <= 1) return;
        if (lf != md) {
            add_fn(f, 2*i, l, m);
        } else {
            add_fn(f, 2*i+1, m, r);
        }
    }
    LL get(int x, int i = 1, int l = 0, int r = -1) {
        if (r == -1) r = n;
        int m = (l + r) / 2;
        if (r - l <= 1) return t[i].eval(x);
        if (x < m) {
            return min(t[i].eval(x), get(x, 2*i, l, m));
        } else {
            return min(t[i].eval(x), get(x, 2*i+1, m, r));
        }
    }
};

struct ST {
    int n;
    vector<int> t;
    ST(vector<int> v) : n(v.size()), t(2 * n) {
        for (int i = 0; i < n; ++i) {
            t[i + n] = v[i];
        }
        for (int i = n-1; i > 0; --i) {
            t[i] = min(t[2 * i], t[2 * i + 1]);
        }
    }
    int query(int l, int r) {
        int ans = 1e9;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = min(ans, t[l++]);
            if (r & 1) ans = min(ans, t[--r]);
        }
        return ans;
    }
};

int main() {
    int n; cin >> n;
    int m; cin >> m;
    int q; cin >> q;
    vector<int> s(n), t(n - 1);
    for (int& i : s) cin >> i;
    for (int& i : t) cin >> i;

    vector<LL> pt(n); pt[0] = 0;
    vector<LL> st(n); st[n - 1] = 0;
    for (int i = 1; i < n; ++i) pt[i] = pt[i - 1] + t[i - 1];
    for (int i = n - 2; i >= 0; --i) st[i] = st[i + 1] + t[i];

    struct qry {
        LL a, b, c, d, h, i;
    };
    vector<qry> qs(q);
    for (int i = 0; i < q; ++i) {
        auto& qq = qs[i];
        qq.i = i;
        cin >> qq.a >> qq.b >> qq.c >> qq.d;
        if (qq.a > qq.c) {
            swap(qq.a, qq.c);
            swap(qq.b, qq.d);
        }
        qq.h = max(qq.b, qq.d) - min(qq.b, qq.d);
        qq.h = min(qq.h, m - qq.h);
    }
    vector<vector<qry>> up(n), lo(n);
    for (auto qq : qs) {
        up[qq.c].push_back(qq);
        lo[qq.a].push_back(qq);
    }

    vector<LL> ans(q, 1e15);

    {   // case: attraversa in mezzo
        ST seg(s);
        for (auto qq : qs) {
            LL cur = pt[qq.c] - pt[qq.a];
            cur += qq.h * seg.query(qq.a, qq.c + 1);
            ans[qq.i] = min(ans[qq.i], cur);
        }
    }

    {   // case: attraversa piu' in alto
        LCT lct(m);
        for (int i = n - 1; i >= 0; --i) {
            lct.add_fn(fn(s[i], 2 * pt[i]));
            for (auto qq : up[i]) {
                LL cur = lct.get(qq.h) - pt[qq.a] - pt[qq.c];
                ans[qq.i] = min(ans[qq.i], cur);
            }
        }
    }

    {   // case: attraversa piu' in basso
        LCT lct(m);
        for (int i = 0; i < n; ++i) {
            lct.add_fn(fn(s[i], 2 * st[i]));
            for (auto qq : lo[i]) {
                LL cur = lct.get(qq.h) - st[qq.a] - st[qq.c];
                ans[qq.i] = min(ans[qq.i], cur);
            }
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }
}
