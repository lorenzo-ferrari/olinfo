#include <bits/stdc++.h>
using namespace std;

int main() {
#ifdef EVAL
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");
#endif

  int n;
  cin >> n;

  vector<int> v(n);
  vector<bool> vis(n);
  for (int &i : v)
    cin >> i;

  int p = 1;
  int ans = n;
  while (!vis[p-1]) {
    --ans;
    vis[p-1] = true;
    p = (p + v[p-1]) % n + 1;
  }

  cout << ans << "\n";
  for (int i = 0; i < n; ++i)
    if (!vis[i])
      cout << i+1 << " ";
  // cout << "\n";
}