#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	long long r, c, k;

	cin >> r >> c >> k;

	long long ans = (1 + (r - 1) / k) * (1 + (c - 1) / k);

	cout << ans << endl;
}
