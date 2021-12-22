#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");
  int n;
  cin >> n;
  int sum = 0;
  vector<int> v(n);
  for (int &i : v) {
    cin >> i;
    sum += i;
  }
  sort(v.begin(), v.end());
  int ans = 0;
  while (sum <= 0)
    sum -= 2*v[ans++];
  cout << ans << endl;
}