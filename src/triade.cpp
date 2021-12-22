#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m, ans = 0;
    set <int> adj[MAXN];
    pair<int, int> edg[2*MAXN];
    int deg[MAXN]{ };
    scanf("%d%d", &m, &n);
    for(int i = 0, u, v; i < m; i++){
        scanf("%d%d", &u, &v);
        deg[--u]++;
        deg[--v]++;
        adj[u].insert(v);
        adj[v].insert(u);
        edg[i] = {u, v};
    }

    for(int i = 0, a, b; i < m; i++){
        a = edg[i].first;
        b = edg[i].second;
        if(deg[a] > deg[b]) swap(a, b);
        for(int c : adj[a]) ans += (adj[c].find(b) != adj[c].end());
    }

    printf("%d\n", ans/3);
}