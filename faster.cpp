#include <bits/stdc++.h>
using namespace std;

const int INF = 1e5 + 69;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	#ifdef EVAL
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	int n;
	string w;
	cin >> w >> n;
	vector <int> vel(n+1);
	vel[0] = 1;
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		vel[i] = vel[i-1];
		vel[i] += (s == w);
	}

	int ans = 0;
	for (int i = 0; i < n; i += vel[i])
		ans++;
	cout << ans << "\n";
}
