#include <bits/stdc++.h>
using namespace std;

const long long N = (1 << 20);
const long long INF = 1e15;

struct lazySegment {
	struct node {
		long long sum = 0;
		long long min = INF;
		long long lazy = 0;
		long long sett = INF;
		node (long long a = 0, long long b = INF) {
			sum = a, min = b, lazy = 0, sett = INF;
		}
	};

	node join(node &a, node &b) {
		return node(a.sum + b.sum, std::min(a.min, b.min));
	}

	// actual segment tree
	node st[2 * N];

	lazySegment () {}
	lazySegment (vector<long long> a) {
		for (int i = 0; i < a.size(); ++i)
			st[i + N] = node(a[i], a[i]);
		for (int i = N - 1; i > 0; --i)
			st[i] = join(st[i << 1], st[i << 1 | 1]);
	}

	void prop(int i, int a, int b) {
		if (st[i].lazy) {
			st[i].min += st[i].lazy;
			st[i].sum += (b - a) * st[i].lazy;
			if (i < N) {
				if (st[i << 1].sett ^ INF)
					st[i << 1].sett += st[i].lazy, st[i << 1].lazy = 0;
				else
					st[i << 1].lazy += st[i].lazy;
				if (st[i << 1 | 1].sett ^ INF)
					st[i << 1 | 1].sett += st[i].lazy, st[i << 1 | 1].lazy = 0;
				else
					st[i << 1 | 1].lazy += st[i].lazy;
			}
			st[i].lazy = 0;
		}
		else if (st[i].sett ^ INF) {
			st[i].lazy = 0;
			st[i].min = st[i].sett;
			st[i].sum = (b - a) * st[i].sett;
			if (i < N) st[i << 1    ].sett = st[i].sett, st[i << 1    ].lazy = 0;
			if (i < N) st[i << 1 | 1].sett = st[i].sett, st[i << 1 | 1].lazy = 0;
			st[i].sett = INF;
		}
	}

	void _set(int i, int l, int r, int a, int b, long long val) {
		prop(i, a, b);
		if (r <= a || b <= l) return;
		if (l <= a && b <= r) {
			st[i].sett = val, st[i].lazy = 0;
			prop(i, a, b);
		}
		else {
			_set(i<<1  , l, r, a, (a + b) >> 1, val);
			_set(i<<1|1, l, r, (a + b) >> 1, b, val);
			st[i] = join(st[i << 1], st[i << 1 | 1]);
		}
	}

	void _add(int i, int l, int r, int a, int b, long long val) {
		prop(i, a, b);
		if (r <= a || b <= l) return;
		if (l <= a && b <= r) {
			if (st[i].sett ^ INF)
				st[i].sett += val;
			else
				st[i].lazy += val;
			prop(i, a, b);
		}
		else {
			_add(i << 1    , l, r, a, (a + b) >> 1, val);
			_add(i << 1 | 1, l, r, (a + b) >> 1, b, val);
			st[i] = join(st[i << 1], st[i << 1 | 1]);
		}
	}

	long long _sum(int i, int l, int r, int a, int b) {
		prop(i, a, b);
		if (r <= a || b <= l) return 0;
		if (l <= a && b <= r) return st[i].sum;
		return _sum(i << 1    , l, r, a, (a + b) >> 1) +
					 _sum(i << 1 | 1, l, r, (a + b) >> 1, b);
	}

	long long _min(int i, int l, int r, int a, int b) {
		prop(i, a, b);
		if (r <= a || b <= l) return INF;
		if (l <= a && b <= r) return st[i].min;
		return std::min(_min(i << 1    , l, r, a, (a + b) >> 1),
										_min(i << 1 | 1, l, r, (a + b) >> 1, b));
	}

	int _lower_bound(int i, int l, int r, int a, int b, long long x) {
		prop(i, a, b);
		if (r <= a || b <= l || st[i].min > x) return -1;
		if (i >= N) return a;
		int o = _lower_bound(i << 1, l, r, a, (a + b) >> 1, x);
		if (o != -1)
				return o;
		return _lower_bound(i << 1 | 1, l, r, (a + b) >> 1, b, x);
	}

	long long get_sum(int l, int r) { return _sum(1, l, r, 0, N); }
	long long get_min(int l, int r) { return _min(1, l, r, 0, N); }
	void add(int l, int r, long long x) { _add(1, l, r, 0, N, x); }
	void set_range(int l, int r, long long x) { _set(1, l, r, 0, N, x); }
	int lower_bound(int l, int r, long long x) { return _lower_bound(1, l, r, 0, N, x); }
};

lazySegment t;

void init(vector<long long> a) { t = lazySegment(a); }
long long get_sum(int l, int r) { return t.get_sum(l, r); }
long long get_min(int l, int r) { return t.get_min(l, r); }
void add(int l, int r, long long x) { t.add(l, r, x); }
void set_range(int l, int r, long long x) { t.set_range(l, r, x); }
int lower_bound(int l, int r, long long x) { return t.lower_bound(l, r, x); }
