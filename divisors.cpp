#pragma GCC optimize ("Ofast")
long long compute(long long n) {
	long long ans = 0;
	for (long long i = 1; i*i <= n; ++i)
		ans += 2 * ((n - i*i) / i) + 1;
	return ans;
}
