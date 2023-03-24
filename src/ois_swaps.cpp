#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define all(x) begin(x),end(x)

int flag[10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> p(n+1);
    vector<set<int>> s;
    vector<bool> vis(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        int x = i;
        set<int> t;
        while (!vis[x]) {
            t.insert(x);
            vis[x] = true;
            x = p[x];
        }
        s.push_back(t);
    }
    int g = 0;
    for (auto& t : s) {
        for (int i : t) {
            g = __gcd(g, i - *begin(t));
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (g % i == 0) {
            cout << n - s.size() << " ";
        } else {
            cout << -1 << " ";
        }
    }
    cout << "\n";
}

