#include <bits/stdc++.h>

#define INF 2147483647
#define MAXN 50000

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

typedef pair <int, int> pii;

int N, S, E, M, s, t0, e, t1;
vector <pair <int, pii>> graph[MAXN];
int time_distance[MAXN];

int main()
{
    in >> N;
    in >> S >> E;
    in >> M;

    fill(time_distance, time_distance+N, INF);

    for(int i = 0; i < M; i++)
    {
        in >> s >> t0 >> e >> t1;
        graph[s].push_back({e, {t0, t1}});
    }

    priority_queue <pii> Q;
    Q.push({0, S});
    time_distance[S] = 0;

    int cur_time, cur_s, cur_e, cur_t0, cur_t1;

    while(!Q.empty())
    {
        cur_time = -Q.top().first;
        cur_s = Q.top().second;

        Q.pop();

        if(time_distance[cur_s] < cur_time)
            continue;

        time_distance[cur_s] = cur_time;

        for(int i = 0; i < graph[cur_s].size(); i++)
        {
            cur_t0 = graph[cur_s][i].second.first;

            if(cur_t0 >= cur_time) 
            {
                cur_e = graph[cur_s][i].first;
                cur_t1 = graph[cur_s][i].second.second;

                if(cur_t1 < time_distance[cur_e]) 
                {
                    time_distance[cur_e];
                    Q.push({-cur_t1, cur_e});
                }
            }
        }
    }

    if(time_distance[E] == INF)
        out << "IMPOSSIBLE";
    else
        out << time_distance[E];

    in.close();
    out.close();
}
