#include <bits/stdc++.h>
using namespace std;

int main()
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  cin >> n;

  int mx = INT_MIN; //-inf idealmente
  for (int i = 0, v; i < n; ++i)
  {
    cin >> v;
    mx = max(v, mx);
  }

  cout << mx << endl;
}
