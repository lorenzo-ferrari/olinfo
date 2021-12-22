#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	const int N = 1e6 + 5;

	int v[N];
	int n;
	cin >> n;

	v[0] = 0;
	v[n + 1] = 0;
	int cnt = 0;

	for (int i = 1; i <= n; ++i)
		cin >> v[i];

	for (int i = 1; i <= n; ++i)
	{
		if (v[i] == 0 && v[i - 1] >= 2)
		{
			++v[i];
			--v[i - 1];
		}
		else if (v[i] == 0 && v[i + 1] >= 2)
		{
			++v[i];
			--v[i + 1];
		}

		if (v[i] == 0)
			++cnt;
	}

	cout << cnt << endl;
}
