#include "bits/stdc++.h"
using namespace std;
using LL = long long;
using vi = vector<int>;
#define all(x) begin(x), end(x)

#ifndef LOCAL
static constexpr int N = 3e5 + 5;
#else
static constexpr int N = 120;
#endif

struct AncSum {
    int n;
	vector<int> in, out;
	vector<int> t;
    AncSum(int n, vector<vector<int>> adj)
		: n(n), in(n), out(n), t(2 * n) {
        int tt = 0;
        auto dfs = [&](auto&& self, int v, int p) -> void {
            in[v] = tt;
            for (int u : adj[v]) {
                if (u == p) continue;
                self(self, u, v);
            }
            out[v] = ++tt;
        };
        dfs(dfs, 0, -1);
    }
    void add_range(int l, int r, int v) {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) t[l++] += v;
            if (r & 1) t[--r] += v;
        }
    }
    int qry(int v) {
        LL ans = 0;
        for (v += n; v > 0; v >>= 1) {
            ans += t[v];
        }
        return ans;
    }
    void inc_node(int v, int x) {
        add_range(in[v], out[v], x);
    }
    int ask_anc(int v) {
        return qry(out[v]-1);
    }
};

struct Dsu {
	vector<int> p, s;
	Dsu(int n) : p(n), s(n, 1) {
		iota(all(p), 0);
	}
	int findset(int v) {
		return p[v] == v ? v : p[v] = findset(p[v]);
	}
	void onion(int a, int b) {
		a = findset(a);
		b = findset(b);
		if (s[a] < s[b])
			swap(a, b);
		p[b] = a;
		s[a] += s[b];
	}
};

struct OfflineLca {
	vector<int> anc;
	vector<bool> vis;
	vector<int> ans;
	vector<vector<array<int, 2>>> queries;
	Dsu dsu;

	OfflineLca(int n, vector<vector<int>> adj, vector<int> l, vector<int> t)
		: anc(n), vis(n), ans(l.size()), queries(n), dsu(n) {
		assert(t.size() == l.size());
		for (int i = 0; i < (int)t.size(); ++i) {
			queries[t[i]].push_back({l[i], i});
			queries[l[i]].push_back({t[i], i});
		}
		auto dfs = [&](auto&& self, int v) -> void {
			vis[v] = true;
			anc[v] = v;
			for (int u : adj[v]) {
				if (!vis[u]) {
					self(self, u);
					dsu.onion(v, u);
					anc[dsu.findset(v)] = v;
				}
			}
			for (auto [oth, i] : queries[v]) {
				if (vis[oth]) {
					ans[i] = anc[dsu.findset(oth)];
				}
			}
		};
		dfs(dfs, 0);
	}
	int lca(int i) {
		return ans[i];
	}
};


vi raccogli(int n, int q, vi& a, vi& b, vi& oc, vi& l, vi& t) {
	// i != j => c[i] != c[j]
	vector<LL> c(n);
	for (int i = 0; i < n; ++i) c[i] = LL(n) * oc[i] + i;

	vector<vector<int>> adj(n);
	for (int i = 0; i < n - 1; ++i) {
		adj[a[i]].push_back(b[i]);
		adj[b[i]].push_back(a[i]);
	}

	OfflineLca lca(n, adj, l, t);
	AncSum ancsum(n, adj);

	vector<int> state(n);
	auto sum_on_path = [&](int v, int u, int i) -> int {
		int l = lca.lca(i);
		int ans = ancsum.ask_anc(v) + ancsum.ask_anc(u) - 2 * ancsum.ask_anc(l);
		ans += state[l];
		return ans;
	};

	vector<int> ans(q, -1);
	vector<array<LL, 2>> ci(n);
	for (int i = 0; i < n; ++i) ci[i] = {c[i], i};
	sort(all(ci));
	auto search = [&](auto&& self, int ll, int rr, vector<int> qq) -> void {
		if (qq.empty()) return;
		if (rr - ll == 1) {
			for (int i : qq) {
				ans[i] = ci[ll][0] / n;
			}
			return;
		}
		// assume those with c[v] >= c[rr] are already on
		int mm = (ll + rr) / 2;
		for (int i = mm; i < rr; ++i) {
			ancsum.inc_node(ci[i][1], +1);
			state[ci[i][1]] += 1;
		}
		vector<int> ql, qr;
		for (int i : qq) {
			if (sum_on_path(l[i], t[i], i) < n - mm) {
				qr.push_back(i);
			} else {
				ql.push_back(i);
			}
		}
		self(self, ll, mm, ql);
		for (int i = mm; i < rr; ++i) {
			ancsum.inc_node(ci[i][1], -1);
			state[ci[i][1]] -= 1;
		}
		self(self, mm, rr, qr);
	};

	vector<int> p(q);
	iota(all(p), 0);
	search(search, 0, n, p);

	return ans;
}
