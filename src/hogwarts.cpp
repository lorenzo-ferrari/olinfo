#include <array>
#include <queue>
#include <vector>
#pragma GCC optimize("O3")
using namespace std;

const int INF = 1e9 + 69;

int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]) {
    vector <vector<array<int, 3>>> graph(N);

    for (int i = 0; i < M; i++) {
        graph[A[i]].push_back({B[i], inizio[i], fine[i]});
        graph[B[i]].push_back({A[i], inizio[i], fine[i]});
    }

    vector <bool> vis(N);
    vector <int> t(N, INF);
    priority_queue<array<int, 2>> Q;

    t[0] = 0;
    Q.push({0, 0});

    while (!Q.empty()) {
        int tt = -Q.top()[0];
        int v  =  Q.top()[1];

        Q.pop();

        if (vis[v])
            continue;
        vis[v] = true;

        for (auto e : graph[v]) {
            if (e[2] > tt && t[e[0]] > 1 + max(tt, e[1])) {
                t[e[0]] = 1 + max(tt, e[1]);
                Q.push({-t[e[0]], e[0]});
            }
        }
    }

    return (t[N - 1] == INF) ? -1 : t[N - 1];
}