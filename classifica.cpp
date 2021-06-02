#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
  if (a.first > b.first) return true;
  if (a.first < b.first) return false;
  return a.second < b.second;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  int n;
  cin >> n;
  vector <pair<int, int>> a(n);
  for (int i = 0; i < n; i++)
    a[i].second = i;
  for (int i = 0, s1, s2, g1, g2; i < n*(n-1)/2; i++) {
    cin >> s1 >> s2 >> g1 >> g2;
    if (g1 < g2) {
      a[s2-1].first += 3;
    } else if (g2 < g1) {
      a[s1-1].first += 3;
    } else {
      a[s1-1].first++;
      a[s2-1].first++;
    }
  }
  sort(a.begin(), a.end(), cmp);
  cout << a[0].second+1 << " " << a[0].first << "\n";
}
