#include <bits/stdc++.h>
using namespace std;

int main() {
	#ifdef EVAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif


	int a, b;
	cin >> a >> b;

	int ans = 0;
	map <int, map <int, bool>> mp;
	for (;!mp[a][b] && (a != 1 || b != 1); ans++) {
		mp[a][b] = true;
		if (a % 2 == 0 && b % 2 == 0) {
			a >>= 1;
			b >>= 1;
		} else if (a % 2 == 1 && b % 2 == 1) {
			a = 3*a + 1;
			b = 3*b + 1;
		} else if (a % 2 == 1) {
			a += 3;
		} else if (b % 2 == 1) {
			b += 3;
		}
	}

	cout << ((mp[a][b]) ? -1 : ans) << "\n";
}
