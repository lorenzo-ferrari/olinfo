#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

struct pt {
	double x;
	double y;
};

bool cmp (pt &a, pt &b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

inline bool over (pt a, pt b, pt c) {
	return a.x != b.x && (c.y - a.y) > ((c.x - a.x) * (b.y - a.y) / (b.x - a.x));
}

inline bool under (pt a, pt b, pt c) {
	return a.x != b.x && (c.y - a.y) < ((c.x - a.x) * (b.y - a.y) / (b.x - a.x));
}

int convexHull (vector <pt> &v) {
	if (v.size() == 1)
		return 1;

	sort(v.begin(), v.end(), &cmp);

	pt a = v[0], b = v.back();
	vector <pt> up, down;

	up.push_back(a);
	down.push_back(a);

	for (int i = 1; i < v.size(); i++) {
		if (i == v.size() - 1 || over(a, b, v[i])) {
			while (up.size() > 1 && !over(up[up.size()-2], v[i], up.back()))
				up.pop_back();
			up.push_back(v[i]);
		}
		if (i == v.size() - 1 || under(a, b, v[i])) {
			while (down.size() > 1 && !under(down[down.size()-2], v[i], down.back()))
				down.pop_back();
			down.push_back(v[i]);
		}
	}

	return up.size() + down.size() - 2;
}

int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;

	vector <pt> v(n);
	for (auto &x : v)
		cin >> x.x >> x.y;

	cout << convexHull(v) << "\n";
}
