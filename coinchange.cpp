#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	ll tot = 0;
	ll val[15] {1,2,5,10,20,50,100,200,500,1000,2000,5000,10000,20000,50000};
	for (int i = 0, v; i < 15; i++) {
		cin >> v;
		tot += v*val[i];
	}

	vector <ll> ans;

	for (int i = 14; i >= 0; i--) {
		ans.push_back(tot/val[i]);
		tot %= val[i];
	}

	reverse(ans.begin(), ans.end());
	for (ll i : ans) cout << i << " ";
	cout << "\n";
}
//100 10 50 10 0 13 11 10 1 10 100 1000  200 1 1
