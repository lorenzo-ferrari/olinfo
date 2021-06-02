#include <iostream>
#pragma GCC optimize ("O3")
using namespace std;

inline int64_t get_int() {
    int64_t n = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        n = (n << 3) + (n << 1) + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

inline void print(int64_t n) {
    int64_t i = 0;
    char S[20];
    if (n == 0) {
        putchar_unlocked('0');
        putchar_unlocked(' ');
        return;
    }
    while (n) {
        S[i++] = n % 10 + '0';
        n /= 10;
    }
    while (--i >= 0)
        putchar_unlocked(S[i]);
    putchar_unlocked(' ');
}

const int MAXN = 1e6 + 1;

int64_t m, n, ans, acc;
int64_t l[MAXN], nxt[MAXN], pref[MAXN];

int32_t main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	m = get_int(); n = get_int();

	if (m == 0) {
		int64_t z = 0, ans = 0;
		while (n--) {
			z = (get_int()) ? 0 : z + 1;
			ans += z;
		}

		print(ans);
		return 0;
	}

	l[0] = get_int(); pref[0] = l[0];
	for (int i = 1; i < n; i++) { l[i] = get_int(); pref[i] = pref[i - 1] + l[i];}

	nxt[n] = n;
	nxt[n - 1] = n;
	for (int i = n - 2; i >= 0; i--)
		nxt[i] = (l[i + 1]) ? i + 1 : nxt[i + 1];

	int64_t ans = 0, l = 0, r = 0;
	while (r < n && nxt[r] != n && pref[r] < m)
		r = nxt[r];

	if (pref[r] == m) ans += (nxt[r] - r);

	for (l = 1; l < n; l++) {
		while (r < n && nxt[r] != n && pref[r] - pref[l-1] < m) {
			r = nxt[r];
		}

		if (pref[r] - pref[l-1] == m) ans += (nxt[r] - r);
	}

	print(ans);
}
