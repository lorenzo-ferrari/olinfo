#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#define MAXM 13005
#define INF 2000000000
using namespace std;
typedef pair<int, int> pii;

vector <pair <int, pii>> edges;
int parent[MAXM], rankk[MAXM];

void make_set(int v) {
    parent[v] = v;
}

int f_set(int v) {
    if(v == parent[v])
        return v;
    return parent[v] = f_set(parent[v]);
}

void union_set(int a, int b) {
    a = f_set(a);
    b = f_set(b);

    if(a != b) {
        if(rankk[a] < rankk[b])
            swap(a, b);
        parent[b] = a;
        if(rankk[a] == rankk[b])
            rankk[a]++;
    }

}

int alzati(int N, int M, int X[], int Y[])
{
    pii dist[MAXM];
    bitset <MAXM> tree = 0;
    tree[0] = 1;   

    int minimo = INF, idx, prev, tramite = 0;

    for(int i = 0; i < M; i++)
    {
        if(!tree[i])
        {
            int temp = (Y[i] == Y[0] || X[i] == X[0]) ? (abs(X[0]-X[i])+abs(Y[0]-Y[i]))/2 : (abs(X[0]-X[i])+abs(Y[0]-Y[i])-1)/2;
            
            dist[i] = {temp, 0};
            
            if(temp < minimo)
            {
                idx = i;
                minimo = temp;
            }
        }
        
        edges.push_back({X[i], {i+4, 0}});          //0 up
        edges.push_back({Y[i], {i+4, 1}});          //1 left
        edges.push_back({N-1-X[i], {i+4, 2}});      //2 down
        edges.push_back({N-1-Y[i], {i+4, 3}});      //3 right
    }

    for(int step = 1; step < M; step++)
    {
        tree[idx] = 1;
        prev = idx;
        edges.push_back({minimo, {tramite+4, idx+4}});
        minimo = INF;

        for(int i = 1; i < M; i++)
        {
            if(!tree[i])
            {
                int temp = (Y[i] == Y[prev] || X[i] == X[prev]) ? (abs(X[prev]-X[i])+abs(Y[prev]-Y[i]))/2 : (abs(X[prev]-X[i])+abs(Y[prev]-Y[i])-1)/2;

                if(dist[i].first > temp)
                    dist[i] = {temp, prev};
                
                if(dist[i].first < minimo)
                {
                    idx = i;
                    minimo = dist[i].first;
                    tramite = dist[i].second;
                }
            }
        }
    }

    for(int i = 0; i <= M+4; i++) make_set(i);

    sort(edges.begin(), edges.end());

    int sleep = 1;

    for(int i = 0; (f_set(0) != f_set(1) && f_set(0) != f_set(2) && f_set(1) != f_set(3) && f_set(2) != f_set(3)); i++)
    {
        int w = edges[i].first;
        int a = edges[i].second.first;
        int b = edges[i].second.second;

        union_set(a, b);
        sleep = max(sleep, w);
    }

    return sleep-1;
}