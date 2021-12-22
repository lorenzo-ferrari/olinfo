#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  cin >> n;

  int a, b;
  int mx = -1; // somma pari massima
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    if ((a + b) % 2 == 0)
      mx = max(mx, a + b);
  }

  cout << mx << endl;
}