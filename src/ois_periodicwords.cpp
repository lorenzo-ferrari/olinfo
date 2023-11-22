#include "bits/stdc++.h"
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
using namespace std;
using LL = long long;

class Hash {
private:
    static constexpr int SZ = 2;
    static constexpr LL mod = 2e9 + 11;
    static constexpr LL pr = 29;
    
public:
    int n;
    string s;
    vector<LL> hsh;
    vector<LL> pws;

    Hash(int _n, string _s) : n(_n), s(_s) {
        hsh.resize(n + 1);
        pws.resize(n + 1);
        hsh[0] = 0;
        pws[0] = 1;
        for (int i = 1; i <= n; ++i) {
            pws[i] = pws[i - 1] * pr % mod;
            hsh[i] = pr * hsh[i - 1] + (s[i - 1] - '`');
            hsh[i] %= mod;
        }
    }

    LL get_hash(int l, int len) {
        return (hsh[l + len] - hsh[l] * pws[len] % mod + mod) % mod;
    }

    bool same(int l, int r, int len) {
        return get_hash(l, len) == get_hash(r, len);
    }
};

int main() {
    static constexpr int N = 100000;
    vector<int> d[N+1];

    for (int i = 1; i <= N; ++i) {
        for (int j=i+i; j <= N; j += i) {
            d[j].push_back(i);
        }
        reverse(begin(d[i]), end(d[i]));
    }

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    string s; cin >> s;
    Hash h(n, s);
    int q; cin >> q;
    for (int i = 0, l, r; i < q; ++i) {
        cin >> l >> r;
        int len = r - l + 1;
        bool works = false;
        for (int j : d[len]) {
            if (h.same(l, l+j, len - j)) {
                works = true;
                break;
            }
        }
        cout << (works ? "YES" : "NO") << "\n";
    }
}
