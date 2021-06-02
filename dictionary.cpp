#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

int n;

unordered_map <string, int> sToIdx;
unordered_map <int, string> idxToS;

vector <int> in; // how many unknown words reach me
vector <int> out; // how many unknown word I reach
vector <bool> vis; // do I know this word
vector <vector<int>> g; // graph
vector <int> ans;

clock_t clockBegin;

inline void input();
inline void debug();
inline void print();
inline void dfs(int &v);
inline bool cmp(int &a, int &b);

inline void solve() {
	for (int i = 0; i < n; i++) {
		if (!vis[i] && in[i] == 0) {
			dfs(i);
			ans.push_back(i);
		}
	}

	vector <int> p;
	vector <int> in0 = in;
	vector <int> ans0 = ans;
	vector <bool> vis0 = vis;

	for (int i = 0; i < n; i++)
		if (!vis[i] && out[i])
			p.push_back(i);

	mt19937 generator;

	sort(p.begin(), p.end(), &cmp);
	vector <int> best (n+1);
	while (clock() - clockBegin <= 9.98 * CLOCKS_PER_SEC) {
		for (int &i : p) {
			if (!vis[i]) {
				dfs(i);
				ans.push_back(i);
			}
			if (ans.size() >= best.size())
				break;
		}

		if (ans.size() < best.size())
			best = ans;

		// random_shuffle(p.begin(), p.end());
		shuffle(p.begin(), p.end(), generator);

		vis = vis0;
		ans = ans0;
		in = in0;
	}

	ans = best;
}

int main() {
	clockBegin = clock();
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	srand(time(NULL));

	input();
	solve();
	print();
}

inline void input() {
	int d;
	cin >> n >> d;

	g.resize(n);
	in.resize(n);
	vis.resize(n);
	out.resize(n);

	int num;
	string w;
	string toDef;
	unordered_set <string> seen;
	while (d--) {
		cin >> toDef;
		if (seen.find(toDef) == seen.end()) {
			sToIdx[toDef] = seen.size();
			idxToS[seen.size()] = toDef;
			seen.insert(toDef);
		}
		int v = sToIdx[toDef];
		cin >> num;
		while (num--) {
			cin >> w;
			if (seen.find(w) == seen.end()) {
				sToIdx[w] = seen.size();
				idxToS[seen.size()] = w;
				seen.insert(w);
			}
			int u = sToIdx[w];
			g[u].push_back(v);
			++in[v];
			++out[u];
		}
	}
}

inline void dfs(int &v) {
	vis[v] = true;
	for (int &u : g[v])
		if (!vis[u] && --in[u] == 0) {
			dfs(u);
		}
}

inline bool cmp(int &a, int &b) {
	return out[a] > out[b];
}

inline void print() {
	cout << ans.size() << "\n";
	for (auto x : ans)
		cout << idxToS[x] << "\n";
}
