#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		int m; cin >> m;
		int cnt = 0, mx = n, my = m, Mx = -1, My = -1;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				char c; cin >> c;
				if (c == '1') {
					++cnt;
					mx = min(mx, i);
					my = min(my, j);
					Mx = max(Mx, i);
					My = max(My, j);
				}
			}
		}
		if (cnt != 0 && (Mx - mx + 1) * (My - my + 1) == cnt) {
			cout << "1\n";
		} else {
			cout << "0\n";
		}
	}
}
