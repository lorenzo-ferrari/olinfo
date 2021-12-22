#include <queue>
#include <vector>
#include <iostream>
#pragma GCC optimize ("O3")
using namespace std;

const int N = 4e5;

int n;
int c[N], s[N], a[N];
int dp[N][2];
vector <int> g[N];
vector <int> t[N];

int solve(int i, int st) { //0->non necessario; 1->necessario
	if (dp[i][st]) return dp[i][st];
	int v1 = c[i];
	for (int u : t[i])
		v1 += solve(u, 0);
	if (st) return v1;

	int v0 = 0;
	for (int u : t[i])
		v0 += solve(u, 1);

	if (v1 < v0) {
		s[i] = 1;
		return dp[i][st] = v1;
	}
	return dp[i][st] = v0;
}

void dfs(int i, int p) {
	for (int u : g[i]) {
		if (u != p) {
			t[i].push_back(u);
			dfs(u, i);
		}
	}
}

int main() {
	#ifdef EVAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++) cin >> c[i];
	for (int i = 1, a, b; i < n; i++) {
		cin >> a >> b; a--, b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	dfs(0, -1);

	int ans = solve(0, 0);

	int quanti = 0;
	queue <int> Q;
	Q.push(0);

	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();

		if (s[v]) {
			a[v] = 1; quanti++;
			for (int u : t[v])
				Q.push(u);
		}
		else {
			for (int u : t[v]) {
				a[u] = 1; quanti++;
				for (int i : t[u])
					Q.push(i);
			}
		}
	}

	cout << quanti << "\n";
	for (int i = 0; i < n; i++)
		if (a[i])
			cout << i + 1 << " ";
	cout << "\n";
}
