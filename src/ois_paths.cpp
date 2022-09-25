#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#define int long long
using namespace std;

const int nax = 3e5 + 42;
const int mod = 1e9 + 7;
const int L = 21;

int fast_exp(int x, int y) {
    int res = 1;
    x = x % mod;

    while (y > 0) {
        if (y & 1) res = (res * x) % mod;

        y = y >> 1;
        x = (x * x) % mod;
    }

    return res;
}

int parent[nax];

void make_set(int v) {
    parent[v] = v;
}

int find_set(int v) {
    return (v == parent[v]) ? v : parent[v] = find_set(parent[v]);
}

void union_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);

    if(a != b) {
        parent[b] = a;
    }
}

int n, m;
vector <int> graph[nax];
vector <int> tree, depth;
vector <int> anc[L]; //anc[i][v] = (2^i)-th ancestor of v

void fill_anc() {
	stack <int> st;
	st.push(1);

	anc[0][1] = 1;

	while (!st.empty()) {
		int v = st.top();

		st.pop();

		anc[0][v] = v;
		anc[1][v] = tree[v];

		for (int i = 2; i < L; i++) {
			anc[i][v] = anc[i - 1][anc[i - 1][v]];
		}

		for (int &u : graph[v]) {
			if (u != tree[v]) {
				st.push(u);
			}			
		}
	}
}

void build_tree() {
	queue <pair<int, int>> Q;
	Q.push({1, 0});
	depth[1] = 0;

	while (!Q.empty()) {
		int v = Q.front().first;
		int par = Q.front().second;

		Q.pop();

		tree[v] = par;
		
		for (int &u : graph[v]) {
			if (u != par) {
				depth[u] = depth[v] + 1;
				Q.push({u, v});
			}
		}
	}

	fill_anc();
}

pair <int, int> _lca(int &pa, int &pb) {
    if (depth[pa] < depth[pb]) {
		swap(pa, pb);
	}

	int a = pa, b = pb;

	while (depth[a] != depth[b] && depth[a] > depth[b] + 1) {
		int pa = a;
		for (int i = 1; i < L; i++) {
			if (depth[anc[i][a]] < depth[b] + 1) {
				break;
			}
			pa = anc[i][a];
		}

		a = pa;
	}

	if (depth[a] != depth[b] && tree[a] == b) {
		return {a, a};
	}
	else if (depth[a] == depth[b] + 1) {
		a = tree[a];
	}

	while (tree[a] != tree[b]) {
		int pa = a;
		int pb = b;

		for (int i = 0; i < L - 1 && tree[anc[i + 1][a]] != tree[anc[i + 1][b]]; i++) {
			pa = anc[i][a];
			pb = anc[i][b];
		}

		assert (tree[pa] != tree[pb]);
		
		a = tree[pa];
		b = tree[pb];
	}

	return {a, b};
}

void join_lca(int lca, int v) {
	while (find_set(lca) != find_set(v)) {
		int tmp = 1;
		while (tmp < L - 1 && find_set(anc[tmp + 1][v]) == find_set(v)) {
			tmp++;
		}

		union_set(v, anc[tmp][v]);
		v = anc[tmp][v];
	}
}

void join(int a, int b) {
	auto lca = _lca(a, b);
	union_set(lca.first, lca.second);
	if (a != tree[lca.first]) join_lca(lca.first, a);
	if (b != tree[lca.first]) join_lca(lca.second, b);
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	tree.resize(n + 1);
	depth.resize(n + 1);
	for(int i = 0; i < L; i++) anc[i].resize(n + 1);

	for (int i = 1; i <= n; i++) make_set(i);

	for (int u, v, i = 0; i < n - 1; i++) {
		cin >> u >> v;

		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	build_tree();

	cin >> m;
	for (int a, b, i = 0; i < m; i++) {
		cin >> a >> b;
		join(a, b);
	}

	int cnt = 0;
	vector <bool> sets (n + 1);
	for (int i = 2; i <= n; i++) {
		int curSet = find_set(i);
		cnt += !(sets[curSet]);
		sets[curSet] = true;
	}

	cout << fast_exp(2, cnt) << "\n";
}
