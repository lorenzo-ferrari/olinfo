#include <bits/stdc++.h>
using namespace std;

int main() {
#ifdef EVAl
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");
#endif

  int n, e;
  cin >> n >> e;

  vector<int> p(n);
  vector<int> who(n);
  iota(who.begin(), who.end(), 0);

  for (int i = 0, x, y; i < e; i++) {
    cin >> x >> y;
    if (x ^ y) {
      p[x]++;
      who[y] = x;
    } else {
      p[who[x]]--;
      who[x] = x;
    }
  }

  for (int i : p)
    cout << i << " ";
  cout << endl;
}