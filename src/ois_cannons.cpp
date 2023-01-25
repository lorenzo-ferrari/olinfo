#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    vector<int> d(n, 1e9);
    priority_queue<array<int, 2>> Q;
    d[0] = 0;
    Q.push({0, 0});
    while (!Q.empty()) {
        int v = Q.top()[1];
        Q.pop();
        if (d[t[v]] > d[v]) {
            d[t[v]] = d[v];
            Q.push({-d[v], t[v]});
        }
        for (int dx = -1; dx <= 1; dx += 2) {
            int u = v + dx;
            if (0 <= u && u < n && d[u] > d[v] + 1) {
                d[u] = d[v] + 1;
                Q.push({-d[u], u});
            }
        }
    }
    cout << d[n-1] << "\n";
}
