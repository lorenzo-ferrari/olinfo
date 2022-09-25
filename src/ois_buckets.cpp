#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n; cin >> n;
  vector<int> v(n);
  for (int& i : v)
    cin >> i;
  sort(v.begin(), v.end());
  bool noice = 1;
  for (int i = 0; i < n - 1; ++i)
    if (v[i] == v[i + 1])
      noice = 0;
  cout << (noice ? "Ok" : "Impossible") << "\n";
}
