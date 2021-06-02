#include <queue>
#include <vector>
#define MAXN 100000
#pragma GCC optimize ("O3")
using namespace std;

void Analizza(int N, int M, int A[], int B[], int T[]) {
    T[0] = 0; T[1] = 0; T[2] = 0;
    int deg[MAXN + 1] {};
    bool vis[MAXN + 1] {};
    vector <int> graph[MAXN + 1];
        
    for (int i = 0; i < M; i++) {
        graph[A[i]].push_back(B[i]);
        graph[B[i]].push_back(A[i]);
        deg[A[i]]++;
        deg[B[i]]++;
    }

    queue <int> st;
    for (int i = 1; i <= N; i++) {
        if (!vis[i]) {
            int n = 0, dg2 = 0, dg1 = 0, dgMAX = 0;
            vis[i] = true;
            st.push(i);
            while (!st.empty()) {
                int v = st.front();
                n++;
                dg2 += (deg[v] == 2);
                dg1 += (deg[v] == 1);
                dgMAX = max(dgMAX, deg[v]);
                st.pop();
                for (int u : graph[v]) {
                    if (!vis[u]) {
                        vis[u] = true;
                        st.push(u);
                    }
                }
            }
            if (n == 1)
                continue;
            T[0] += (dg1 == 2 && dg2 == n - 2);
            T[1] += (dg2 == n);
            T[2] += (dg1 == n - 1 && dgMAX > 2);
        }
    }
}
