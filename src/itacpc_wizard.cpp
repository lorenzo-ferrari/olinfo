// https://training.olinfo.it/task/itacpc_wizard
#include "bits/stdc++.h"
using namespace std;
using LL = long long;

#define all(x) begin(x),end(x)

struct St {
	int n;
	vector<int> t;
	St() {}
	St(int _n) {
		for (n = 1; n < _n; n <<= 1);
		t.resize(2 * n);
	}
	void upd(int p, int v) {
		for (t[p += n] += v; p > 1; p >>= 1)
			t[p >> 1] = t[p] + t[p ^ 1];
	}
	int getkth(int k) {
		int i = 1;
		while (i < n) {
			if (t[2 * i] >= k)
				i = 2 * i;
			else {
				k -= t[2 * i];
				i = 2 * i + 1;
			}
		}
		return i - n;
	}
	int cnt() {
		return t[1];
	}
};


void solve() {
	int n; cin >> n;
	int k; cin >> k;
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	a.reserve(2*n);
	for (int i = 0; i < n; ++i)
		a.push_back(-a[i]);
	auto z = a;
	sort(all(z));
	z.erase(unique(all(z)), end(z));
	auto tr = [&](int x) -> int {
		return lower_bound(all(z), x) - begin(z);
	};

	LL ans = 1e15;
	LL sum = 0;
	St st;

	auto insert = [&](int x) -> void {
		if (st.cnt() < k - 2) {
			sum += x;
		} else {
			LL kth = z[st.getkth(k - 2)];
			if (kth >= x)
				sum += x - kth;
		}
		st.upd(tr(x), 1);
	};

	auto erase = [&](int x) -> void {
		int kth = z[st.getkth(k - 2)];
		if (x <= kth) {
			sum -= x;
			if (st.cnt() > k - 2) {
				sum += z[st.getkth(k - 2 + 1)];
			}
		}
		st.upd(tr(x), -1);
	};

	multiset<int> m1, m2;
	auto sol = [&]() -> void {
		st = St(2 * n);
		sum = 0;
		m1.clear();
		m2.clear();

		m1.insert(a[0]);
		m2.insert(-a[1]);
		sum = a[0] - a[1];
		for (int i = 2; i < n; ++i) {
			if (-a[i] < *begin(m2)) {
				sum += -a[i];
				sum -= *begin(m2);
				insert(*begin(m2));
				m2.insert(-a[i]);
			} else {
				m2.insert(-a[i]);
				insert(-a[i]);
			}
		}
		ans = min(ans, sum);
		for (int i = 1; i < n - 1; ++i) {
			if (-a[i] == *begin(m2)) {
				sum -= -a[i];
				m2.erase(begin(m2));
				erase(*begin(m2));
				sum += *begin(m2);
			} else {
				m2.erase(m2.find(-a[i]));
				erase(-a[i]);
			}

			if (a[i] < *begin(m1)) {
				sum += a[i];
				sum -= *begin(m1);
				insert(*begin(m1));
				m1.insert(a[i]);
			} else {
				m1.insert(a[i]);
				insert(a[i]);
			}
			ans = min(ans, sum);
		}
	};
	sol();
	for (int i = 0; i < n; ++i)
		a[i] *= -1;
	sol();
	cout << -ans << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    for (int i = 1; i <= t; ++i) {
        solve();
    }
}
