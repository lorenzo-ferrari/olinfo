#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

inline int match(string &a, string &b) {
  int ans = 0;
  while (ans < a.size() && ans < b.size() && a[ans] == b[ans])
    ans++;

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int n;
  cin >> n;

  string mx;
  vector<string> v(n);
  for (string &s : v) {
    cin >> s;
    if (s.size() > mx.size())
      mx = s;
  }

  sort(v.begin(), v.end());

  vector<string> m[21];
  for (string &s : v)
    m[match(mx, s)].push_back(s);

  string buffer;
  vector<char> ans;
  for (int i = 0; i <= 20; i++) {
    for (string &s : m[i]) {
      int mt = match(buffer, s);
      for (int i = buffer.size(); i > mt; i--)
        ans.push_back('-');
      for (int i = mt; i < s.size(); i++)
        ans.push_back(s[i]);

      ans.push_back('P');
      buffer = s;
    }
  }

  cout << ans.size() << "\n";
  for (char &c : ans)
    cout << c << "\n";
}
