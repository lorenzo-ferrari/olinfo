#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;

	const int N = 1e5 + 5;
	int v[N];
	int p[N];
	int c[N];

	for (int i = 0; i < n; ++i)
		cin >> v[i];
	for (int i = 0; i < n; ++i)
		cin >> p[i];
	for (int i = 0; i < n; ++i)
		cin >> c[i];


	int spesa = 0;
	int ricavo = 0;
	int denaro_iniziale = 0;
	for (int i = 0; i < n; i++)
	{
		if (c[i] < v[i] - p[i])
		{
			spesa += p[i];
			denaro_iniziale = max(denaro_iniziale, spesa);
			ricavo += v[i];
		}
		else
		{
			spesa -= c[i];
		}
	}

	cout << ricavo-spesa << " " << denaro_iniziale << endl;
}
