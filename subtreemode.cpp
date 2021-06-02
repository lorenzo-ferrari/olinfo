#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

struct emap {
	int mode;
	int cnt;
	unordered_map<int, int> occ;
	emap(): mode(-1), cnt(0){}
	int size() { return occ.size(); }
	void add(int x, int fr = 1) {
		occ[x] += fr;
		int new_cnt = occ[x];
		if (new_cnt > cnt) mode = x, cnt = new_cnt;
		if (new_cnt == cnt && x < mode) mode = x;
	}
};

int label[N];
vector<int> g[N];

vector<int> ans;

emap dfs(int v) {
	emap em;
	em.add(label[v]);

	for (int u : g[v]) {
		emap em2 = dfs(u);
		if (em.size() < em2.size())
			swap(em, em2);
		for (auto x : em2.occ)
			em.add(x.first, x.second);
	}

	ans[v] = em.mode;

	return em;
}

vector<int> solve(int n, vector<int> p, vector<int> a) {
	ans.resize(n);
	for (int i = 1; i < n; i++)
		g[p[i]].push_back(i);
	for (int i = 0; i < n; i++)
		label[i] = a[i];
	dfs(0);
	return ans;
}
