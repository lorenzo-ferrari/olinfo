#include <iostream>
using namespace std;

typedef unsigned long long ULL;

void solve(ULL a, ULL b, ULL N, ULL &GCD, ULL &k, ULL &h) {
	if (a < b) {
		solve(b, a, N, GCD, h, k);
		return;
	}

	if (b == 0) {
		GCD = a;
		k = N / a;
		h = 1;
		return;
	}

	solve(b, a % b, N, GCD, h, k);

	h -= k * (a / b);
	ULL x = (h-1) / (a / GCD);
	k += x * (b / GCD);
	h -= x * (a / GCD);
}

int32_t main() {
	ULL N, C1, C2, GCD, a, b;
	cin >> N >> C1 >> C2;

	solve(C1, C2, N, GCD, a, b);

	cout << a << " " << b << "\n";
}
