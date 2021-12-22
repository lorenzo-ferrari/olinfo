#include <bits/stdc++.h>
#define MAXN 1000000
using namespace std;

typedef pair <int, int> pii;

ifstream in ("input.txt");
ofstream out ("output.txt");

int N, parent;
int arrogance[MAXN];
vector <int> tree[MAXN];

int main()
{
    in >> N;

    in >> parent;

    for(int i = 1; i < N; i++)
    {
        in >> parent;
        tree[parent].push_back(i);
    }

    for(int i = 0; i < N; i++)
        in >> arrogance[i];

    priority_queue <pii> Q;
    Q.push({arrogance[0], 0});

    while(!Q.empty())
    {
        int cur = Q.top().second;

        Q.pop();

        out << cur << " ";

        for(int i = 0; i < tree[cur].size(); i++)
            Q.push({arrogance[tree[cur][i]], tree[cur][i]});
    }

    in.close();
    out.close();

    return 0;
}