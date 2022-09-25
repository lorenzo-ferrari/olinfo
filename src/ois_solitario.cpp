#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int n, m, cnt, ans;
bool g[10][10];

bool tris(int x) {
  int i = x/m;
  int j = x%m;
  if (i >= 2 && g[i][j] && g[i-1][j] && g[i-2][j]) return true;
  if (j >= 2 && g[i][j] && g[i][j-1] && g[i][j-2]) return true;
  if (i >= 2 && j >= 2 && g[i][j] && g[i-1][j-1] && g[i-2][j-2]) return true;
  if (i >= 2 && j+2 < m && g[i][j] && g[i-1][j+1] && g[i-2][j+2]) return true;
  return false;
}

void solve(int i) {
  if ((i && tris(i-1)) || cnt + n*m - i <= ans) return;
  if (i == n*m) {
    ans = max(ans, cnt);
  } else {
    g[i/m][i%m] = 1;
    ++cnt;
    solve(i+1);
    g[i/m][i%m] = 0;
    --cnt;
    solve(i+1);
  }
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  cin >> n >> m;
  solve(0);
  cout << ans << "\n";
}
