#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int N = 1e5 + 5;
const int LOG = 20;

int n;
int v[N];
int Log[N];
int id[N][LOG];
int smax[N][LOG];

void build() {
	for (int i = 0; i < n; i++) {
		id[i][0] = i;
		smax[i][0] = v[i];
	}
	for (int i = 1; i < LOG; i++)
		for (int j = 0; j + (1 << i) <= n; j++) {
			if (smax[j][i - 1] > smax[j + (1 << (i - 1))][i - 1]) {
				id[j][i] = id[j][i - 1];
				smax[j][i] = smax[j][i - 1];
			} else {
				id[j][i] = id[j + (1 << (i - 1))][i - 1];
				smax[j][i] = smax[j + (1 << (i - 1))][i - 1];
			}
		}
}

int maxQuery(int l, int r) {
	int lg = Log[r - l];
	return smax[l][lg] > smax[r - (1 << lg)][lg] ? id[l][lg] : id[r - (1 << lg)][lg];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	Log[1] = 0;
	for (int i = 2; i < N; i++)
		Log[i] = Log[i >> 1] + 1;

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> v[i];

	build();

	stack<pair<int, int>> st;
	st.push({-1, n});
	int ans = 0;
	for (int i = n - 1; i >= 0; i--) {
		while (!st.empty() && st.top().first >= v[i])
			st.pop();
		ans = max(ans, maxQuery(i, st.top().second) - i + 1);
		st.push({v[i], i});
	}
	cout << ans << "\n";
}
