#include <iostream>
#include <vector>
#pragma GCC optimize ("O3")
using namespace std;

typedef long long LL;

struct tile_t {
	LL u = 0;
	LL d = 0;
	LL l = 0;
	LL r = 0;
};

int A, B, N;
LL toR[50];
LL toD[50];
LL used;
int ans[5][5];

istream& operator>>(istream& in, tile_t &x) {
	for (int i = 0; i < A; i++) {
		for (int j = 0; j < A; j++) {
			char c; in >> c;
			if (c != '1') continue;
			if (i == 0) x.u |= (1LL << j);
			if (j == 0) x.l |= (1LL << i);
			if (i == A-1) x.d |= (1LL << j);
			if (j == A-1) x.r |= (1LL << i);
		}
	}
	return in;
}

void solve(int n) {
	if (n == B * B) {
		for (int i = 0; i < B; i++) {
			for (int j = 0; j < B; j++)
				cout << ans[i][j] << " ";
			cout << "\n";
		}
		exit(0);
	}

	int a = n / B, b = n % B;
	LL mask = ~used;
	if (a) mask &= toD[ans[a-1][b]];
	if (b) mask &= toR[ans[a][b-1]];
	for (int i = 0; i < N; i++) {
		if (mask & (1LL << i)) {
			ans[a][b] = i;
			used |= (1LL << i);
			solve(n + 1);
			used ^= (1LL << i);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> A >> B >> N;

	vector<tile_t> tiles(N);
	for (auto &x : tiles)
		cin >> x;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (tiles[i].r == tiles[j].l) toR[i] |= (1LL << j);
			if (tiles[i].d == tiles[j].u) toD[i] |= (1LL << j);
		}
	}

	solve(0);
}
