#include <bits/stdc++.h>
using namespace std;
using LL = long long;

class Hash {
private:
	long long N, P, MOD;
	std::string S;
	std::vector<long long> pw;
	std::vector<long long> prf;

public:
	Hash(int n, int p, long long mod, std::string s) : N(n), S(s), P(p), MOD(mod) {
		pw.resize(N+1);
		prf.resize(N+1);

		pw[0] = 1;
		for (int i = 0; i < N; i++) {
			pw[i + 1] = pw[i] * P % MOD;
			prf[i + 1] = (prf[i] + (S[i] - 'a') * pw[i] % MOD) % MOD;
		}
	}

	bool cmpr(int i, int j, int len) { // [i, i+len)
		if (i > j) std::swap(i, j);
		long long h1 = ((prf[i + len] - prf[i] + MOD) % MOD) * pw[j - i] % MOD;
		long long h2 = ((prf[j + len] - prf[j] + MOD) % MOD);

		return h1 == h2;
	}
};

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  int n; cin >> n;
  string s; cin >> s;

  Hash h(n, 29, 1e9+7, s);
  for (int i = 1; i <= n; ++i) {
    if (n % i) continue;
    bool works = true;
    for (int j = 0; j < n/i/2; ++j) {
      if (!h.cmpr(j * i, (n/i - 1 - j) * i, i)) {
        works = false;
        break;
      }
    }
    if (works) {
      cout << i << "\n";
      return 0;
    }
  }
}
