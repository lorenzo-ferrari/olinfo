#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define SQ(a) (a)*(a)

struct pt {
	LL x;
	LL y;
	pt () {}
	pt (LL X, LL Y) : x(X), y(Y) {}
};

LL operator ^(pt A, pt B) { return A.x*B.y - A.y*B.x; }

double Dist(pt A, pt B) { return sqrt(SQ(A.x-B.x) + SQ(A.y-B.y)); }
double Area(pt A, pt B, pt C) { return abs((A^B) + (B^C) + (C^A)) / 2.0; }

LL fr(LL N, LL D) {
	if (D == 0)
		return -1;

	LL g = __gcd(abs(N), abs(D));
	if (N <= 0 && D <= 0)
		N = -N, D = -D;
	N /= g;
	D /= g;

	return N + 1000000 * D;
}

LL Hash(pt &A, pt &B) {
	LL Hslope = fr(A.y-B.y, A.x-B.x);
	LL Hdist = floor(Area(A, B, pt(0,0)) / Dist(A, B) * 1e8);

	return (211*Hslope) ^ (269*Hdist);
}

void smallN(int N, int K, vector<pt>& P, int& ANS) {
	map<LL, LL> f;
	for (int i = 0; i < N; ++i)
		for (int j = i+1; j < N; ++j)
			++f[Hash(P[i], P[j])];

	LL c = 0;
	for (auto& [a, b] : f)
		c = max(c, b);

	ANS = max(ANS, int((1 + sqrt(1 + 8*c)) / 2));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	int K;
	cin >> N >> K;

	int W = 0;
	int H = 0;
	map<int, int> X;
	map<int, int> Y;
	vector<pt> P(N);
	for (pt &i : P) {
		cin >> i.x >> i.y;
		W = max(W, (int) i.x);
		H = max(H, (int) i.y);
		X[i.x]++;
		Y[i.y]++;
	}

	int ANS = 0;
	for (auto& [a, b] : X) ANS = max(ANS, b);
	for (auto& [a, b] : Y) ANS = max(ANS, b);

	if (N < 8000) {
		smallN(N, K, P, ANS);
		cout << (ANS >= K ? ANS : 0) << "\n";
		return 0;
	}

	++W, ++H;

	vector<vector<bool>> m(W, vector<bool> (H));
	for (pt& i : P)
		m[i.x][i.y] = 1;

	int A = W / K;
	int B = H / K;

	vector<pt> s;
	for (int i = 1; i <= A; ++i)
		for (int j = 1; j <= B; ++j)
			if (__gcd(i, j) == 1) {
				s.push_back(pt(i,  j));
				s.push_back(pt(i, -j));
			}

	int S = s.size();
	vector<vector<vector<int>>> dp;
	dp.assign(W, vector<vector<int>> (H, vector<int> (S)));

	for (int i = W-1; i >= 0; --i)
		for (int j = H-1; j >= 0; --j)
			for (int k = 0; k < S; ++k) {
				if (i+s[k].x < W && j+s[k].y < H && i+s[k].x >= 0 && j+s[k].y >= 0)
					dp[i][j][k] = dp[i + s[k].x][j + s[k].y][k];
				dp[i][j][k] += m[i][j];
				ANS = max(ANS, dp[i][j][k]);
			}

	cout << (ANS < K ? 0 : ANS) << "\n";
}
