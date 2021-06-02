#include <bits/stdc++.h>
using namespace std;

const int N = 2e5;

int n;
int mx[2 * N];
int mn[2 * N];

void build() {
  for (int i = n-1; i > 0; i--) {
    mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
    mn[i] = min(mn[i << 1], mn[i << 1 | 1]);
  }
}

int maxquery(int l, int r) {
  int ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = max(ans, mx[l++]);
    if (r & 1) ans = max(ans, mx[--r]);
  }

  return ans;
}

int minquery(int l, int r) {
  int ans = 1e9;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = min(ans, mn[l++]);
    if (r & 1) ans = min(ans, mn[--r]);
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int ln;
  cin >> ln;

  n = 2 * ln;
  vector<int> v(n);
  for (int &i : v)
    cin >> i;

  for (int i = 0; i < n; i++)
    v.push_back(v[i]);

  n = 2 * n;
  for (int i = 0; i < n; i++) {
    mx[i + n] = v[i];
    mn[i + n] = v[i];
  }

  build();

  int q;
  cin >> q;
  for (int i = 0, shift = 0, w; i < q; i++) {
    cin >> w;
    shift = (shift - w + n) % (2 * ln);

    cout << minquery(shift, shift + ln) << " " << maxquery(shift + ln, shift + 2 * ln) << "\n";
  }
}