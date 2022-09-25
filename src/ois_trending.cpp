#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

const int N = 5e4;
int n, q;
int t[2 * N];
string ans[2 * N];

map <int, string> ItoS;
map <string, int> StoI;

void build(){
  for(int i = n - 1; i > 0; i--) {
    if (t[i << 1] > t[i << 1 | 1] || (t[i << 1] == t[i << 1 | 1] && ans[i << 1] < ans[i << 1 | 1])) {
      t[i] = t[i << 1];
      ans[i] = ans[i << 1];
    } else {
      t[i] = t[i << 1 | 1];
      ans[i] = ans[i << 1 | 1];
    }
  }
}

void inc(int p, int val){
  for(t[p += n] += val; p > 1; p >>= 1) {
    if (t[p] > t[p ^ 1] || (t[p] == t[p ^ 1] && ans[p] < ans[p ^ 1])) {
      t[p >> 1] = t[p];
      ans[p >> 1] = ans[p];
    } else {
      t[p >> 1] = t[p ^ 1];
      ans[p >> 1] = ans[p ^ 1];
    }
  }
}

string query(int l, int r) { //interval [l, r)
  int mx = 0;
  string res;
  for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if((l & 1) && (t[l] > mx || (t[l] == mx && ans[l] < res))) { mx = t[l]; res = ans[l]; l++; }
      if((r & 1) && (t[r-1] > mx || (t[r-1] == mx && ans[r-1] < res))) { mx = t[r-1]; res = ans[r-1]; --r; }
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int tn;
  int tt;
  cin >> tn >> tt;

  vector <string> a(tn);

  set <string> seen;
  for (int i = 0; i < tn; i++) {
    cin >> a[i];
    if (seen.find(a[i]) == seen.end()) {
      ItoS[seen.size()] = a[i];
      StoI[a[i]] = seen.size();
      seen.insert(a[i]);
    }
  }

  n = seen.size();

  for (int i = 0; i < n; i++) {
    ans[i + n] = ItoS[i];
  }

  build();

  for (int i = 0; i < tt; i++) {
    int id = StoI[a[i]];
    inc(id, 1);
  }

  for (int i = 0; i < tn - tt + 1; i++) {
    cout << query(0, n) << "\n";

    inc(StoI[a[i]], -1);
    if (i + tt < tn) inc(StoI[a[i + tt]], 1);
  }
}
