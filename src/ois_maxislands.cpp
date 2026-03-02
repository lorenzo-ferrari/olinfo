#include "bits/stdc++.h"
using namespace std;

constexpr int INF = 1e9;
constexpr array<int, 4> dx{ 0,-1, 0,+1};
constexpr array<int, 4> dy{+1, 0,-1, 0};

int bfs(int s, int t, const vector<vector<int>>& adj, vector<map<int, int>>& c, vector<int>& par) {
	fill(begin(par), end(par), -1);
	queue<array<int, 2>> Q;
	Q.push({s, INF});
	while (!Q.empty()) {
		auto [u, flow] = Q.front();
		Q.pop();
		for (int v : adj[u]) {
			int new_flow = min(c[u][v], flow);
			if (new_flow > 0 && par[v] == -1) {
				par[v] = u;
				if (v == t)
					return new_flow;
				Q.push({v, new_flow});
			}
		}
	}
	return 0;
}

int maxflow(int s, int t, vector<vector<int>>& adj, vector<map<int, int>> c) {
	int flow = 0;
	int new_flow;
	vector<int> par(adj.size());
	while ((new_flow = bfs(s, t, adj, c, par))) {
		flow += new_flow;
		int cur = t;
		while (cur != s) {
			int prv = par[cur];
			c[prv][cur] -= new_flow;
			c[cur][prv] += new_flow;
			cur = prv;
		}
	}
	return flow;
}

int main() {
	int n; cin >> n;
	int m; cin >> m;

	auto exists = [&](int i, int j) -> bool {
		return 0 <= i && i < n && 0 <= j && j < m;
	};

	vector<vector<char>> g(n, vector<char>(m));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			cin >> g[i][j];

	// assegno i '?' banali
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (g[i][j] == '?') {
				for (int k = 0; k < 4; ++k) {
					int ni = i + dx[k];
					int nj = j + dy[k];
					if (exists(ni, nj) && g[ni][nj] == '1')
						g[i][j] = '0';
				}
			}
		}
	}

	// conto le componenti connesse gia' esistenti
	int cnt = 0;
	{
		vector<vector<bool>> vis(n, vector<bool>(m));
		auto dfs = [&](auto&& self, int i, int j) -> void {
			vis[i][j] = true;
			for (int k = 0; k < 4; ++k) {
				int ni = i + dx[k];
				int nj = j + dy[k];
				if (exists(ni, nj) && g[ni][nj] == '1' && !vis[ni][nj])
					self(self, ni, nj);
			}
		};
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (g[i][j] == '1' && !vis[i][j]) {
					++cnt;
					dfs(dfs, i, j);
				}
			}
		}
	}

	// massimizzo le isole nella parte restante di mappa
	int max_ind_set = 0;
	{
		vector<vector<int>> coord2idx(n, vector<int>(m));

		int V = 0;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				if (g[i][j] == '?')
					coord2idx[i][j] = V++;
		V += 2;
		// s: V - 2
		// t: V - 1
		vector<vector<int>> adj(V);
		vector<map<int, int>> c(V);

		auto add_edge = [&](int a, int b) -> void {
			adj[a].push_back(b);
			adj[b].push_back(a);
			c[a][b] = 1;
		};

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (g[i][j] == '?') {
					if ((i + j) & 1)
						add_edge(V - 2, coord2idx[i][j]);
					else
						add_edge(coord2idx[i][j], V - 1);
					for (int k = 0; k < 4; ++k) {
						int ni = i + dx[k];
						int nj = j + dy[k];
						if (exists(ni, nj) && g[ni][nj] == '?') {
							if ((i + j) & 1)
								add_edge(coord2idx[i][j], coord2idx[ni][nj]);
							else
								add_edge(coord2idx[ni][nj], coord2idx[i][j]);
						}
					}
				}
			}
		}

		max_ind_set = V - 2 - maxflow(V - 2, V - 1, adj, c);
	}

	// answer = cnt + max_indipendent_set
	cout << cnt + max_ind_set << "\n";
}
