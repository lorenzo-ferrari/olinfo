/*

let each oriented edge (a,b) represent is part of a region (left to (a,b))

* DSU to join the edges in the same area
* BFS, after how many seconds is the area flooded?
  -> understand who touches the ocean
  -> DSU on the graph
  -> \forall component, outermost edge(s) touches the ocean (*)
* an edge exists iff face(a,b) and face(b,a) are flodded at the same time

(*): not necessarily: components can be matched without touching. However it
     does not affect the answer
*/


#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

constexpr int8_t ord[4][4] {
  {LEFT, UP, RIGHT, DOWN},
  {UP, RIGHT, DOWN, LEFT},
  {RIGHT, DOWN, LEFT, UP},
  {DOWN, LEFT, UP, RIGHT}
};

#define watch(x) cerr << (#x) << " is " << x << endl

class Dsu {
	std::vector<int> p;
public:
	Dsu(int n) {
		p.assign(n, 0);
		while (n--)
			p[n] = n;
	}
	int find(int v) {
		return p[v] == v ? v : p[v] = find(p[v]);
	}
	void onion(int a, int b) {
		a = find(a);
		b = find(b);
		p[b] = a;
	}
  vector<vector<int>> components() {
    vector<vector<int>> cc(p.size());
    for (int i = 0; i < int(p.size()); ++i) {
      cc[find(i)].push_back(i);
    }
    vector<vector<int>> ans;
    for (auto& x : cc) if (x.size()) ans.push_back(x);
    return ans;
  }
};

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  vector<array<int, 2>> v(n);
  for (auto& [a, b] : v) {
    cin >> a >> b;
  }
  auto dir = [&](int a, int b) -> int {
    if (v[a][0] < v[b][0]) return RIGHT;
    if (v[a][0] > v[b][0]) return LEFT;
    if (v[a][1] < v[b][1]) return UP;
    if (v[a][1] > v[b][1]) return DOWN;
    return 42;
  };
  int w; cin >> w;
  vector<array<int, 2>> ws(w);
  vector<array<int, 4>> nb(n, {-1,-1,-1,-1});
  for (auto& [a, b] : ws) {
    cin >> a >> b; --a; --b;
    if (v[a] > v[b]) swap(a, b);
    nb[a][dir(a,b)] = b;
    nb[b][dir(b,a)] = a;
  }
  vector<int> wid(2*w);
  iota(wid.begin(), wid.end(), 0);
  sort(wid.begin(), wid.end(), [&](int i, int j){
    return ((i&1) ? array<int,2>{ws[i/2][1], ws[i/2][0]} : ws[i/2]) < ((j&1) ? array<int,2>{ws[j/2][1], ws[j/2][0]} : ws[j/2]);
  });
  auto w2id = [&](int a, int b) -> int {
    int l = 0, r = 2*w;
    while (r - l > 1) {
      int m = (l + r) / 2;
      int i = wid[m];
      if (((i&1) ? array<int,2>{ws[i/2][1], ws[i/2][0]} : ws[i/2]) <= array<int, 2>{a,b}) {
        l = m;
      } else {
        r = m;
      }
    }
    return wid[l];
  };
  Dsu f(2 * w);
  for (auto [a, b] : ws) {
    int dd = dir(a, b); int i = 0;
    while (nb[b][ord[dd][i]] == -1) ++i;
    f.onion(w2id(a,b), w2id(b,nb[b][ord[dd][i]]));

    dd = dir(b, a); i = 0;
    while (nb[a][ord[dd][i]] == -1) ++i;
    f.onion(w2id(b,a), w2id(a,nb[a][ord[dd][i]]));
  }

  vector<vector<int>> adj(2 * w);
  for (auto [a, b] : ws) {
    adj[f.find(w2id(a,b))].push_back(f.find(w2id(b,a)));
    adj[f.find(w2id(b,a))].push_back(f.find(w2id(a,b)));
  }
  vector<int> d(2 * w, 1e9);
{
  Dsu dsu(n);
  for (auto [a, b] : ws) {
    dsu.onion(a, b);
  }
  auto cc = dsu.components();
  for (auto& c : cc) {
    int mn = *min_element(c.begin(), c.end(), [&](int i, int j){return v[i]<v[j];});
    if (nb[mn][UP] != -1) d[f.find(w2id(mn,nb[mn][UP]))] = 0;
    if (nb[mn][RIGHT] != -1) d[f.find(w2id(nb[mn][RIGHT],mn))] = 0;
  }
}
  queue<int> Q;
  for (int i = 0; i < 2*w; ++i) if (d[i] == 0) Q.push(i);
  while (!Q.empty()) {
    int v = Q.front(); Q.pop();
    for (int u : adj[v]) {
      if (d[u] > d[v] + 1) {
        d[u] = d[v] + 1;
        Q.push(u);
      }
    }
  }
  vector<int> ans;
  for (int i = 0; i < w; ++i) {
    auto [a, b] = ws[i];
    if (d[f.find(w2id(a,b))] == d[f.find(w2id(b,a))]) {
      ans.push_back(i+1);
    }
  }
  cout << ans.size() << "\n";
  for (int i : ans) {
    cout << i << "\n";
  }
}
