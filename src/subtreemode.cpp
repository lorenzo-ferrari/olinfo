#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

static constexpr size_t N = 1e6 + 5;

static int label[N];
static int f[N];
vector<int> g[N];
vector<int> ans;

struct emap {
	int mode;
	int cnt;
	unordered_map<int, int> occ;
    emap() {}
	emap(int x) : mode(x), cnt(1) { occ[x] = 1; }
	int size() const { return occ.size(); }
    void merge(const emap& oth) {
        for (const auto& [x, fr] : oth.occ) {
            if (f[x] < cnt || (f[x] == cnt && x > mode)) {
                continue;
            }
            int new_cnt = (occ[x] += fr);
            if (new_cnt > cnt) mode = x, cnt = new_cnt;
            else if (new_cnt == cnt && x < mode) mode = x;
        }
    }
};

static emap dfs(int v) {
	emap em(label[v]);
	for (int u : g[v]) {
		emap em2 = dfs(u);
		if (em.size() < em2.size())
             swap(em, em2);
        em.merge(em2);
	}
	ans[v] = em.mode;
	return em;
}

vector<int> solve(int n, vector<int> p, vector<int> a) {
	ans.resize(n);
	for (int i = 1; i < n; i++)
		g[p[i]].push_back(i);
	for (int i = 0; i < n; i++) {
		label[i] = a[i];
        ++f[a[i]];
    }
	dfs(0);
	return ans;
}
