#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

const int N = 5e5 + 5;

int n;
int t[2 * N];

// [l, r)
void add(int l, int r, int val) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) t[l++] += val;
    if (r & 1) t[--r] += val;
  }
}

int query(int p) {
  int res = 0;
  for (p += n; p > 0; p >>= 1) {
    res += t[p];
  }

  return res;
}

int _t = 0;
int in[N];
int out[N];
vector<int> g[N];

void dfs(int v) {
  in[v] = _t++;

  for (int u : g[v])
    dfs(u);

  out[v] = _t;
}

int main() {
#ifdef EVAL
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");
#endif

  int m;
  cin >> n;
  cin >> m;

  vector<int> w(n + 1);
  vector<int> p(n + 1);
  cin >> w[1];
  for (int i = 2; i <= n; i++) {
    cin >> w[i] >> p[i];
    g[p[i]].push_back(i);
  }

  dfs(1);

  for (int i = 1; i <= n; i++) {
    add(in[i], in[i] + 1, w[i]);
  }

  while (m--) {
    int a, b;
    char type;
    cin >> type;

    if (type == 'p') {
      cin >> a >> b;
      add(in[a]+1, out[a], b);
    } else if (type == 'u') {
      cin >> a;
      cout << query(in[a]) << "\n";
    }
  }
}