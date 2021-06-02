#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  cin >> n;

  int l = 1;
  while (n != 1) {
    l++; // l = l + 1
    if (n % 2 == 0)
      n = n / 2;
    else
      n = 3 * n + 1;
  }

  cout << l << endl;
}