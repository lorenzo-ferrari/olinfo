#include <bits/stdc++.h>
#define MAXN 100000
using namespace std;
ifstream in ("input.txt");
ofstream out ("output.txt");

vector <int> graph[MAXN];
int T[MAXN], latest[MAXN];
int fine;

int late(int v)
{
    if(latest[v]) return latest[v];

    int minimo = fine;
    for(int i = 0; i < graph[v].size(); i++)
        minimo = min(minimo, late(graph[v][i]));

    return latest[v] = minimo-T[v]; 
}

int main()
{
    int N, k;
    vector <int> v;
    in >> N;
    for(int i = 0; i < N; i++)
        in >> T[i];
    
    for(int i = 0; i < N; i++)
    {
        in >> k;
        if(k == 0) v.push_back(i);
        for(int j = 0; j < k; j++)
        {
            int need;
            in >> need;
            graph[need].push_back(i);
        }
    }

    int dist[MAXN] { };
    queue <int> Q;
    for(int i = 0; i < v.size(); i++)
        Q.push(v[i]);

    while(!Q.empty())
    {
        int cur = Q.front();
        Q.pop();
        fine = max(fine, dist[cur] + T[cur]);
        for(int i = 0; i < graph[cur].size(); i++)
        {
            if(dist[graph[cur][i]] < dist[cur] + T[cur])
            {
                dist[graph[cur][i]] = dist[cur] + T[cur];
                Q.push(graph[cur][i]);
            }
        }
    }

    for(int i = 0; i < v.size(); i++)
        int _ = late(v[i]);

    for(int i = 0; i < N; i++)
        out << latest[i] << " ";
}