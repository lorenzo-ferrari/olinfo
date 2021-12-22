#include <bits/stdc++.h>
using namespace std;

int main() {
#ifdef EVAL
  ifstream cin("input.txt");
  ofstream cout("output.txt");
#endif

  int t; cin >> t;
  int A; cin >> A;
  int D; cin >> D;

  vector<pair<float, float>> a(A);
  vector<pair<float, float>> d(D);

  for (auto &x : a) {
    cin >> x.first;
    cin >> x.first;
    cin >> x.second;
    cin >> x.second;
  }

  for (auto &x : d) {
    cin >> x.first;
    cin >> x.first;
    cin >> x.second;
    cin >> x.second;
  }

  float ydmin = 1e9;
  float yamin = 1e9;
  for (auto &x : d) ydmin = min(ydmin, x.first + (x.second - x.first) * t / 10);
  for (auto &x : a) yamin = min(yamin, x.first + (x.second - x.first) * t / 10);

  cout << (ydmin <= yamin ? 'R' : 'F') << "\n";
}