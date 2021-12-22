#include <bits/stdc++.h>

#define MAXN 10000
#define MAXK 100

using namespace std;

typedef pair<int, int> pii;

ifstream in ("input.txt");
ofstream out ("output.txt");

int N, K, M, sor, des, w;
int dist[MAXN][MAXK+1];
vector <pii> graph[MAXN];

int main()
{
    in >> K >> N >> M;

    for(int i = 0; i < M; i++) {
        in >> sor >> des >> w;
        graph[sor].push_back({des, w});
    }

    queue <pii> Q;
    Q.push({0, 0}); //voli e nodo fino ad ora
    int cur, voli, tempNodo, tempPeso;
    //DIJKSTRA
    while(!Q.empty()) {
        cur = Q.front().first;
        voli = Q.front().second;

        Q.pop();

        if(voli >= K)
            continue;

        for(int i = 0; i < graph[cur].size(); i++) {
            tempNodo = graph[cur][i].first;
            tempPeso = graph[cur][i].second;

            if(dist[cur][voli] + tempPeso > dist[tempNodo][voli+1]) {

                dist[tempNodo][voli+1] = dist[cur][voli] + tempPeso;
                Q.push({tempNodo, voli+1});
            }
        }
    }

    out << dist[0][K];
}
