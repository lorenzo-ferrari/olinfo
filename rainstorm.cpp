#include <bits/stdc++.h>

#define MAXN 100000
#define MAXM 100000

using namespace std;

typedef pair <int, int> pii;

ifstream in ("input.txt");
ofstream out ("output.txt");

int N, M, counter, v1, v2, w, i;

pair <int, pii> edges[MAXM];
int parent[MAXN], rankk[MAXN];

void make_set(int v) {
    parent[v] = v;
}

int find_set(int v) {
    if(v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_set(int a, int b) {
    a = find_set(a);
    b = find_set(b);

    if(a != b) {
        if(rankk[a] < rankk[b])
            swap(a, b);
        parent[b] = a;
        if(rankk[a] == rankk[b])
            rankk[a]++;
    }

}

int main()
{
    in >> N >> M;

    for(i = 0; i < M; i++) {
        in >> v1 >> v2 >> w;
        edges[i] = {-w, {v1, v2}};
    }

    for(i = 0; i < N; i++) make_set(i);

    sort(edges, edges + M);
    
    for(i = 0; counter < N-1 && i < M; i++) {
        v1 = edges[i].second.first;
        v2 = edges[i].second.second;
        
        if(find_set(v1) != find_set(v2)) {
            union_set(v1, v2);
            counter++;
        }
    }

    out << -edges[i-1].first;
}
