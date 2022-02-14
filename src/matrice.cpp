#include <bits/stdc++.h>
using namespace std;
using LL = long long;

vector<int> primes;

void sieve(int til) {
  vector<int> d(til + 1, 1);
  for (int i = 2; i <= til; ++i) {
    if (d[i] == 1) {
      primes.push_back(i);
      for (int j = i; j <= til; j += i) {
        if (d[j] == 1) {
          d[j] = i;
        }
      }
    }
  }
}

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  sieve(120000);
  int n; cin >> n;
  int m; cin >> m;
  vector<int> rows(n);
  vector<int> cols(m);
  for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
    int a; cin >> a;
    a = *lower_bound(primes.begin(), primes.end(), a) - a;
    rows[i] += a;
    cols[j] += a;
  }
  int minrow = *min_element(rows.begin(), rows.end());
  int mincol = *min_element(cols.begin(), cols.end());
  cout << min(minrow, mincol) << "\n";
}
