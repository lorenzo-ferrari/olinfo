#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n; cin >> n;
  string s; cin >> s;
  string ans;
  for (char c : s) {
    ans.push_back(c);
    if (ans.size() >= 3 && ans.substr(ans.size()-3) == "PaH") {
      for (int _ = 0; _ < 3; ++_) ans.pop_back();
      if (!ans.empty() && ans.back() != ' ') ans.push_back(' ');
    }
    else if (ans.size() >= 4 && ans.substr(ans.size()-4) == "TuNZ") {
      for (int _ = 0; _ < 4; ++_) ans.pop_back();
      if (!ans.empty() && ans.back() != ' ') ans.push_back(' ');
    }
  }
  cout << ans << "\n";
}
