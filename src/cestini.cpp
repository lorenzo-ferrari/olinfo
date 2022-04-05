#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr int M = 100000;

vector<int> c[M];

void inizia(int n, int m) {
  c[0].resize(n);
  for (int i = 0; i < n; ++i) {
    c[0][i] = i;
  }
}

void sposta(int a, int b) {
  c[b].push_back(c[a].back());
  c[a].pop_back();
}

int controlla(int a, int i) {
  return int(c[a].size()) <= i ? -1 : c[a][i];
}
