#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

#define int int64_t

const int N = 1e5 + 42;
const int mod = 1e9 + 7;

int n;
int fct;
int f[10];
int finv[N];

int sum = 0;
int prd = 1;
int ans = 0;

inline int fxp(int x, int y) {
	int res = 1;
	while (y) {
		if (y & 1)
			res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}

	return res;
}

inline int coeff() {
	int res = fct;
	for (int i = 0; i < 10; i++) {
		res = (res * finv[f[i]]) % mod;
	}

	return res;
}

inline void solve(int c, int i) {
  if (sum + n - i == prd) {
		f[1] = n - i;
    ans = (ans + coeff()) % mod;
    return;
  }

  if (c == 9) {
    return;
  }

  c++;
  int of = f[c];
	int os = sum;
  int op = prd;
  for (; i <= n; i++) {
    if (prd > sum + (n-i))
      break;
    solve(c, i);

    f[c]++;
    sum += c;
    prd *= c;
  }

	f[c] = of;
	sum = os;
	prd = op;
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n;

	if (n == 1) {
		cout << 10 << "\n";
		return 0;
	}

	// init
	fct = 1;
	finv[0] = 1;
	for (int i = 1; i <= n; i++) {
		fct = fct * i % mod;
		finv[i] = fxp(fct, mod - 2);
	}
	//

  solve(1, 0);

  cout << ans + 1 << "\n"; // +1 (000...)
}
