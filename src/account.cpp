#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int chiedi(int);
void rispondi(string);

void indovina(int n) {
	char c = 'a' + n - 1;
	int m = n*(n+1)/2, l;
	string s(n, ' ');
	while (c > 'a') {
		l = chiedi(m);
		s[n - l] = c--;
		m -= l;
	}
	s[n-m] = 'a';

	rispondi(s);
}