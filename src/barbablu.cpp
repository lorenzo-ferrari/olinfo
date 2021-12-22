#include <bits/stdc++.h>

#define MAXN 30
#define INF 1000000000

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

typedef pair<int, int> pii;

int N, M, C, K;
vector <pii> graph[MAXN+1];
int dist[MAXN+1][21];
bool air[MAXN+1];

void fill_matrix()
{
    for(int i = 1; i <= N; i++)
        for(int j = 0; j < 21; j++)
            dist[i][j] = INF;
}

int main()
{
    in >> N >> M >> C >> K;

    fill_matrix();

    int stanza, i;

    for(i = 0; i < K; i++)
    {
        in >> stanza;
        air[stanza] = 1;
    }

    int v1, v2, l;

    for(i = 0; i < M; i++)
    {
        in >> v1 >> v2 >> l;

        if(l > 20)
            continue;

        graph[v1].push_back({v2, l});
        graph[v2].push_back({v1, l});
    }

    queue <pair<int, pii>> Q;
    Q.push({0, {1, 0}});

    int cur, curPercorso, totPercorso, temp, tempL;

    while(!Q.empty())
    {
        totPercorso = -Q.front().first;
        cur = Q.front().second.first;
        curPercorso = Q.front().second.second;

        Q.pop();

        if(dist[cur][curPercorso] < totPercorso)
            continue;
        dist[cur][curPercorso] = totPercorso;

        for(i = 0; i < graph[cur].size(); i++)
        {
            temp = graph[cur][i].first;
            tempL = graph[cur][i].second;

            if(air[cur] && totPercorso+tempL < dist[temp][tempL])
                Q.push({-(totPercorso+tempL), {temp, tempL}});
            else if(curPercorso+tempL <= 20 && totPercorso+tempL < dist[temp][curPercorso+tempL])
                Q.push({-(totPercorso+tempL), {temp, curPercorso+tempL}});
        }
    }

    int minimo = INF;

    for(i = 0; i < 21; i++)
        minimo = min(minimo, dist[C][i]);

    if(minimo == INF)
        out << -1;
    else
        out << minimo;

    in.close();
    out.close();
}
