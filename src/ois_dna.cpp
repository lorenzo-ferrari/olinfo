#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

int n, m;
vector<bitset<105>> s;

inline int16_t d(int16_t a, int16_t b) {
  if (a == 0 || b == 0)
    return m;

  return (s[a] ^ s[b]).count();
}

inline int mst() {
  int ans = 0;

  vector<bool> vis(n + 1);
  vector<int16_t> mn(n + 1, m);

  int v = 0;
  vis[0] = true;
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= n; j++) {
      if (!vis[j]) {
        mn[j] = min(mn[j], d(j, v));
      }
    }

    int w = m + 1;
    for (int j = 1; j <= n; j++) {
      if (!vis[j] && mn[j] < w) {
        v = j;
        w = mn[j];
      }
    }

    vis[v] = true;
    ans += w;

    cerr << v << " " << w << "\n";
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> m;

  s.resize(n + 1);

  char c;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> c;
      while (c != '0' && c != '1')
        cin >> c;
      s[i][j] = (c == '1');
    }
  }

  cout << mst() << "\n";
}
