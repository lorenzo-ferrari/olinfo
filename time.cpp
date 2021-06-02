#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int h0, h1;
	int m0, m1;

	cin >> h0 >> m0;
	cin >> h1 >> m1;

	int m_slept = 60 * (h1 - h0) + (m1 - m0);
	if (m_slept <= 0)
		m_slept += 24 * 60;

	cout << (m_slept / 60) << " " << (m_slept % 60) << endl;
}
