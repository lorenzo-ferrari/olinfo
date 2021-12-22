#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

typedef long long ll;

const int N = 1e5;
const int LOG = 18;
const ll INF = 1e9;

struct ND {
	ll to;
	ll mn;
	ll sum;
	ll pref;
	ll suff;
	ll subarr;
	ND () {}
	ND (int a, int b, ll c, ll d, ll e, ll f) :
		to(a), mn(b), sum(c), pref(d), suff(e), subarr(f) {}
};

ND join(ND &a, ND &b) {
	return ND (
		b.to,
		min(a.mn, b.mn),
		a.sum + b.sum,
		min(a.pref, a.sum + b.pref),
		min(b.suff, b.sum + a.suff),
		max(max(a.subarr, b.subarr), a.sum + b.sum - a.pref - b.suff)
	);
}

int dep[N];
ND up[N][LOG];

void inizia(int n, int t, int a[], int b[], int c[]) {
	vector<vector<pair<int, int>>> g(n);
	for (int i = 0; i < n-1; i++) {
		g[a[i]].push_back({b[i], c[i]});
		g[b[i]].push_back({a[i], c[i]});
	}
	function<void(int,int,int)> dfs = [&](int v, int par, int x) {
		up[v][0] = ND(par,x,x,min(0,x),min(0,x),max(0,x));
		if (v) dep[v] = dep[par] + 1;
		for (auto &[u, w] : g[v])
			if (par != u)
				dfs(u, v, w);
	};
	dfs(0, 0, 0);
	for (int i = 1; i < LOG; i++)
		for (int j = 0; j < n; j++)
			up[j][i] = join(up[j][i-1], up[up[j][i-1].to][i-1]);
}

int lca(int u, int v) {
	if (dep[u] > dep[v])
		swap(v, u);
	int k = dep[v] - dep[u];
	for (int i = LOG-1; i >= 0; i--)
		if (k & (1 << i))
			v = up[v][i].to;
	if (u == v)
		return u;
	for (int i = LOG-1; i >= 0; i--)
		if (up[v][i].to != up[u][i].to) {
			v = up[v][i].to;
			u = up[u][i].to;
		}
	return up[u][0].to;
}

ll query(int v, int k, const function<ll(ll, ND*)> f, ll ans) {
	for (int i = LOG-1; i >= 0; i--)
		if (k & (1 << i)) {
			ans = f(ans, &up[v][i]);
			v = up[v][i].to;
		}
	return ans;
}

ll mn_prf(int v, int k) {
	ll ans = 0;
	ll sum = 0;
	for (int i = LOG-1; i >= 0; i--)
		if (k & (1 << i)) {
			ans = min(ans, sum + up[v][i].pref);
			sum += up[v][i].sum;
			v = up[v][i].to;
		}
	return ans;
}

ll mx_subarr(int v, int k) {
	ll ans = 0;
	ll sum = 0;
	ll mn_pref = 0;
	for (int i = LOG-1; i >= 0; i--)
		if (k & (1 << i)) {
			ans = max(ans, up[v][i].subarr);
			ans = max(ans, sum + up[v][i].sum - mn_pref - up[v][i].suff);
			mn_pref = min(mn_pref, sum + up[v][i].pref);
			sum += up[v][i].sum;
			v = up[v][i].to;
		}
	return ans;
}

ll distanza1(int u, int v) { return dep[u] + dep[v] - 2*dep[lca(u, v)]; }
ll distanza2(int u, int v) {
	int l = lca(u, v);
	return query(u, dep[u]-dep[l], [](ll a, ND* nd){ return a + nd->sum; }, 0) +
				 query(v, dep[v]-dep[l], [](ll a, ND* nd){ return a + nd->sum; }, 0);
}
ll minimo(int u, int v) {
	int l = lca(u, v);
	return min(query(u, dep[u]-dep[l], [](ll a, ND* nd){ return min(a, nd->mn); }, INF),
						 query(v, dep[v]-dep[l], [](ll a, ND* nd){ return min(a, nd->mn); }, INF));
}
ll massimo(int u, int v) {
	int l = lca(u, v);
	ll sum_u = query(u, dep[u]-dep[l], [](ll a, ND* nd){ return a + nd->sum; }, 0);
	ll sum_v = query(v, dep[v]-dep[l], [](ll a, ND* nd){ return a + nd->sum; }, 0);
	ll u_mn = mn_prf(u, dep[u] - dep[l]);
	ll v_mn = mn_prf(v, dep[v] - dep[l]);
	ll with_lca = sum_u + sum_v - u_mn - v_mn;
	ll without_lca = max(mx_subarr(u, dep[u] - dep[l]), mx_subarr(v, dep[v] - dep[l]));

	return max(with_lca, without_lca);
}
