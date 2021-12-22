#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

int main() {
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");

  int n;
  cin >> n;

  vector<pair<int, int>> v(n);
  for (auto &[a, b] : v)
    cin >> a >> b;

  vector<int> dp(370);

  for (auto &[a, b] : v)
    for (; b >= a; --b)
      dp[b] = max(dp[b], dp[b-a] + 1);

  cout << *max_element(dp.begin(), dp.end()) << endl;
}