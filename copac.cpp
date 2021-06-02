#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

inline int get_int() {
    int n = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        n = 10 * n + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

inline void print(int n) {
    int i = 0;
    char S[20];

    while (n) {
        S[i++] = n % 10 + '0';
        n /= 10;
    }
    while (--i >= 0)
        putchar_unlocked(S[i]);
    putchar_unlocked('\n');
}

int n;
vector <int> ans;
vector <int> g[100001];

inline int dfs(int v, int p) {
	int c;
	int sum = 0;
	bool ok = true;
	for (int u : g[v]) {
		if (u ^ p) {
			c = dfs(u, v);
			sum += c;
			if (c > (n >> 1))
				ok = false;
		}
	}

	if (n - 1 - sum > (n >> 1))
		ok = false;

	if (ok)
		ans.push_back(v);

	return 1 + sum;
}

int main() {
	n = get_int();
	for (int i = 1, a, b; i < n; i++) {
		a = get_int(), b = get_int();
		g[a].push_back(b);
		g[b].push_back(a);
	}

	dfs(1, -1);

	sort(ans.begin(), ans.end());

	for (int &i : ans)
		print(i);
}
