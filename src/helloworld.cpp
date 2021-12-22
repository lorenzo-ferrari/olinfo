#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s;
  cin >> s;

  if (s.size() < 10) {
    cout << 0 << endl;
    return 0;
  }

  vector<int> v;
  for (int i = 0; i < s.size()-4; i++) {
    if (s.substr(i, 5) == "hello")
      v.push_back(1);
    else if (s.substr(i, 5) == "world")
      v.push_back(0);
  }

  vector<int> p = v;
  for (int i = 1; i < p.size(); i++)
    p[i] += p[i - 1];

  long long ans = 0;
  for (int i = 0; i < v.size(); i++)
    if (v[i] == 0)
      ans += p[i];

  cout << ans << endl;
}