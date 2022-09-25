#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> pii;

vector <pii> graph[100001];
int sor[100001];
int t[100001];

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int n; in >> n;

    for(int i = 1; i <= n; i++)
        in >> sor[i];

    for(int i = 1; i <= n; i++)
        in >> t[i];

    for(int i = 1; i <= n; i++)
        graph[sor[i]].push_back({i, t[i]});

    queue <int> Q;
    Q.push(0);

    long long tot = 0;

    while(!Q.empty()) {
        int cur = Q.front();
        int massimo = 0;

        Q.pop();
        for(int i = 0; i < graph[cur].size(); i++) {
            massimo = fmax(massimo, graph[cur][i].second);
            tot += graph[cur][i].second;
            Q.push(graph[cur][i].first);
        }
        tot -= massimo;
    }

    out << tot;
}
