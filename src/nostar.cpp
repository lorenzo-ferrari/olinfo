#include <bits/stdc++.h>
using namespace std;
using LL = long long;

vector<set<int>> adj;

void find_tour(int v) {
    while (!adj[v].empty()) {
        int u = *adj[v].begin();
        cout << v << " " << u << "\n";
        adj[v].erase(u);
        adj[u].erase(v);
        find_tour(u);
    }
}

int main() {
    int n; cin >> n;
    int m; cin >> m;
    adj.resize(n);
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    find_tour(0);
}
