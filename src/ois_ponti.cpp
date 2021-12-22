#include <bits/stdc++.h>
using namespace std;

bool vis[10000];
vector <int> graph[10000];

void dfs(int v) {
    vis[v] = true;
    for (int u : graph[v])
        if (!vis[u])
            dfs(u);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    scanf("%d %d", &n, &m);
    
    for (int i = 0, v, u; i < m; i++) {
        scanf("%d %d", &v, &u);
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            ans++;
            dfs(i);
        }
    }

    printf("%d\n", ans - 1);
}