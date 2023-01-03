#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr int T = 1e6;
static constexpr int N = 2000;

static int a[N], b[N], c[N];

static LL eval(int i, LL t) {
  return a[i]*t*t + b[i]*t + c[i];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n; cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i] >> b[i] >> c[i];
  }
  int q; cin >> q;
  vector<array<LL, 2>> vals(n);
  for (int j = 0; j < q; ++j) {
    int pp; cin >> pp;
    int tt; cin >> tt;
    for (LL i = 0; i < n; ++i) {
      vals[i] = {-eval(i, tt), i+1};
    }
    nth_element(begin(vals), begin(vals)+pp-1, end(vals));
    cout << vals[pp-1][1] << "\n";
  }
}
