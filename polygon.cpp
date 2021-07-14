#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
// GEOMETRY TEMPLATE
/////////////////////////////////////////////////////////////////////////////////////////

typedef long long LL;

struct pt {
	LL x, y;
	pt () {}
	pt (LL X, LL Y) : x(X), y(Y) {}
};

istream& operator >>(istream& in, pt& A) { return in >> A.x >> A.y; }
ostream& operator <<(ostream& out, pt A) { return out << '(' << A.x << "," << A.y << ')'; }
pt operator +(pt A, pt B) { return pt(A.x + B.x, A.y + B.y); }
pt operator -(pt A, pt B) { return pt(A.x - B.x, A.y - B.y); }
pt operator *(LL D, pt A) { return pt(D * A.x, D * A.y); }
LL operator ^(pt A, pt B) { return A.x*B.y - A.y*B.x; }
bool operator ==(pt A, pt B) { return A.x == B.x && A.y == B.y; }

/////////////////////////////////////////////////////////////////////////////////////////

int sgn(LL x) { return (0 < x) - (x < 0); }

int quad(pt A) {
	if (A.x >= 0 && A.y >= 0) return 1;
	if (A.x <  0 && A.y >= 0) return 2;
	if (A.x <  0 && A.y <  0) return 3;
	return 4;
}

bool onSegment(pt C, pt A, pt B) {
	return ((A-C)^(B-C)) == 0 && quad(A-C) != quad(B-C);
}

bool intersect(pt A, pt B, pt C, pt D) {
	return
	sgn((A-C)^(B-C)) != 0 && sgn((A-D)^(B-D)) != 0 &&
	sgn((C-A)^(D-A)) != 0 && sgn((C-B)^(D-B)) != 0 &&
	sgn((A-C)^(B-C)) == -sgn((A-D)^(B-D)) &&
	sgn((C-A)^(D-A)) == -sgn((C-B)^(D-B));
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	vector<pt> P(N);
	for (pt &i : P) {
		cin >> i;
		i = 2 * i;
	}

	function<bool(pt)> inner = [&](pt A) {
		pt X(1000, A.y + 1);
		int cnt = 0;
		for (int i = 0; i < N; i++) {
			cnt += intersect(A, X, P[i], P[(i + 1) % N]);
			if (onSegment(A, P[i], P[(i + 1) % N]))
				return false;
		}
		return cnt % 2 == 1;
	};

	const int G = 205;
	int ans = 0;
	for (int i = 1; i < G; i += 2) {
		for (int j = 1; j < G; j += 2) {
			if (inner(pt(i, j))) {
				bool x = true;
				pt A(i-1, j-1), B(i+1, j-1), C(i+1, j+1), D(i-1, j+1);
				for (int k = 0; k < N; k++) {
					if (intersect(A, C, P[k], P[(k + 1) % N]) || intersect(B, D, P[k], P[(k + 1) % N])) {
						x = false;
						break;
					}
				}
				ans += x;
			}
		}
	}

	cout << ans << "\n";
}
