#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int N = 50000;

int n, k;
char t[2 * N];
string s;

inline void build(){
    for(int i = n - 1; i > 0; i--)
      t[i] = max(t[i << 1], t[i << 1 | 1]);
}

inline char query(int l, int r) { //interval [l, r)
    char res = 'a';
    for(l += n, r += n; l < r; l >>= 1, r >>= 1){
        if(l & 1) res = max(t[l++], res);
        if(r & 1) res = max(t[--r], res);
    }
    return res;
}

inline int find_first(int i, char c) {
  while (i < n && s[i] != c)
    i++;
  return i;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> k >> s;
  for (int i = 0; i < n; i++)
    t[i + n] = s[i];

  build();

  string ans;
  for (int i = 0; i < n-k;) {
    int pos = find_first(i, query(i, i + k + 1));
    k -= pos - i;
    ans.push_back(s[pos]);
    i = pos + 1;
  }

  cout << ans << "\n";
}
