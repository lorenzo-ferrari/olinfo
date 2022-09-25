#include <array>
#include <queue>
#include <vector>
#include <algorithm>
#pragma GCC optimize ("O3")
using namespace std;

const int64_t INF = 1e15;

int n, k, t, s, ee;
// b, w, p, v
vector <vector<array<int64_t, 4>>> g;

inline int64_t tempo(int64_t vol) {
    int64_t minT = INF;
    vector <vector<int64_t>> d(n, vector <int64_t> (k + 1, INF));
    vector <vector<bool>> vis(n, vector <bool> (k + 1));

    priority_queue <array<int64_t, 3>> Q;
    Q.push({0, s, 0});
    d[s][0] = 0;
    while (!Q.empty()) {
        int64_t v  = Q.top()[1];
        int64_t tk = Q.top()[2];

        if (v == ee)
            return d[v][tk];

        Q.pop();

        if (vis[v][tk])
            continue;
        vis[v][tk] = true;

        for (auto e : g[v]) {
            if (e[3] <= vol && d[e[0]][tk] > d[v][tk] + e[1]) {
                d[e[0]][tk] = d[v][tk] + e[1];
                Q.push({-d[e[0]][tk], e[0], tk});
            }
            if (tk < k && d[e[0]][tk + 1] > d[v][tk] + e[2]) {
                d[e[0]][tk + 1] = d[v][tk] + e[2];
                Q.push({-d[e[0]][tk + 1], e[0], tk + 1});
            }
        }
    }

    return INF;
}

int32_t avoid_volunteers(int subtask, int N, int M, int K, int S, int E, int T, int A[], int B[], int W[], int P[], int V[]) {
    n = N, k = K, t = T, ee = E, s = S;
    g.resize(N);
    for (int i = 0; i < M; i++) {
        g[A[i]].push_back({B[i], W[i], P[i], V[i]});
        g[B[i]].push_back({A[i], W[i], P[i], V[i]});
    }

    int l = 0, r = 1e9 + 1, mid;
    while (l < r - 1) {
        mid = l + (r - l) / 2;
        if (tempo(mid) <= T) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    if (tempo(r) <= T) return r;
    return -1;
}