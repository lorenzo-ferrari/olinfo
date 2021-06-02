#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int n, m, a, b;
vector <int> ans;
vector <multiset<int>> g;
void find_eulerian_cycle(int v) {
    while (g[v].size()) {
        int u = *g[v].begin();
        // assert(g[v].find(u) != g[v].end());
        // assert(g[u].find(v) != g[u].end());
        g[v].erase(g[v].find(u));
        g[u].erase(g[u].find(v));

        find_eulerian_cycle(u);
    }
    ans.push_back(v);
}

int main() {
  #ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  #endif

    scanf("%d %d %d %d", &n, &m, &a, &b);
    g.resize(n + 1);
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d %d", &u, &v);
        g[v].insert(u);
        g[u].insert(v);
    }

    g[a].insert(b);
    g[b].insert(a);

    find_eulerian_cycle(a);

    // reverse(ans.begin(), ans.end());
    // for (int i : ans) cout << i << " "; cout << "\n";

    assert(ans[0] == ans.back());
    assert(1);
    ans.pop_back();

    int z = ans.size();

    if (ans[0] == a && ans.back() == b) {
      for (int i = 0; i < z-1; i++)
        printf("%d %d\n", ans[i], ans[i + 1]);
      return 0;
    }

    for (int i = 0; i < z; i++) {
        if (ans[i] == b && ans[(i+1)%z] == a) {
            i++;
            for (int j = 0; j < z-1; j++)
                printf("%d %d\n", ans[(i+j)%z], ans[(i+j+1)%z]);
            return 0;
        }
        if (ans[i] == b && ans[(i-1+n)%z] == a) {
            i--;
            for (int j = 0; j < z-1; j++)
                printf("%d %d\n", ans[(i-j+z)%z], ans[(i-j-1+z)%z]);
            return 0;
        }
    }

    ans.push_back(a);
    reverse(ans.begin(), ans.end());
    ans.pop_back();

    if (ans[0] == a && ans.back() == b) {
      for (int i = 0; i < z-1; i++)
        printf("%d %d\n", ans[i], ans[i + 1]);
      return 0;
    }

    for (int i = 0; i < z; i++) {
        if (ans[i] == b && ans[(i+1)%z] == a) {
            i++;
            for (int j = 0; j < z-1; j++)
                printf("%d %d\n", ans[(i+j)%z], ans[(i+j+1)%z]);
            return 0;
        }
        if (ans[i] == b && ans[(i-1+n)%z] == a) {
            i--;
            for (int j = 0; j < z-1; j++)
                printf("%d %d\n", ans[(i-j+z)%z], ans[(i-j-1+z)%z]);
            return 0;
        }
    }
}
