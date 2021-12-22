#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

const int N = 1e5;

int n;
int h;
int d[N];
int t[3][2 * N];

void init() {
	for (int i = 2*n - 1; i > 0; i--) {
		t[0][i] = (i < n) ? t[0][i << 1] + t[0][i << 1 | 1] : 1;
	}
}

void apply(int p, int val) {
	if (val == 1) {
		swap(t[0][p], t[1][p]);
		swap(t[0][p], t[2][p]);

		if (p < n) {
			d[p] += 1;
			if (d[p] >= 3)
				d[p] -= 3;
		}
	} else if (val == 2) {
		swap(t[0][p], t[1][p]);
		swap(t[1][p], t[2][p]);

		if (p < n) {
			d[p] += 2;
			if (d[p] >= 3)
				d[p] -= 3;
		}
	}
}

// chiama sempre prima push(p)
void build(int p) {
	for (; p > 1; p >>= 1) {
		t[0][p >> 1] = t[0][p] + t[0][p ^ 1];
		t[1][p >> 1] = t[1][p] + t[1][p ^ 1];
		t[2][p >> 1] = t[2][p] + t[2][p ^ 1];
	}
}

// propaga le delayed operations down the tree
void push(int p) {
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
		if (l & 1) ans += t[0][l++];
		if (r & 1) ans += t[0][--r];
	}

	return ans;
}

void inc(int l, int r) {
	l += n;
	r += n;
	int l0 = l;
	int r0 = r;
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

	init();

	for (int i = 0, tp, l, r; i < q; i++) {
		cin >> tp >> l >> r;
		if (tp == 0) {
			inc(l, r + 1);
		} else {
			cout << query(l, r + 1) << "\n";
		}
	}
}
