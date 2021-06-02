#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int N = 1e5 + 5;

int n;
int t[2 * N];

void update(int l, int r, int val) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) { t[l] = (t[l] + val) % mod; ++l; }
    if (r & 1) { --r; t[r] = (t[r] + val) % mod; }
  }
}

int query(int p) {
  int ans = 0;
  for (p += n; p > 0; p >>= 1) {
    ans = (ans + t[p]) % mod;
  }

  return ans;
}

int main() {
#ifdef EVAL
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");
#endif

  cin >> n;

  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }

  vector<int> s = v;
  sort(s.begin(), s.end());

  int tr = 0;
  map<int, int> mp;
  mp[s[0]] = tr++;
  for (int i = 1; i < n; i++) {
    if (s[i] != s[i-1]) {
      mp[s[i]] = tr++;
    }
  }

  vector<int> dp(n+1);
  for (int i = n-1; i >= 0; i--) {
    dp[i] = 1 + query(mp[v[i]]);
    update(0, mp[v[i]], dp[i]);
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    // cout << "dp[" << i << "] = " << dp[i] << "\n";
    ans = (ans + dp[i]) % mod;
  }

  cout << ans << "\n";
}