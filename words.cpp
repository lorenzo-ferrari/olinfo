#include <bits/stdc++.h>
using namespace std;

const int L = 1e4 + 1;
const int K = 17576;

string s[K];
vector<int> c[K];
long long n, l, k;
static long long dp[L][K];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> l >> k;
  for (int i = 0; i < k; i++)
    cin >> s[i];
  sort(s, s + k);
  for (int i = 0; i < k; i++) {
    string tmp = s[i].substr(1,2);
    for (char x = 'a'; x <= 'z'; x++) {
      tmp.push_back(x);
      int it = lower_bound(s, s + k, tmp) - s;
      if (it != k && s[it] == tmp)
        c[i].push_back(it);
      tmp.pop_back();
    }
  }
  for (int i = 0; i < k; i++)
    dp[3][i] = 1;
  for (int i = 3; i <= l; i++) {
    for (int j = 0; j < k; j++) {
      for (int nxt : c[j]) {
        if (dp[i][j] >= n)
          break;
        dp[i][j] += dp[i-1][nxt];
      }
    }
  }

  int prv;
  string ans;
  for (int i = 0; i < k; i++) {
    if (dp[l][i] >= n) {
      prv = i;
      ans = s[i];
      break;
    } else {
      n -= dp[l][i];
    }
  }
  for (int i = l-1; i >= 0; i--) {
    for (int j : c[prv]) {
      if (dp[i][j] >= n) {
        prv = j;
        ans.push_back(s[j][2]);
        break;
      } else {
        n -= dp[i][j];
      }
    }
  }

  cout << ans << "\n";
}
