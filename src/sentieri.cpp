#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int N = 105;
const int INF = 1e9;

int dist[N]; // dist[v] : n archi bollenti tra node e v

vector<vector<pair<int, int>>> g;

// pair<tipo_1, tipo_2>
// pair<int, bool> a = {42, false};
// a.first // 42
// a.second // false

void bfs(int node) {
		fill(dist, dist + N, INF); // for (int i = 0; i < N; i++) dist[i] = INF;

    queue<int> q;

    q.push(node);
    dist[node] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i=0; i<g[u].size(); i++) {
            int v = g[u][i].first;
            int w = g[u][i].second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                q.push(v);
            }
        }
    }
}

int main() {
#ifdef EVAL
	ifstream cin ("input.txt");
	ofstream cout ("output.txt");
#endif

		int n, a, b;
		cin >> n >> a >> b;

		g.resize(n+1);

		for (int i = 0; i < a; i++) {
			int u, v;
			cin >> u >> v;
			g[u].push_back({v, 0});
			g[v].push_back({u, 0});
		}
		for (int i = 0; i < b; i++) {
			int u, v;
			cin >> u >> v;
			g[u].push_back({v, 1});
			g[v].push_back({u, 1});
		}

    bfs(1);

    cout << dist[n] << "\n";
}
