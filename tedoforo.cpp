#include <bits/stdc++.h>
#define MAXN 1000
using namespace std;

int main(){
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
    vector <pair<int, int>> graph[MAXN];
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0, u, v, w; i < m; i++){
        scanf("%d%d%d", &u, &v, &w);
        graph[--u].push_back({--v, w});
        graph[v].push_back({u, w});
    }

    int dist[MAXN]; dist[0] = 0;
    fill(dist+1, dist+n, 1000000000);
    priority_queue <pair<int, int>> Q;
    Q.push({0, 0});

    while(!Q.empty()){
        int cur = Q.top().second;
        int d = -Q.top().first;
        Q.pop();
        for(int i = 0; i < graph[cur].size(); i++){
            int v = graph[cur][i].first;
            int w = graph[cur][i].second;
            if(dist[v] > d+w){
                dist[v] = d+w;
                Q.push({-dist[v], v});
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++)
        ans += (dist[i] <= 10*i+10);
    printf("%d\n", ans);    
}