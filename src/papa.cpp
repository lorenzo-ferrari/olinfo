#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

const int K = 7;
const int N = 1500;

int l[N];
int r[N];
string s[N];

bool compatible(int &a, int &b) {
	int tl = max(l[a], l[b]);
	int tr = min(r[a], r[b]);
	if (tl >= tr)
		return true;
	for (int i = 0, idx; i < K; ++i) {
		idx = tl + rand() % (tr-tl);
		if (s[a][idx-l[a]] != '?' && s[b][idx-l[b]] != '?' && s[a][idx-l[a]] != s[b][idx-l[b]])
			return false;
	}
	return true;
}

bool color(int n, vector<vector<int>> &g) {
	vector<int> col(n);
	queue<int> Q;
	for (int i = 0; i < n; i++) {
		if (col[i] == 0) {
			col[i] = 1;
			Q.push(i);
			while (!Q.empty()) {
				int v = Q.front();
				Q.pop();
				for (int u : g[v]) {
					if (col[u] == 0) {
						col[u] = 3-col[v];
						Q.push(u);
					} else if (col[u] == col[v]) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

void solve(int n) {
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i] >> s[i];
		r[i] += l[i];
	}
	vector<vector<int>> g(n);
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (!compatible(i, j)) {
				g[i].push_back(j);
				g[j].push_back(i);
			}
		}
	}
	cout << 1-color(n, g) << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int t;
	cin >> t;
	vector<int> m(t);
	for (int &i : m)
		cin >> i;
	for (int i = 0; i < t; i++)
		solve(m[i]);
}
