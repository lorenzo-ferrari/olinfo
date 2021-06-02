#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;
	int f[101] {};
	int g;
	while (n--) {
		cin >> g;
		f[g]++;
	}

	for (int ans = 0, i = 100; i >= 0; i--) {
		ans += f[i];
		cout << ans << " ";
	}
	cout << "\n";
}
