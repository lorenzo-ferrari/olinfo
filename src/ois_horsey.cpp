#include "bits/stdc++.h"
using namespace std;
using LL = long long;
using m_t = array<LL, 2>;
using mm_t = array<m_t, 2>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t; cin >> t;
	while (t--) {
		LL n, m, h, w;
		cin >> n >> m >> h >> w;
		if (h < w)
			swap(h, w);
		if (n < m)
			swap(n, m);
		if ((h + w) % 2 == 0 || __gcd(h, w) != 1) {
			cout << "NO\n";
		} else if (m < (h + w) || n < (2 * h)) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
		}
	}
}
