#include <functional>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct pt {
	int m;
	std::vector<int> c;
	pt() {}
	pt(int M) {
		m = M;
		c.resize(M);
	}
};

std::istream& operator >>(std::istream &in, pt &a) {
	for (int &x : a.c)
		in >> x;
	return in;
}
bool operator ^(pt &a, pt &b) {
	int diff = 0;
	for (int i = 0; diff < 2 && i < a.m; i++)
		diff += abs(a.c[i] - b.c[i]);
	return diff < 2;
}

const int INF = 1e9;
bool dfs(int n, int s, int e, std::vector<std::vector<int16_t>> &g, std::vector<std::vector<bool>> &c, std::vector<int16_t> &par) {
	par.assign(n, -1);
	std::stack<int> st;
	st.push(s);
	while (!st.empty()) {
		int v = st.top();
		st.pop();

		for (int u : g[v])
			if (par[u] == -1 && c[v][u]) {
				par[u] = v;
				if (u == e)
					return true;
				st.push(u);
			}
	}

	return 0;
}

int maxflow(int16_t n, int16_t s, int16_t e, std::vector<std::vector<int16_t>> &g, std::vector<std::vector<bool>> &c) {
	int flow = 0;
	std::vector<int16_t> par;
	while (dfs(n, s, e, g, c, par)) {
		flow++;
		int cur = e;
		while (cur != s) {
			int prv = par[cur];
			c[prv][cur] = 0;
			c[cur][prv] = 1;
			cur = prv;
		}
	}

	return flow;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N, M, B;
	std::cin >> N >> M >> B;

	std::vector<pt> P(N, pt(M));
	std::vector<std::vector<int16_t>> g(N);
	for (pt &x : P)
		std::cin >> x;
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
			if (P[i] ^ P[j]) {
				g[i].push_back(j);
				g[j].push_back(i);
			}

	std::vector<bool> col(N, -1);
{
	std::vector<bool> vis(N);
	std::function<void(int)> dfs = [&](int v) {
		vis[v] = true;
		for (int u : g[v])
			if (!vis[u]) {
				col[u] = 1 - col[v];
				dfs(u);
			}
	};

	for (int i = 0; i < N; i++) {
		if (!vis[i]) {
			col[i] = 1;
			dfs(i);
		}
	}
}

	g.resize(N + 2); // add 2 empty vectors
	std::vector<std::vector<bool>> C(N + 2, std::vector<bool> (N + 2));
	for (int i = 0; i < N; i++) {
		if (col[i] == 1) {
			for (int j : g[i])
				if (col[j] ^ col[i])
					C[i][j] = 1;
			C[N][i] = 1;
			g[N].push_back(i);
			g[i].push_back(N);
		} else {
			for (int j : g[i])
				if (col[j] ^ col[i])
			C[i][N + 1] = 1;
			g[N + 1].push_back(i);
			g[i].push_back(N + 1);
		}
	}

	int ans = maxflow(N + 2, N, N + 1, g, C);
	std::cout << ans << "\n";
}
