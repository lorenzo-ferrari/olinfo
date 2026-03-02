#include <iostream>
using namespace std;
using LL = long long;

static constexpr LL mod = 1e9 + 7;

LL fexp(LL x, LL y) {
	LL ans = 1;
	while (y) {
		if (y & 1)
			ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}
LL inv(LL x) {
	return fexp(x, mod - 2);
}

int main() {
	int N; cin >> N;

	LL ans = 1;
	LL factN = 1, fact2N = 1;
	for (LL i = 1; i <= N; ++i)
		factN = factN * i % mod;
	for (LL i = 1; i <= 2 * N; ++i)
		fact2N = fact2N * i % mod;
	ans = fact2N * inv(factN) % mod;
	ans = ans * inv(factN) % mod;
	ans = ans * inv(N + 1) % mod;

	cout << (factN + mod - ans) % mod << "\n";
}
