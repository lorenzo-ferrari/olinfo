#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    int m; cin >> m;
    vector<int> r(n), w(m);
    for (int& i : r) cin >> i;
    for (int& i : w) cin >> i;
    vector<int> p(m, -1);
    priority_queue<int, vector<int>, greater<int>> Q;
    for (int i = 0; i < n; ++i) {
        Q.push(i);
    }
    queue<int> q;
    for (int i = 0; i < 2*m; ++i) {
        int c; cin >> c;;
        if (c > 0) {
            if (Q.empty()) {
                q.push(c-1);
            } else {
                p[c-1] = Q.top();
                Q.pop();
            }
        } else {
            Q.push(p[-c-1]);
            if (!q.empty()) {
                p[q.front()] = Q.top();
                Q.pop();
                q.pop();
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        ans += r[p[i]] * w[i];
    }
    cout << ans << "\n";
}
