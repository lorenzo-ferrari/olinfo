#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int N = 1e5 + 5;
const long long INF = 1e12;

long long dist[N];
bool vis[N] { false };
vector<vector<pair<int, int>>> g;

/*
bool minore(pair<int, int> a, pair<int, int> b) {
	if (a.first < b.first)
		return true;
	if (a.first == b.first && (a.second < b.second))
		return true;
	return false;
}
*/

// O(VlogV + E)
void dijkstra(int node) {
		fill(dist, dist + N, INF); // for (int i = 0; i < N; i++) dist[i] = INF;

    priority_queue<pair<long long, int>> Q;

    Q.push({0, node});
    dist[node] = 0;

    while (!Q.empty()) {
        int cur = Q.top().second;
        long long cur_dist = -Q.top().first;
        Q.pop();

				if (vis[cur])
					continue;
				vis[cur] = true;

        for (int i = 0; i < g[cur].size(); i++) {
            int v = g[cur][i].first;
            int w = g[cur][i].second;
            if (dist[v] > cur_dist + w) {
                dist[v] = cur_dist + w;
                Q.push({-dist[v], v});
            }
        }
    }
}

int main() {
#ifdef EVAL
	ifstream cin ("input.txt");
	ofstream cout ("output.txt");
#endif

		int n, m, s, e;
		cin >> n >> m >> s >> e;

		g.resize(n + 1);

		for (int i = 0; i < m; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			g[u].push_back({v, w});
		}

    dijkstra(s);

    cout << dist[e] << "\n";
}
