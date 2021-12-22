#include <bits/stdc++.h>
#define MAXN 10000
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, u, v;
    int s[MAXN];
    bitset <MAXN> vis;
    vector <int> graph[MAXN];
    queue <int> Q;


    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        scanf("%d %d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i = 0; i < n; i++)
        if((s[i] = graph[i].size()) < 2)
            Q.push(i);

    while(!Q.empty()){
        u = Q.front();
        Q.pop();

        if(vis[u]) continue;
        vis[u] = 1;

        for(int i = 0; i < graph[u].size(); i++){
            v = graph[u][i];
            if(--s[v] < 2 && !vis[v])
                Q.push(v);
        }
    }

    int counter = 0;
    for(int i = 0; i < n; i++)
        counter += (s[i] >= 2);

    printf("%d\n", counter);
}