#include <bits/stdc++.h>
#define MAXN 50000
using namespace std;

typedef long long ll;

ifstream in ("input.txt");
ofstream out ("output.txt");

int N, parent;
ll tot;
int F[MAXN];
vector <int> tree[MAXN];

ll weight_balanced(int v)
{
    ll massimo = 0;
    ll temp_weight;

    for(int i = 0; i < tree[v].size(); i++)
    {
        temp_weight = weight_balanced(tree[v][i]);
        massimo = max(massimo, temp_weight);
        tot -= temp_weight;
    }
    tot += tree[v].size()*massimo;

    return massimo*tree[v].size() + F[v];
}

int main()
{
    in >> N;

    for(int i = 1; i < N; i++)
    {
        in >> parent >> F[i];
        tree[parent].push_back(i);
    }
    
    ll avvio = weight_balanced(0);

    out << tot;
}
