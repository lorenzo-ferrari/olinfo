#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;

	int cnt = -1;
	int arr = INT_MAX;
	for (int i = 0, t; i < n; ++i)
	{
		cin >> t;
		if (i + t < arr)
		{
			arr = i + t;
			++cnt;
		}
	}

	cout << arr << " " << cnt << endl;
}
