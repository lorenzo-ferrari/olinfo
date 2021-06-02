#include <iostream>
using namespace std;

const int N = 25;
const int M = 2e5 + 1;
const int mod = 1e9 + 7;

int n, m;
int dp[N][M]; // memoization

int seq(int i, int value) {
	if (value > m)
		return 0;

	if (i == 1)
		return 1;

	if (dp[i][value] != -1)
		return dp[i][value];

	int ans = 0;
	for (int nxt = 2*value; nxt <= m; ++nxt)
		ans = (ans + seq(i-1, nxt)) % mod;

	return dp[i][value] = ans;
}

int main() {
	cin >> n >> m;

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			dp[i][j] = -1;

	int ans = 0;
	for (int i = 1; i <= m; i++)
		ans = (ans + seq(n, i)) % mod;
	cout << ans << "\n";
}

/*

totale di O(n*m) stati che calcolo una sola volta
per calcolare uno stato ci impiego O(m)

(2**(n-1))*initial_value <= m
initial_value <= m/(2**(n-1))

*/
