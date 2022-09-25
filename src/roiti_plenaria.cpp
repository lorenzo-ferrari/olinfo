#include <bits/stdc++.h>
#define INF 9223372036854775807
#define MAXN 30000
#define MAXK 10
using namespace std;
typedef pair<int64_t, int64_t> pii;
ifstream in ("input.txt");
ofstream out ("output.txt");

int main()
{
    int64_t N, M, K, u, v, w;
    in >> N >> M >> K;
    int64_t sedi[MAXK], P[MAXN];
    int64_t dist[MAXN][MAXK];
    vector <pii> graph[MAXN];

    for(int i = 0; i < K; i++)
        in >> sedi[i];
    
    for(int i = 0; i < K; i++)
        in >> P[i];

    for(int i = 0; i < M; i++)
    {
        in >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    for(int i = 0; i < N; i++) for(int j = 0; j < K; j++) dist[i][j] = INF;

    priority_queue <pii> Q;

    for(int i = 0; i < K; i++)
    {
        dist[sedi[i]][i] = 0;
        Q.push({0, sedi[i]});

        while(!Q.empty())
        {
            int64_t cur = Q.top().second;
            int64_t cur_w = -Q.top().first;

            Q.pop();

            for(int j = 0; j < graph[cur].size(); j++)
            {
                int temp = graph[cur][j].first;
                int temp_w = graph[cur][j].second;

                if(dist[temp][i] > cur_w + temp_w)
                {
                    dist[temp][i] = cur_w + temp_w;
                    Q.push({-dist[temp][i], temp});
                }
            }
        }
    }

    int64_t minimo = INF, counter = 0;

    for(int i = 0; i < N; i++)
    {
        int64_t temp_min = 0;
        for(int j = 0; j < K; j++)
            temp_min += dist[i][j]*P[j];
        
        if(temp_min < minimo)
            minimo = temp_min;
    }
    
    for(int i = 0; i < N; i++)
    {
        int64_t temp_min = 0;
        for(int j = 0; j < K; j++)
            temp_min += dist[i][j]*P[j];
        
        if(temp_min == minimo)
            counter++;
    }

    out << counter << "\n" << minimo << "\n";
}