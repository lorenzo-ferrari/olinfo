#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  int s = 0;
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    s += a;
  }
  cout << s << " " << 1.0*s/n << "\n";
}
