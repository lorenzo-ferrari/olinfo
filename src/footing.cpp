#include <bits/stdc++.h>
#define INF 1000000001
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#include <bits/stdc++.h>
#define INF 1000000000
using namespace std;
typedef pair<int,int> pii;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m, u, v, w, min_ciclo = INF;
    vector <pii> graph[10001];
    vector <pair<pii, int>> edges;

    scanf("%d %d", &n, &m);

    for(int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});

        edges.push_back({{u, v}, w});
    }

    vector <int> dist (n+1, INF);
    priority_queue <pii> Q;
    int cur, cur_w, temp, temp_w;

    for(int arco = 0; arco < m; arco++)
    {
        u = edges[arco].first.first;
        v = edges[arco].first.second;

        fill(dist.begin(), dist.end(), INF);
        dist[u] = 0;
        Q.push({0, u});

        while(!Q.empty())
        {
            cur = Q.top().second;
            cur_w = -Q.top().first;

            Q.pop();

            if(cur_w >= min_ciclo)
                continue;

            for(int i = 0; i < graph[cur].size(); i++)
            {
                temp = graph[cur][i].first;
                temp_w = graph[cur][i].second;

                if((cur != u || temp != v) && (cur != v || temp != u) && dist[temp] > cur_w + temp_w && cur_w + temp_w < min_ciclo)
                {
                    dist[temp] = cur_w + temp_w;
                    Q.push({-dist[temp], temp});
                }
            }
        }

        min_ciclo = min(min_ciclo, dist[v] + edges[arco].second);       
    }

    printf("%d\n", min_ciclo);    
}