#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

#define N 400000
#define mod 1000000007

int n;
int a[N], dp[N];

int get_int() {
	int n = 0;
	char c = getchar_unlocked();

	while ('0' <= c && c <= '9') {
		n = 10 * n + c - '0';
		c = getchar_unlocked();
	}

	return n;
}

void print(int n) {
	int i = 0;
	char st[10];
	while (n) {
		st[i++] = n % 10 + '0';
		n /= 10;
	}
	while (i)
		putchar_unlocked(st[--i]);
}

int32_t main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n = get_int();

	for (int i = 0; i < n; ++i)
		a[i] = get_int();

	dp[n - 1] = 1;
	for (int i = n - 2; i >= 0; --i)
		for (int j = 1; i + j < n; j <<= 1)
			if (!((a[i] + a[i + j]) & (j - 1))) {
				dp[i] = (dp[i] + dp[i + j]) % mod;
				if (dp[i] > mod) dp[i] -= mod;
			}

	print(dp[0]);
}
