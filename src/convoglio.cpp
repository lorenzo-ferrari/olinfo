#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

const int N = 1e5 + 5;
const int INF = 1e9;

int _p[2*N];

void make_set(int v) { _p[v] = v; }
int find_set(int v) { return _p[v] == v ? v : _p[v] = find_set(_p[v]); }
bool union_set(int a, int b) {
  a = find_set(a);
  b = find_set(b);
  if (a == b)
    return false;
  _p[b] = a;
  return true;
}

int par[2*N];
vector<int> g[2*N];
void dfs(int v, int parent) {
  par[v] = parent;
  for (int u : g[v])
  	if (u != par[v] && par[u] == -1)
  	  dfs(u, v);
}

int main() {
#ifdef EVAL
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");
#endif

  int n, m;
  cin >> n >> m;
  vector<int> p(2*n);
  for (int i = 0; i < 2*n; i++)
    make_set(i);
  for (int i = 0, a, b; i < m; i++) {
    cin >> a >> b;
    b += n;
    if (i < n) {
      p[a] = b;
      p[b] = a;
    }
    g[a].push_back(b);
    g[b].push_back(a);
    if (!union_set(a, b)) {
      fill(par, par+2*n, -1);
      dfs(a, -1);
      int cur = a;
      while (par[cur] != a) {
        int prv = par[cur];
        if (cur < n) {
          p[cur] = prv;
          p[prv] = cur;
        }
        cur = prv;
      }
      
// schifo, ma prende ac
        vector<bool> seen(n);
        for (int i = 0; i < n; i++) {
          if (seen[p[i]-n]) {
            cout << -1 << "\n";
            return 0;
          }
          seen[p[i]-n] = true;
        }
//
      for (int i = 0; i < n; i++) {
      	cout << i << " " << p[i]-n << "\n";
      }
      return 0;
    }
  }

  cout << -1 << "\n";
}