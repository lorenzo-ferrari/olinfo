#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define int long long

const int N = (1 << 16);
const int INF = 1e9;

struct nd {
	int sum = 0;
	int arr = -INF;
	int pref = -INF;
	int suff = -INF;

	nd() {}
	nd(int x) : sum(x), arr(x), pref(x), suff(x) {}
};

nd join(nd a, nd b) {
	nd ans;
	ans.sum = a.sum + b.sum;
	ans.arr = max(max(a.arr, b.arr), a.suff + b.pref);
	ans.pref = max(a.pref, a.sum + b.pref);
	ans.suff = max(b.suff, a.suff + b.sum);
	return ans;
}

struct st {
	nd t[2 * N];

	st(vector<int> a) {
		for (int i = 0; i < a.size(); i++)
			t[i + N] = nd(a[i]);
		for (int i = N - 1; i > 0; i--)
			t[i] = join(t[i << 1], t[i << 1 | 1]);
	}

	void update(int p, int val) {
		t[p += N] = nd(val);
		for (; p > 1; p >>= 1)
			t[p >> 1] = (p & 1) ? join(t[p ^ 1], t[p]) : join(t[p], t[p ^ 1]);
	}

	nd query(int i, int l, int r, int a, int b) {
		if (b <= l || r <= a) return nd();
		if (l <= a && b <= r) return t[i];
		return join(query(i << 1    , l, r, a, (a + b) >> 1),
								query(i << 1 | 1, l, r, (a + b) >> 1, b));
	}
};

int32_t main() {
#ifdef EVAL
	ifstream cin("input.txt");
	ofstream cout("output.txt");
#endif

	int n;
	cin >> n;

	vector<int> a(n);
	for (int &i : a)
		cin >> i;

	st t(a);

	int q;
	cin >> q;
	while (q--) {
		int type, x, y;
		cin >> type >> x >> y;

		if (type == 0)
			t.update(x-1, y);
		else
			cout << t.query(1, x-1, y, 0, N).arr << "\n";
	}
}
