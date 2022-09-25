#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

const int N = 1e5;
const int M = 1e6;

int64_t n;
int64_t b, p;
int64_t d[10];

bool pr[M];

int64_t eval(string s) {
	int ans = b;
	int is = stoi(s);
	if (pr[is])
		ans += is + p;

	int sum = 0, prod = 1;
	for (char c : s) {
		ans += d[c - '0'];
		sum += c - '0';
		prod *= c - '0';
	}

	if (pr[sum])
		ans += sum;

	if (pr[prod])
		ans += prod;

	return ans;
}

void init() {
	fill(pr, pr+M, true);
	for (int i = 2; i < (M >> 1); i++) {
		if (pr[i]) {
			for (int j = i+i; j < M; j+=i) {
				pr[j] = false;
			}
		}
	}
	pr[0] = false;
	pr[1] = false;
}

int main() {
	init();

	int n;
	string l[N];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> l[i];

	cin >> b >> p;
	cin >> d[2] >> d[3] >> d[5] >> d[7];

	int64_t ans = 0;
	string s;
	for (int i = 0; i < n; i++) {
		s = l[i];
		int64_t val = 0;
		bool nz = true;

		for (char &c : s) {
			char mem = c;
			for (char dig = '0'; dig <= '9'; dig++) {
				if (nz) {
					nz = false;
					continue;
				}
				c = dig;
				val = max(val, eval(s));
			}
			c = mem;
		}

		ans += val;
	}

	cout << ans << "\n";
}
