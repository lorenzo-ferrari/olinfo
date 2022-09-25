#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int N = 1e5;

int m[N + 1];
int sum[N + 1];
vector<int> g[N + 1];

int dfs(int v) {
  int ans = 0;
  for (int u : g[v])
    ans += dfs(u);
  return sum[v] = ans + m[v];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

#ifdef EVAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> m[i];
		m[i]--;
	}
  for (int i = 2, p; i <= n; i++) {
    cin >> p;
    g[p].push_back(i);
  }

  long long ans = abs(dfs(1));
  for (int i = 2; i <= n; i++)
    ans += abs(sum[i]);

  cout << ans << "\n";
}
