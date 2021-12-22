#include <set>
#include <queue>
#include <vector>
#include <cassert>
using namespace std;

void nuovo_gruppo();

void aggiungi(int bambino);

void smista(int N, int nemico[]) {
	vector <set<int>> g(N);
	for (int i = 0; i < N; i++) {
		g[i].insert(nemico[i]);
		g[nemico[i]].insert(i);
	}

	queue <int> Q;
	vector <int> s(N, -1);
	vector <bool> vis(N);

	for (int i = 0; i < N; i++) {
		if (!vis[i]) {
			vis[i] = true;
			s[i] = 0;
			Q.push(i);
			while (!Q.empty()) {
				int v = Q.front();
				Q.pop();
				for (int u : g[v]) {
					if (vis[u]) continue;

					bool b0 = true, b1 = true, b2 = true;
					for (int x : g[u]) {
						if (s[x] == 0) b0 = false;
						else if (s[x] == 1) b1 = false;
						else if (s[x] == 2) b2 = false;
					}

					vis[u] = true;
					if (b0) {s[u] = 0; Q.push(u);}
					else if (b1) {s[u] = 1; Q.push(u);}
					else if (b2) {s[u] = 2; Q.push(u);}
					else {assert(0);}
				}
			}
		}
	}

	// for (int i = 0; i < N; i++) cout << s[i] << " "; cout << "\n";

	vector <int> gruppi[3];
	for (int i = 0; i < N; i++)
		gruppi[s[i]].push_back(i);

	for (int i = 0; i < 3; i++) {
		if (!gruppi[i].empty()) nuovo_gruppo();
		for (int v : gruppi[i]) aggiungi(v);
	}
}
