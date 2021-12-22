#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int d;
  cin >> d;

  int ans = 0;
  for (int i = 0; i <= 30; i++)
    if (d & (1 << i))
      ans++;

  cout << ans << endl;
}