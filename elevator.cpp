#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int N = 1 << 18;

struct ND {
	int ans;
	int cnt;
	int lazy;
	ND () : ans(N), cnt(0), lazy(0) {}
};

ND join(ND &a, ND &b) {
	return (a.cnt > b.cnt || (a.cnt == b.cnt && a.ans < b.ans)) ? a : b;
}

ND st[2 * N];

void prop(int i) {
	if (st[i].lazy) {
		st[i].cnt += st[i].lazy;
		if (i < N) st[i << 1    ].lazy += st[i].lazy;
		if (i < N) st[i << 1 | 1].lazy += st[i].lazy;
		st[i].lazy = 0;
	}
}

void update(int i, int l, int r, int a, int b, int val) {
	prop(i);
	if (r <= a || b <= l) return;
	if (l <= a && b <= r) {
		st[i].lazy += val;
	} else {
		update(i << 1    , l, r, a, (a + b) >> 1, val);
		update(i << 1 | 1, l, r, (a + b) >> 1, b, val);
		st[i] = join(st[i << 1], st[i << 1 | 1]);
	}
	prop(i);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int i = 0; i < N; i++)
		st[N + i].ans = i;
	for (int i = N-1; i > 0; i--)
		st[i] = join(st[i << 1], st[i << 1 | 1]);

	int n;
	cin >> n;
	vector<int> t(n);
	for (int &i : t)
		cin >> i;
	update(1, t[0], t[0] + 1, 0, N, 1);
	for (int i = 1; i < n; i++) {
		if (t[i - 1] < t[i])
			update(1, t[i - 1] + 1, t[i] + 1, 0, N, 1);
		else
			update(1, t[i], t[i - 1], 0, N, 1);
	}

	int q;
	cin >> q;
	for (int i = 0, a, b; i < q; i++) {
		cin >> a >> b; // change a-th floor to b

		if (a == 0) update(1, t[0], t[0] + 1, 0, N, -1);
		if (a > 0) {
			if (t[a - 1] < t[a])
				update(1, t[a - 1] + 1, t[a] + 1, 0, N, -1);
			else
				update(1, t[a], t[a - 1], 0, N, -1);
		}
		if (a < n - 1) {
			if (t[a] < t[a + 1])
				update(1, t[a] + 1, t[a + 1] + 1, 0, N, -1);
			else
				update(1, t[a + 1], t[a], 0, N, -1);
		}
		t[a] = b;
		if (a == 0) update(1, t[0], t[0] + 1, 0, N, 1);
		if (a > 0) {
			if (t[a - 1] < t[a])
				update(1, t[a - 1] + 1, t[a] + 1, 0, N, 1);
			else
				update(1, t[a], t[a - 1], 0, N, 1);
		}
		if (a < n - 1) {
			if (t[a] < t[a + 1])
				update(1, t[a] + 1, t[a + 1] + 1, 0, N, 1);
			else
				update(1, t[a + 1], t[a], 0, N, 1);
		}

		cout << st[1].ans << " " << st[1].cnt << "\n";
	}
}
