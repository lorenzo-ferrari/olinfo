/*
 *  https://training.olinfo.it/#/task/juice/statement
 *
 *  please be aware that the following solution is not the smartest one
 *  (and definetely not the easiest one to code)
 *
 *  let dp[i][k] be the the answer if i is cut exactly on day k
 *  let pp[i][k] be max(dp[i][0], dp[i][1], ..., dp[i][k])
 *  -> pp[i][k] <= pp[i][k+1]
 *
 *  every time a parent asks, use pp[i]
 *  
 *  dp[i][k] = sum(pp[j][k] for every j child of i)
 *  dp[i][day[i]] += w[i]
 *
 *  it is too expensive to run the dp explicitly
 *  -> let pp[i] be a segment tree st and st.get(k) be pp[i][k]
 *  -> the queries are known beforehand, compressed segtree
 *  -> HLD, so each element is copied in O(lg n) segtrees
 *  -> compressed lazy segtree + helper functions to keep pp[i] increasing
 *
 *  * alternatively, lazy segtree beats works too
 *
 */

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct ST {
    struct nd {
        LL val, lset = 0, lsum = 0;
        nd(LL _val = 0) : val(_val) {}
    };
    nd join(const nd& a, const nd& b) {
        return nd(max(a.val, b.val));
    }

    int n;
    vector<nd> t;

    ST() {}
    ST(int _n) {
        for (n = 1; n < _n; n <<= 1);
        t.resize(2 * n);
    }

    void _apply_set(int i, LL x) {
        t[i].lset = x;
        t[i].lsum = 0;
    }

    void _apply_sum(int i, LL x) {
        if (t[i].lset) {
            t[i].lset += x;
        } else {
            t[i].lsum += x;
        }
    }

    void _prop(int i) {
        if (t[i].lset) {
            t[i].val = t[i].lset;
            if (i < n) {
                _apply_set(2*i  , t[i].lset);
                _apply_set(2*i+1, t[i].lset);
            }
        } else if (t[i].lsum) {
            t[i].val += t[i].lsum;
            if (i < n) {
                _apply_sum(2*i  , t[i].lsum);
                _apply_sum(2*i+1, t[i].lsum);
            }
        }
        t[i].lset = t[i].lsum = 0;
    }

    int _find_first(int l, int r, LL x, int i = 1, int a = 0, int b = -1) {
        if (b == -1) b = n;
        _prop(i);
        if (r <= a || b <= l || t[i].val < x) return n;
        if (i > n == 1) return a;
        int o = _find_first(l, r, x, 2*i, a, (a+b)/2);
        return o != n ? o : _find_first(l, r, x, 2*i+1, (a+b)/2, b);
    }

    void _range_upd(int l, int r, LL x, bool w, int i = 1, int a = 0, int b = -1) {
        if (b == -1) b = n;
        _prop(i);
        if (r <= a || b <= l) return;
        if (l <= a && b <= r) { if (w) _apply_sum(i, x); else _apply_set(i, x); }
        else {
            _range_upd(l, r, x, w, 2*i  , a, (a+b)/2);
            _range_upd(l, r, x, w, 2*i+1, (a+b)/2, b);
            t[i] = join(t[2*i], t[2*i+1]);
        }
        _prop(i);
    }

    LL get(int p, int i = 1, int a = 0, int b = -1) {
        if (b == -1) b = n;
        _prop(i);
        if (i >= n) return t[i].val;
        if (p < (a+b)/2) return get(p, 2*i , a, (a+b)/2);
        else return get(p, 2*i+1, (a+b)/2, b);
    }

    void _maxify(int l) {
        LL x = get(l-1);
        int r = _find_first(l, n, x);
        _range_upd(l, r, x, false);
    }

    void range_add(int l, int r, LL x) {
        if (r == -1) r = n;
        _range_upd(l, r, x, true);
    }

    void point_add(int p, LL x) {
        range_add(p, p+1, x);
        _maxify(p+1);
    }
};

struct ST_ZIP {
    int n;
    vector<int> q;
    ST st;

    ST_ZIP() {}
    ST_ZIP(const vector<int>& _q) : q(_q), n(_q.size()) {
        st = ST(n);
    }

    int tr(int p) { return lower_bound(begin(q), end(q), p) - begin(q); }

    void range_add(int l, int r, LL x) { st.range_add(tr(l), (r == -1 ? st.n : tr(r)), x); }

    void point_add(int p, LL x) { st.point_add(tr(p), x); }

    LL get(int p) { return st.get(tr(p)); }

    void merge(ST_ZIP oth) {
        for (int i = oth.n-1; i >= 0; --i) {
            int l = oth.q[i];
            int r = (i == oth.n-1 ? -1 : oth.q[i+1]);
            range_add(l, r, oth.get(oth.q[i]));
        }
    }
};

LL harvest(int n, int m, int k, vector<int>& p, vector<int>& v, vector<int>& d, vector<int>& w) {
    vector<vector<int>> adj(n);
    vector<int> head(n);
    vector<vector<int>> qs(n);
    for (int i = 1; i < n; ++i) {
        adj[p[i]].push_back(i);
    }
    vector<array<int, 2>> f(n); // {day, juiciness}
    for (int i = 0; i < m; ++i) {
        f[v[i]] = {d[i], w[i]};
    }
    {
        vector<int> sz(n);
        auto dfs = [&](auto&& self, int v) -> int {
            sz[v] = 1;
            for (int u : adj[v]) {
                sz[v] += self(self, u);
            }
            sort(begin(adj[v]), end(adj[v]), [&](int i, int j){ return sz[i] > sz[j]; });
            return sz[v];
        };
        dfs(dfs, 0);
    }
    {
        auto dfs = [&](auto&& self, int v, int h) -> void {
            head[v] = h;
            qs[h].push_back(f[v][0]);
            for (int u : adj[v]) {
                self(self, u, (u == adj[v][0] ? h : u));
                if (u != adj[v][0]) {
                    for (int i : qs[u]) {
                        qs[h].push_back(i);
                    }
                }
            }
        };
        dfs(dfs, 0, 0);
        for (int i = 0; i < n; ++i) {
            sort(begin(qs[i]), end(qs[i]));
            qs[i].resize(unique(begin(qs[i]), end(qs[i])) - begin(qs[i]));
        }
    }

    auto solve = [&](auto&& self, int v) -> ST_ZIP {
        ST_ZIP st;
        if (adj[v].empty()) {
            st = ST_ZIP(qs[head[v]]);
        } else {
            st = self(self, adj[v][0]);
        }
        for (int u : adj[v]) {
            if (u == adj[v][0]) continue;
            auto oth = self(self, u);
            st.merge(oth);
        }
        st.point_add(f[v][0], f[v][1]);
        return st;
    };

    auto st = solve(solve, 0);

    return st.get(st.q.back());
}
