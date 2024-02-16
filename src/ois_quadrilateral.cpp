#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
	int n; cin >> n;
	vector<LL> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	sort(begin(a), end(a));
	for (int i = 3; i < n; ++i) {
		if (a[i] < a[i-1] + a[i-2] + a[i-3]) {
			for (int j = i-3; j <= i; ++j) {
				cout << a[j] << " \n"[j == i];
			}
			return 0;
		}
	}
	cout << -1 << "\n";
}
