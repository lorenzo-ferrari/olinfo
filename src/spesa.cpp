#include <bits/stdc++.h>
#define MAXN 10000
#define INF 2147483647
using namespace std;
typedef pair <int, int> pii;
ifstream in ("input.txt");
ofstream out ("output.txt");

int main()
{
    vector <pii> graph[MAXN+1];
    bitset <MAXN+5> s;

    int N, M, K, u, v;

    in >> N >> M >> K;
    
    for(int i = 0; i < K; i++)
    {
        in >> u;
        s[u] = 1;
    }

    for(int i = 0; i < M; i++)
    {
        in >> u >> v;
        graph[u].push_back({v, 1});
        graph[v].push_back({u, 1});
    }

    int dist_sor[MAXN+1], dist_des[MAXN+1];

    fill(dist_sor, dist_sor+N+1, INF);
    fill(dist_des, dist_des+N+1, INF);

    priority_queue <pii> Q;

    dist_sor[1] = 0;
    dist_des[N] = 0;

    Q.push({0, 1});

    while(!Q.empty())
    {
        int cur = Q.top().second;
        int cur_w = -Q.top().first;

        Q.pop();

        for(int i = 0; i < graph[cur].size(); i++)
        {
            int temp = graph[cur][i].first;
            int temp_w = graph[cur][i].second;

            if(dist_sor[temp] > cur_w + temp_w)
            {
                dist_sor[temp] = cur_w + temp_w;
                Q.push({-dist_sor[temp], temp});
            }
        }
    }

    Q.push({0, N});

    while(!Q.empty())
    {
        int cur = Q.top().second;
        int cur_w = -Q.top().first;

        Q.pop();

        for(int i = 0; i < graph[cur].size(); i++)
        {
            int temp = graph[cur][i].first;
            int temp_w = graph[cur][i].second;

            if(dist_des[temp] > cur_w + temp_w)
            {
                dist_des[temp] = cur_w + temp_w;
                Q.push({-dist_des[temp], temp});
            }
        }
    }

    int best_track = INF;

    for(int i = 1; i <= N; i++)
        if(s[i])
            best_track = min(best_track, dist_des[i]+dist_sor[i]);

    out << best_track;
}