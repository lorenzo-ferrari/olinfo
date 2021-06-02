#include <array>
#include <queue>
#include <vector>
#include <iostream>
#pragma GCC optimize ("O3")
using namespace std;

long long costruisci(int N, int M, vector<long long>& H, vector<int>& A,vector<int>& B, vector<int>& C) {
    vector<vector<array<int64_t, 2>>> g(N);
    for (int i = 0; i < M; i++)
        g[A[i]].push_back({B[i], C[i]});
    
    priority_queue <array<int64_t, 2>> Q;

    for (int i = 0; i < N; i++)
        Q.push({-H[i], i});
    
    while (!Q.empty()) {
        int64_t h = -Q.top()[0];
        int64_t v =  Q.top()[1];

        Q.pop();

        for (auto e : g[v]) {
            if (H[e[0]] > h + e[1]) {
                H[e[0]] = h + e[1];
                Q.push({-H[e[0]], e[0]});
            }
        }
    }

    long long sum = 0;
    for (long long i : H) sum += i;
    
    return sum;
}
