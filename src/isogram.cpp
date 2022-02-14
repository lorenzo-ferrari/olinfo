#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  int cnt = 0;
  string s; getline(cin, s);
  for (int i = 0; i < n; ++i) {
    getline(cin, s);
    map<char, int> frq;
    for (char c : s) {
      if (c == ' ') continue;
      if ('A' <= c && c <= 'Z') ++frq[c-'A'+'a'];
      if ('a' <= c && c <= 'z') ++frq[c];
    }
    bool good = true;
    for (auto [c, f] : frq) {
      if (f > 2) {
        good = false;
        break;
      }
    }
    cnt += good;
  }
  cout << cnt << "\n";
}
