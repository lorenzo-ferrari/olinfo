#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int n;
vector<vector<int>> fa;
vector<vector<int>> fr;

void init(int _n) {
	n = _n;
	fa.resize(n+1);
	fr.resize(n+1);
}

int day = 1;
void log(vector<int> &add, vector<int> &rm) {
	for (int i = day; i <= n; i += i & -i) {
		for (int &j : add) fa[i].push_back(j);
		for (int &j :  rm) fr[i].push_back(j);
	}
	if (day++ == n) {
		for(auto &x : fa) sort(x.begin(), x.end());
		for(auto &x : fr) sort(x.begin(), x.end());
	}
}

int answer(int d, int y) {
	int ans = 0;
	for (int i = d; i > 0; i -= i & -i) {
		ans += fa[i].end() - lower_bound(fa[i].begin(), fa[i].end(), y);
		ans -= fr[i].end() - lower_bound(fr[i].begin(), fr[i].end(), y);
	}
	return ans;
}

#ifndef EVAL
int main() {
	int n, q;
	cin >> n >> q;
	
	init(n);
	
	vector<int> added, removed;
	for (int i = 1; i <= n; i++) {
		added.clear();
		int a;
		cin >> a;
		for (int j = 0; j < a; j++) {
			int k;
			cin >> k;
			added.push_back(k);
		}
		removed.clear();
		int r;
		cin >> r;
		for (int j = 0; j < r; j++) {
			int k;
			cin >> k;
			removed.push_back(k);
		}
		log(added, removed);
	}
	
	for (int i = 0; i < q; i++) {
		int d, x;
		cin >> d >> x;
		cout << answer(d, x) << "\n";
	}
	
	return 0;
}
#endif
