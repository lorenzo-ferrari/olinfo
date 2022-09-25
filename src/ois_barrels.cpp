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
        putchar_unlocked('\n');
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

const int N = 1e6;

int main() {
	int n = get_int();
	int t = get_int();

	int c[N];
	int nxt[N];
	int used[N]{};

	for (int i = 0; i < n; ++i) {
		c[i] = get_int();
		nxt[i] = i + 1;
	}

	char type;
	int k, u, q;
	stack <int> st;
	while (t--) {
		type = getchar_unlocked();
		getchar_unlocked();
		if (type == 'P') {
			k = get_int();
			u = get_int();
			while (u < n && k) {
				int d = min(k, c[u]);
				k -= d;
				c[u] -= d;
				used[u] += d;

				while (u < n && !c[u]) {
					st.push(u);
					u = nxt[u];
				}

				while (!st.empty()) {
					nxt[st.top()] = u;
					st.pop();
				}
			}
		}
		else {
			q = get_int();
			print(used[q]);
		}
	}
}
