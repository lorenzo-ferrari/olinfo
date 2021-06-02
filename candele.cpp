#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

#define F first
#define S second

void brucia(int n, vector<int> &m, vector<int> &b, vector<long long> &t) {
	vector <pair<long long, long long>> c(n);
	for (int i = 0; i < n; i++)
		c[i] = {m[i], i};
	sort(c.begin(), c.end());

	stack <pair<long long, long long>> st;
	vector <vector<pair<long long, long long>>> g(n);
	for (auto x : c) {
		while (!st.empty() && b[x.S] <= st.top().F) {
			g[x.S].push_back({st.top().S, x.F - st.top().F});
			// cout << x.S << " to " << st.top().S << "\n";
			st.pop();
		}
		st.push(x);
	}

	while (!st.empty())
		st.pop();

	reverse(c.begin(), c.end());

	for (auto x : c) {
		while (!st.empty() && b[x.S] >= st.top().F) {
			g[x.S].push_back({st.top().S, st.top().F - x.F});
			// cout << x.S << " to " << st.top().S << "\n";
			st.pop();
		}
		st.push(x);
	}

	// for (int i = 0; i < n; i++) {
	// 	cout << i << ": ";
	// 	for (auto e : g[i]) {
	// 		cout << "{" << e.F << "," << e.S << "} ";
	// 	}
	// 	cout << "\n";
	// }

	fill(t.begin(), t.end(), -1);

	priority_queue <pair<long long, long long>> Q;
	Q.push({0, 0});
	t[0] = 0;

	while (!Q.empty()) {
		int v = Q.top().S;

		Q.pop();

		for (auto e : g[v]) {
			if (t[e.F] == -1 || t[e.F] > t[v] + e.S) {
				t[e.F] = t[v] + e.S;
				Q.push({-t[e.F], e.F});
			}
		}
	}
}