#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i] >> b[i];
    if (i && max(a[i], a[i-1]) > min(b[i], b[i-1])) {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";
}
