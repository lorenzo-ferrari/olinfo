#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

#define sz size
#define F first
#define S second
typedef long long ll;

const int mod = 1e9 + 7;
const int p1 = 71;

ll fxp(ll x, ll y) {
	ll res = 1;
	while (y) {
		if (y & 1)
			res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}

ll inv(ll x) {
	return fxp(x, mod - 2);
}

ll hsh(string s) {
	ll ans = 0;
	ll mul = 1;
	int n = s.size();
	for (int i = 0; i < n; i++) {
		ans = (ans + (s[i] - 'a' + 1) * mul) % mod;
		mul = mul * p1 % mod;
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m;
	cin >> n >> m;

	vector<ll> nv(n+1);
	nv[0] = 1;
	for (ll mul = p1, i = 1; i <= n; i++) {
		nv[i] = inv(mul);
		mul = mul * p1 % mod;
	}

	string msg;
	cin >> msg;

	vector<ll> prf(n+1);
	ll mul = 1;
	for (int i = 0; i < n; i++) {
		prf[i + 1] = (prf[i] + (msg[i] - 'a' + 1) * mul) % mod;
		mul = mul * p1 % mod;
	}

	vector<pair<ll, ll>> h(n);
	vector<string> sos(n);
	for (int i = 0; i < n; i++) {
		cin >> sos[i];
		h[i] = {hsh(sos[i]), int(sos[i].sz())};
	}

	sort(h.begin(), h.end(), [](pair<ll,ll> &a, pair<ll,ll> &b){return a.S < b.S;});

	vector<long long> dp(n+1);
	dp[n] = 1;

	for (int i = n-1; i >= 0; i--)
		for (auto &x : h)
			if (i + x.S <= n && (prf[i + x.S] - prf[i] + mod) * nv[i] % mod == x.F)
				dp[i] = (dp[i] + dp[i + x.S]) % mod;

	cout << dp[0] << "\n";
}
