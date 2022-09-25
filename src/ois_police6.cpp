#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define all(x) x.begin(), x.end()

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  LL n; cin >> n;
  LL m; cin >> m;
  LL l; cin >> l;
  vector<LL> d(n);
  for (int i = 0; i < n; ++i) {
    cin >> d[i];
  }
  vector<LL> useful;
  for (int i = 0; i < n; ++i) {
    useful.push_back(max(0LL, d[i] - m - 1));
    useful.push_back(min(l  , d[i] + m + 1));
  }
  sort(all(useful));
  useful.resize(unique(all(useful)) - useful.begin());
  int p = useful.size();
  vector<int> prf(p);
  for (int i = 0; i < n; ++i) {
    int ll = lower_bound(all(useful), d[i] - m) - useful.begin();
    int rr = upper_bound(all(useful), d[i] + m) - useful.begin();
    prf[ll] += 1;
    if (rr != p) prf[rr] -= 1;
  }
  for (int i = 1; i < p; ++i) {
    prf[i] += prf[i - 1];
  }
  cout << *min_element(all(prf)) << "\n";
}
