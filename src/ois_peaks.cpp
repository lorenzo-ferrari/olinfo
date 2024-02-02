#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr LL mod = 1e9 + 7;
static constexpr int LG = 60;

int main() {
	int n; cin >> n;
	int m; cin >> m;
	vector<int> a(n), b(m);
	for (int& i : a) cin >> i;
	for (int& i : b) cin >> i;
	LL ca = 0, cb = 0;
	for (int i = 0; i < n; ++i) {
		ca += (i == 0 || a[i - 1] < a[i]) && (i == n-1 || a[i] > a[i+1]);
	}
	for (int i = 0; i < m; ++i) {
		cb += (i == 0 || b[i - 1] < b[i]) && (i == m-1 || b[i] > b[i+1]);
	}

	cout << ca * cb << "\n";
}
