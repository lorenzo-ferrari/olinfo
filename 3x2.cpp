#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  int ans = 0;
  vector<int> p(n);
  for (int &i : p) {
    cin >> i;
    ans += i;
  }

  sort(p.begin(), p.end());

  for (int i = n-3; i >= 0; i -= 3)
    ans -= p[i];

  cout << ans << "\n";
}
