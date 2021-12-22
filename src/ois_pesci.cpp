#include <bits/stdc++.h>
using namespace std;

int main() {

#ifdef EVAL
  ifstream cin("input.txt");
  ofstream cout("output.txt");
#endif

  int n;
  cin >> n;

  vector<int> v(n);
  vector<int> d(n);

  for (int i = 0; i < n; i++)
    cin >> d[i] >> v[i];

  // scorri l->r e vedi quali (< < < <) passano
  // scorri r->l e vedi quali (> > > >) passano

  int ans = 0;
  int bro = 0;
  int enemy = 0;
  for (int i = 0; i < n; i++) {
    if (d[i] == 1 && enemy < v[i]) { // <
      ans++;
      enemy = 0;
    } else { // >
      enemy = max(enemy, v[i]);
    }
  }

  bro = 0;
  enemy = 0;
  for (int i = n-1; i >= 0; i--) {
    if (d[i] == 0 && enemy < v[i]) { // >
      ans++;
      enemy = 0;
    } else {
      enemy = max(enemy, v[i]);
    }
  }

  cout << ans << endl;
}