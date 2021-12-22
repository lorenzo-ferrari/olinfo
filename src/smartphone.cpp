#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;

	int c, mx = 0;
	long long sum = 0;
	for (int i = 0; i < n; ++i)
	{
		cin >> c;
		if (c > mx)
		{
			mx = c;
			sum += c;
		}
	}

	cout << sum << endl;
}
