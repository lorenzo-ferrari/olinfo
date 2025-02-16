#include <bits/stdc++.h>
#pragma GCC otpimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

unordered_set <string> vis;

int64_t _n;
string cur;

void prepara(int n) {
	_n = n;
	for (int64_t i = 1; i <= n; ++i) {
		cur.push_back(i);
	}
}

string f(int k) {
	string ans = cur;
	reverse(ans.begin(), ans.begin() + k);

	return ans;
}

int ribalta() {
	vis.insert(cur);

	for (int i = 2; i <= _n; ++i) {
		if (vis.find(f(i)) == vis.end()) {
			cur = f(i);
			return i;
		}
	}

	return 1;
}
