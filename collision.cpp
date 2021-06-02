#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

int64_t submask(int64_t k) {
  int cnt = __builtin_popcount(k);

  int64_t ans = 0;
  for (int64_t i = 0, j = 0; i < 31 && j < (cnt / 2); i++) {
    if (k & (1LL << i)) {
      ans += (1LL << i);
      j++;
    }
  }


  return ans;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int64_t n, k;
  cin >> n >> k;

  vector<int64_t> s1(n);
  vector<int64_t> s2(n);

  s1[0] = k;
  s2[0] = submask(k);
  s2[1] = k^submask(k);

  if (n == 3) {
    int64_t f1 = -1, f2 = -1;
    for (int64_t i = 0; i < 31 && f2 == -1; i++) {
      if (!(k & (1LL << i))) {
        f2 = f1;
        f1 = i;
      }
    }

    s1[0] ^= (1LL << f1);
    s1[1] ^= (1LL << f2);
    s1[2] ^= (1LL << f1) + (1LL << f2);
    swap(f1, f2);
    s2[0] ^= (1LL << f1) + (1 << f2);
    s2[1] ^= (1LL << f1);
    s2[2] ^= (1LL << f2);
  } else {
    mt19937 generator;
    int64_t ones = (n - 1) / 2;
    ones -= (ones & 1);

    vector<int64_t> v(n-1);
    fill(v.begin(), v.begin() + ones, 1);
    for (int64_t i = 0; i < 31; i++) {
      shuffle(v.begin(), v.end(), generator);
      for (int64_t j = 1; j < n; j++)
        s1[j] += v[j-1] * (1LL << i);
    }

    sort(v.begin(), v.end(), greater<int>());
    v.pop_back();

    for (int64_t i = 0; i < 31; i++) {
      shuffle(v.begin(), v.end(), generator);
      for (int64_t j = 2; j < n; j++)
        s2[j] += v[j-2] * (1LL << i);
    }
  }

    for (int i : s1)
      cout << i << " ";
    cout << "\n";
    for (int i : s2)
      cout << i << " ";
    cout << "\n";
}