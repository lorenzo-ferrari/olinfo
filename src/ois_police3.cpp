#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  vector<int> a(n);
  for (int& i : a) cin >> i;
  vector<int> dp1(n+1);
  vector<int> dp2(n+1);
  dp1[0] = a[0];
  dp2[0] = 0;
  for (int i = 1; i < n; ++i) {
    dp1[i] = a[i] + min(dp1[i-1], dp2[i-1]);
    dp2[i] = dp1[i-1];
  }
  cout << min(dp1[n-1], dp2[n-1]) << "\n";
}
