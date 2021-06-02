#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

inline int get_int() {
    int n = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        n = (n << 3) + (n << 1) + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

inline void print(int n) {
    int i = 0;
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
    putchar_unlocked('\n');
}

int n;
int m;
int lis(vector <vector<int>> &v) {
	int ans = 0;
	vector <int> l(m + 2, 1e9); l[0] = 0;
	for (auto &x : v) {
		vector <pair<int, int>> buff;
		for (int &i : x) {
			int it = lower_bound(l.begin(), l.end(), i) - l.begin();
			buff.push_back({it, i});
			ans = max(ans, it);
		}
		for (auto &i : buff)
			l[i.first] = min(l[i.first], i.second);
	}

	return ans;
}

int main() {
#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	n = get_int();
	m = get_int();
	int c = get_int();

	vector <vector<int>> g(n+1);
	for (int i = 0, a, b; i < c; i++) {
		a = get_int();
		b = get_int();
		g[a].push_back(b);
	}

	vector <int> v;
	for (auto &x : g)
		sort(x.begin(), x.end());

	print(2 * lis(g));
}
