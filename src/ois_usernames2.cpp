#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
	string s; cin >> s;
	int n; cin >> n;
	set<string> u;
	for (int i = 0; i < n; ++i) {
		string t; cin >> t;
		u.insert(t);
	}
	if (!u.count(s)) {
		cout << s << "\n";
	} else {
		int c = 1;
		while (u.count(s + to_string(c))) {
			++c;
		}
		cout << s + to_string(c) << "\n";
	}
}
