#include <bits/stdc++.h>

#define MAXN 100005
#define INF 1000000000

using namespace std;

typedef pair <int, int> pii;

inline int get_int()
{
    int n = 0; 
    char c = getchar_unlocked();
    while(c >= '0')
    {
        n = 10*n+c-'0';
        c = getchar_unlocked();
    }

    return n;
}

int N, M;
vector <pii> graph[MAXN]; //archi invertiti
bitset <MAXN> vis[2];
int dist[MAXN][2];


int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    N = get_int();
    M = get_int();

    for(int i = 0; i <= N; i++)
    {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    int a, b, p;

    for(int i = 0; i < M; i++)
    {
        a = get_int();
        b = get_int();
        p = get_int();

        if((a == 1 && b == N) || (a == N && b == 1))
        {
            printf("%d", 0);
            return 0;
        }

        graph[a].push_back({b, p});
    }

    priority_queue <pair<int, pii>> Q;
    int cur, maxmax, k;
    Q.push({0, {1, 0}});

    while(!Q.empty())
    {
        maxmax = -Q.top().first;
        cur = Q.top().second.first;
        k = Q.top().second.second;

        Q.pop();

        for(int i = 0; i < graph[cur].size(); i++)
        {
            int temp = graph[cur][i].first;
            int temp_p = graph[cur][i].second;

            if(dist[temp][k] > max(temp_p, maxmax))
            {
                dist[temp][k] = max(temp_p, maxmax);
                Q.push({-dist[temp][k], {temp, k}});
            }

            if(k == 0 & dist[temp][k+1] > maxmax)
            {
                dist[temp][k+1] = maxmax;
                Q.push({-dist[temp][k+1], {temp, k+1}});
            }
        }
    }

    cout << dist[N][1];
}

