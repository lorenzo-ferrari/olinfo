#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n; cin >> n;
  vector<char> st;
  bool good = true;
  for (int i = 0; i < n; ++i) {
    char c; cin >> c;
    if (c == '<' || c == '(' || c == '[' || c == '{') st.push_back(c);
    else {
      if (st.empty()) good = false;
      else if (st.back() != '<' && '>' == c) good = false;
      else if (st.back() != '(' && ')' == c) good = false;
      else if (st.back() != '[' && ']' == c) good = false;
      else if (st.back() != '{' && '}' == c) good = false;
      else st.pop_back();
    }
  }
  cout << (good && st.empty() ? "corretta" : "malformata") << "\n";
}
