#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr LL mod = 1e9 + 7;
static constexpr int LG = 60;

int main() {
	int n; cin >> n;
	map<LL, int> m;
	for (int i = 0, s; i < n; ++i) {
		cin >> s;
		++m[s];
	}
	LL b = 0, h = 0;
	for (auto it = prev(end(m));; --it) {
		if (it->second >= 4) {
			b = max(b, it->first);
			h = max(h, it->first);
			break;
		} else if (it->second >= 2) {
			if (b == 0) {
				b = it->first;
			} else if (h == 0) {
				h = it->first;
				break;
			}
		}
		if (it == begin(m)) {
			break;
		}
	}

	cout << b * h << "\n";
}
