#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

const int N = 1000;

int nxt[N][N];

int solve(int n, bool v[N][N], bool team) {
  for (int i = 0; i < n; i++) {
    nxt[i][n-1] = (v[i][n-1] != team) ? n-1 : n;
  }
  for (int i = 0; i < n; i++) {
    for (int j = n-2; j >= 0; j--) {
      nxt[i][j] = (v[i][j] != team) ? j : nxt[i][j+1];
    }
  }

  int ans = 0;
  vector <int> id(n);
  iota(id.begin(), id.end(), 0);
  for (int i = 0; i < n; i++) {
    auto cmp = [i](int a, int b) { return nxt[a][i] > nxt[b][i]; };
    sort(id.begin(), id.end(), cmp);

    for (int j = 0; j < n; j++) {
      ans = max(ans, (j + 1) * (nxt[id[j]][i] - i));
    }
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  bool v[N][N];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      char c;
      cin >> c;
      v[i][j] = (c == 'R');
    }
  }

  int r = solve(n, v, 1);
  int b = solve(n, v, 0);

  if (r > b) {
    cout << 1 << " " << r << "\n";
  } else if (r < b) {
    cout << 2 << " " << b << "\n";
  } else {
    cout << 0 << " " << r << "\n";
  }
}
