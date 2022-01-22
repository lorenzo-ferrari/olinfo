#include <bits/stdc++.h>
using namespace std;

constexpr size_t N = 256;
constexpr double TL = 0.59;

bitset<N> cov[N];
bitset<N> isgood;

struct bb {
  clock_t until;
  bitset<N> missing;
  vector<bitset<N>> st;

  size_t ans;

  void rec(vector<int>& goods) {
    if (clock() > until) return;
    if ((st.back() | ~missing).count() == N) ans = min(ans, st.size() - 1);
    if (goods.empty() || st.size() - 1 >= ans) return;
    int nxt = goods[0];
    for (int j : goods) {
      if ((st.back() | cov[j]).count() > (st.back() | cov[nxt]).count()) {
        nxt = j;
      }
    }
    vector<int> nxtGoods;
    for (int j : goods) {
      if ((st.back() | cov[nxt] | cov[j]) != (st.back() | cov[nxt])) {
        nxtGoods.push_back(j);
      }
    }
    st.push_back(st.back() | cov[nxt]);
    rec(nxtGoods);
    st.pop_back();
    rec(nxtGoods);
  }

  bb(const vector<int>& idxs, clock_t _until) : until(_until), ans(N) {
    vector<int> goods;
    for (int i : idxs) {
      if (isgood[i]) {
        goods.push_back(i);
      }
      missing.set(i, 1);
    }
    st.push_back(bitset<N>(0));
    rec(goods);
  }

  size_t getans() { return ans; }
};

struct Dsu {
	vector<int> p;
	Dsu(int n) {
		p.assign(n, 0);
		while (n--)
			p[n] = n;
	}

	int find(int v) {
		return p[v] == v ? v : p[v] = find(p[v]);
	}

	bool onion(int a, int b) {
		a = find(a);
		b = find(b);
    if (a == b) return false;
		p[b] = a;
		return true;
	}
};

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  clock_t tbegin = clock();
  int n; cin >> n;
  int m; cin >> m;
  int v[N];
  Dsu dsu(n);
  for (int i = 0; i < n; ++i) cin >> v[i];
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    if (v[j] % v[i] == 0) {
      cov[i][j] = cov[j][i] = 1;
      dsu.onion(i, j);
    }
  }
  for (int i = 0; i < n; ++i) {
    isgood[i] = 1;
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      if (cov[i] == cov[j]) isgood[i] = (i < j);
      else if ((cov[i] | cov[j]) == cov[j]) isgood[i] = 0;
    }
  }
  vector<vector<int>> sets(n);
  for (int i = 0; i < n; ++i) {
    sets[dsu.find(i)].push_back(i);
  }
  sort(sets.begin(), sets.end(), [&](vector<int>& a, vector<int>& b){
    return a.size() > b.size();
  });
  while (!sets.empty() && sets.back().empty()) {
    sets.pop_back();
  }

  int tot = 0;
  for (int i = 0; i < int(sets.size()); ++i) {
    clock_t until = tbegin + (TL * CLOCKS_PER_SEC) / (sets.size() - i);
    bb sol(sets[i], until);
    tot += sol.getans();
  }

  cout << tot << "\n";
}
