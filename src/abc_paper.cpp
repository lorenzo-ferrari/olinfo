#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int NAX = 75042;

int p[NAX];

int find_set(int v) { return p[v] == v ? v : p[v] = find_set(p[v]); }

void union_set(int a, int b) {
  a = find_set(a);
  b = find_set(b);

  p[b] = a;
}

vector<int> g[NAX];
vector<int> gr[NAX];
vector <int> ord;
bool vis[NAX];

int t_set = -1;

void dfs1(int v) {
  vis[v] = true;
  for (int u : g[v])
    if (!vis[u])
      dfs1(u);
  ord.push_back(v);
}

void dfs2(int v) {
  vis[v] = true;
	// cout << v << " ";
  union_set(t_set, v);
  for (int u : gr[v])
    if (!vis[u])
      dfs2(u);
}

int paper(int n, int m, int a[], int b[]) {
	for (int i = 0; i < m; i++) {
    a[i]--, b[i]--;
    g[a[i]].push_back(b[i]);
    gr[b[i]].push_back(a[i]);
  }

	for (int i = 0; i < n; i++)
    if (!vis[i])
      dfs1(i);
  fill(vis, vis + n, false);
  reverse(ord.begin(), ord.end());
  for (int i = 0; i < n; i++)
    p[i] = i;
  for (int v : ord) {
    if (!vis[v]) {
      t_set = v;
      dfs2(v);
			// cout << "\n";
    }
  }

  // componenti fortemente connesse nello stesso set
	map <int, int> deg;
	map <int, set<int>> arc;
	for (int i = 0; i < n; i++) {
		deg[find_set(i)] += 0;
		for (int u : g[i]) {
			if (find_set(u) != find_set(i)) {
				arc[find_set(i)].insert(find_set(u));
				deg[find_set(u)]++;
			}
		}
	}

	// for (auto x : arc) {
	// 	cout << x.first << ": ";
	// 	for (int v : x.second) {
	// 		cout << v << " ";
	// 	}
	// 	cout << "\n";
	// }

	bool sol = true;
	int source = -1;
	for (auto x : deg) {
		if (x.second == 0) {
			if (source == -1)
				source = x.first;
			else
				sol = false;
		}
	}

	if (sol) {
		int ans = 0;
		for (int i = 0; i < n; i++)
			ans += (find_set(i) == source);
		return ans;
	} else {
		return 0;
	}
}