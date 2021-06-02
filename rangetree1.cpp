#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

const int N = 1e5;

int n;
int h;
int d[N];
int t[2 * N];
int k[2 * N];

inline void build_k() {
	for (int i = 2 * n - 1; i > 0; i--) {
		k[i] = (i < n) ? k[i << 1] + k[i << 1 | 1] : 1;
	}
}

inline void apply(int p, int b) {
	if (b)
		t[p] = k[p] - t[p];
	if (p < n)
		d[p] ^= b;
}

// build ancestors of p
// always call push(p) before
inline void build(int p) {
	for (; p > 1; p >>= 1) {
		t[p >> 1] = t[p] + t[p ^ 1];
	}
}

// delay operations down the tree
inline void push(int p) {
	for (int s = h; s > 0; s--) {
		int i = p >> s;
		apply(i << 1, d[i]);
		apply(i << 1 | 1, d[i]);
		d[i] = 0;
	}
}

int query(int l, int r) {
	l += n;
	r += n;
	push(l);
	push(r - 1);

	int ans = 0;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) ans += t[l++];
		if (r & 1) ans += t[--r];
	}

	return ans;
}

inline void flip(int l, int r) {
	l += n, r += n;
	int l0 = l, r0 = r;
	for (; l < r; l >>= 1, r >>= 1) {
		if (l & 1) apply(l++, 1);
		if (r & 1) apply(--r, 1);
	}
	push(l0);
	push(r0 - 1);
	build(l0);
	build(r0 - 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int q;
	cin >> n >> q;

	h = sizeof(int) * 8 - __builtin_clz(n);

	build_k();

	for (int i = 0, type, l, r; i < q; i++) {
		cin >> type >> l >> r;
		if (type == 0) {
			flip(l, r+1);
		} else {
			cout << query(l, r+1) << "\n";
		}
	}
}
