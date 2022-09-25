#include <bits/stdc++.h>
using namespace std;

int main() {

#ifdef EVAL
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");
#endif

  int n;
  double e;
  cin >> n >> e;

  double btc = 1;
  double euro;
  for (int i = 0; i < n; i++) {
    double d;
    cin >> d;

    // sell btc -> d ->  buy btc
    if (d < 0) {
      euro = btc * e;
      e += d;
      btc = euro / e;
    } else { // do nothing
      e += d;
    }
  }

  cout << fixed << setprecision(8) << btc * e << endl;
}