#include <iostream>
#pragma GCC optimize ("O3")
using namespace std;

int main() {
ios_base::sync_with_stdio(false);
cin.tie(NULL);
  int n; cin >> n;
  int s = 0;
  for (int i = 0; i < n; ++i) {
    int a; cin >> a;
    s += a;
  }
  cout << s << " " << static_cast<double>(s)/n << "\n";
}
