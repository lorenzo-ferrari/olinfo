#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;

	const int N = 1e4 + 5;

	int v[N];

	for (int i = 0; i < n; ++i)
		cin >> v[i];

	int d = INT_MAX;
	for (int i = 0; i < n; ++i)
		d = min(d, max(v[i]-v[0], v[n-1]-v[i]));

	cout << d << endl;
}
