#include <bits/stdc++.h>

#define MAXN 10000
#define MAXM 1000000

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

typedef pair<int, int> pii;
typedef long long ll;

int N, M, counter, v1, v2;
ll w, peso;
int parent[MAXN + 1];
pair<ll, pii> edges[MAXM];
vector <pii> output;

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

    if(a != b)
        parent[b] = a;
}

int main() {
    in >> N >> M;

    for(int i = 0; i < M; i++) {
        in >> v1 >> v2 >> w;
        if(v1 > v2)
            swap(v1, v2);
        edges[i] = {w, {v1, v2}};
    }

    for(int i = 1; i <= N; i++) make_set(i);

    sort(edges, edges + M);

    for(int i = 0; counter < N-1; i++) {
        v1 = edges[i].second.first;
        v2 = edges[i].second.second;

        if(find_set(v1) != find_set(v2)) {
            peso += edges[i].first;
            counter++;
            union_set(v1, v2);
            output.push_back({v1, v2});
        }
    }
    sort(output.begin(), output.end());

    out << peso << "\n";

    for(int i = 0; i < N-1; i++)
        out << output[i].first << " " << output[i].second << "\n";

    in.close();
    out.close();
}
