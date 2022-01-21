#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct group {
  int cnt;
  int x0r;
  group() : cnt(0), x0r(0) {}
  void add(int x) {
    ++cnt;
    x0r ^= x;
  }
  void erase(int x) {
    --cnt;
    x0r ^= x;
  }
  int ans() {
    return cnt - (x0r == 0);
  }
};

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  int q; cin >> q;
  vector<group> a(20);
  auto kek = [&]() {
    int ret = 0;
    for (int i = 0; i < 20; ++i) ret = max(ret, a[i].ans());
    return ret;
  };
  auto add = [&](int x) {
    for (int i = 0; i < 20; ++i)
      if (x & (1 << i))
        a[i].add(x);
  };
  auto erase = [&](int x) {
    for (int i = 0; i < 20; ++i)
      if (x & (1 << i))
        a[i].erase(x);
  };
  vector<int> v(n);
  for (int& i : v) cin >> i;
  for (int& i : v) add(i);
  cout << kek() << "\n";
  for (; q--; ) {
    int val, pos;
    cin >> pos >> val;
    --pos;
    erase(v[pos]);
    v[pos] = val;
    add(v[pos]);
    cout << kek() << "\n";
  }
}
