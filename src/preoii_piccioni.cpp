// https://training.olinfo.it/#/task/preoii_piccioni/statement
// O(n log n * q/BS + q * BS)

#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")
#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr int N = 1e5 + 5;
static constexpr int BS = 1536;

struct nd {
    LL frq, sum;
    nd() : frq(0), sum(0) {}
    nd(LL f, LL s)
        : frq(f), sum(s) {}
};
static nd join(nd a, nd b) { return nd(a.frq + b.frq, a.sum + b.sum); }

struct Segment {
    int n;
    vector<nd> t;
    Segment() {}
    Segment(int _n) : n(_n) {
        t.resize(2 * n);
    }
    void update(int p) {
        t[p+n].frq += 1;
        t[p+n].sum += p;
        for (p += n; p > 1; p >>= 1) {
            t[p >> 1] = join(t[p], t[p^1]);
        }
    };
    nd query(int l, int r) {
        r = min(r, n);
        nd ans;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = join(ans, t[l++]);
            if (r & 1) ans = join(ans, t[--r]);
        }
        return ans;
    }
};

Segment st;
vector<LL> ans;
vector<int> dep, tin, tout, head;
vector<array<int, 3>> upds;
bitset<N> is_moved;
vector<vector<int>> adj;

int t;
static void dfs(int v, int k[]) {
    head[v] = v;
    tin[v] = t++;
    st.update(dep[v]);
    nd prv = st.query(dep[v]+1, dep[v]+k[v]+1);
    for (int u : adj[v]) {
        dep[u] = dep[v] + 1;
        dfs(u, k);
    }
    nd cur = st.query(dep[v]+1, dep[v]+k[v]+1);
    LL cnt = cur.frq - prv.frq;
    LL sum = cur.sum - prv.sum - (dep[v]+1)*cnt;

    ans[v] = k[v] * cnt - sum;
    tout[v] = t;
}

static void recalc(int n, int p[], int k[]) {
    ans.assign(n+1, 0);
    dep.assign(n+1, 0);
    tin.resize(n+1);
    tout.resize(n+1);
    head.resize(n+1);
    upds.clear();
    is_moved.reset();

    adj.assign(n+1, vector<int>(0));
    for (int i = 1; i <= n; ++i) {
        adj[p[i]].push_back(i);
    }

    t = 0;
    dfs(1, k);
}

void calcola_disagio(int n, int q, int p[], int k[], int u[], int v[], LL risposta[]) {
    st = Segment(n);
    int r = 0;
    for (int i = 0; i < q; ++i) {
        if (r % BS == 0) {
            recalc(n, p, k);
        }
        if (v[i] == -1) {
            // query
            risposta[r] = ans[u[i]];
            if (!is_moved.test(u[i])) {
                for (auto [j, h, d] : upds) {
                    if (tin[u[i]] <= tin[h] && tout[h] <= tout[u[i]] && k[u[i]] - (d - dep[u[i]] - 1) > 0) {
                        if (j < 0) {
                            risposta[r] -= k[u[i]] - (d - dep[u[i]] - 1);
                        } else {
                            risposta[r] += k[u[i]] - (d - dep[u[i]] - 1);
                        }
                    }
                }
            }
            ++r;
        } else {
            // update
            upds.push_back({-u[i], head[u[i]], dep[u[i]]});
            for (int j = p[u[i]]; is_moved.test(j); j = p[j]) {
                if (k[j] - (dep[u[i]] - dep[j] - 1) > 0) {
                    ans[j] -= k[j] - (dep[u[i]] - dep[j] - 1);
                }
            }
            is_moved.set(u[i]);
            ans[u[i]] = 0;
            p[u[i]] = v[i];
            head[u[i]] = head[v[i]];
            dep[u[i]] = dep[v[i]] + 1;
            for (int j = p[u[i]]; is_moved.test(j); j = p[j]) {
                if (k[j] - (dep[u[i]] - dep[j] - 1) > 0) {
                    ans[j] += k[j] - (dep[u[i]] - dep[j] - 1);
                }
            }
            upds.push_back({u[i], head[u[i]], dep[u[i]]});
        }
    }
}
