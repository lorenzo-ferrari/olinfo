#include "bits/stdc++.h"
using namespace std;
using LL = long long;

class Hash {
private:
    static constexpr int SZ = 2;
    static constexpr LL mod = 2e9 + 11;
    static constexpr array<LL, SZ> pr{3, 5};
    
public:
    int n;
    string s;
    vector<array<LL, SZ>> hsh;
    vector<array<LL, SZ>> pws;

    Hash(int _n, string _s) : n(_n), s(_s) {
        hsh.resize(n + 1);
        pws.resize(n + 1);
        for (int j = 0; j < SZ; ++j) {
            hsh[0][j] = 0;
            pws[0][j] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < SZ; ++j) {
                pws[i][j] = pws[i - 1][j] * pr[j] % mod;
                hsh[i][j] = pr[j] * hsh[i - 1][j] + (s[i - 1] - '`');
                hsh[i][j] %= mod;
            }
        }
    }

    array<LL, SZ> get_hash(int l, int len) {
        array<LL, SZ> ans;
        for (int j = 0; j < SZ; ++j) {
            ans[j] = (hsh[l + len][j] - hsh[l][j] * pws[len][j] % mod + mod) % mod;
        }
        return ans;
    }

    bool same(int l, int r, int len) {
        return get_hash(l, len) == get_hash(r, len);
    }
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n; cin >> n;
	string a; cin >> a; a += "0";
	string b; cin >> b; b += "0";
	for (char& c : b) {
		c ^= 1;
	}
	Hash ha(n+1, a), hb(n+1, b);
	int q; cin >> q;
	for (int i = 0, x, y, l; i < q; ++i) {
		cin >> x >> y >> l;
		int ll = 0, rr = l+1;
		while (rr - ll > 1) {
			int mm = (ll + rr) / 2;
			if (ha.get_hash(x, mm) == hb.get_hash(y, mm)) {
				ll = mm;
			} else {
				rr = mm;
			}
		}
		if (ll == l || a[x + ll] == '0') {
			cout << "1 ";
		} else {
			cout << "0 ";
		}
	}
	cout << "\n";
}
