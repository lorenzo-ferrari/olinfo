#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const LL mod = 2011;
const LL mod2 = 1e9 + 7;
const LL p = 3;

std::vector<int> z_algo(std::string s) {
	int n = s.size();
	std::vector<int> Z(n);
	for (int i = 1, L = 0, R = 0; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R - L] == s[R])
				R++;
			Z[i] = R - L;
			R--;
		}
		else {
			if (i + Z[i - L] <= R)
				Z[i] = Z[i - L];
			else {
				L = i; // s[R] != s[R-L+1], sarei andato avanti
				while (R < n && s[R - L] == s[R])
					R++;
				Z[i] = R - L; R--;
			}
		}
	}

	return Z;
}

int lsp(string s) {
    auto v = z_algo(s);
    int n = v.size();
    for (int i = n-1; i > 0; --i) {
        if (v[n-i] == i) {
            return i;
        }
    }
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int m; cin >> m;
    int n; cin >> n;
    string s; cin >> s;
    assert((int)s.size() == m);
    vector<array<int, 2>> nxt(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (j == s[i] - '0') {
                nxt[i][j] = i+1;
            } else {
                string t = s.substr(0,i) + string(1, j + '0');
                // trova max suff which is also pref
                nxt[i][j] = lsp(t);
            }
        }
    }
    vector<vector<int>> dp(n+1, vector<int>(m));;
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        for (int k = 0; k < 2; ++k) {
            int nn = nxt[j][k];
            if (nn == m) continue;
            dp[i+1][nn] += dp[i][j];
            dp[i+1][nn] %= mod;
        }
    }
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        ans += dp[n][i];
    }
    cout << ans % mod << "\n";
}
