#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, l;
	cin >> n >> l;
	int m1;
	cin >> m1;
	vector<string> f(m1);
	unordered_map<string, int> mp;
	for (int i = 0; i < m1; i++) {
		cin >> f[i];
		mp[f[i]] = 0;
	}
	for (int i = 1, k; i < n; i++) {
		cin >> k;
		unordered_set<string> st;
		string s;
		for (int j = 0; j < k; j++) {
			cin >> s;
			if (mp.find(s) != mp.end())
				st.insert(s);
		}
		for (string x : st)
			++mp[x];
	}
	for (string &x : f)
		cout << mp[x] << " ";
	cout << "\n";
}
