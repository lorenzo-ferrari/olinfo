#include <bitset>
#pragma GCC optimize ("O3")

const int N = 10001;
std::bitset <N> b[N];

int solve(int n, int m, int* Q, int** sp, int* A, int* B) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < Q[i]; j++)
			b[sp[i][j]][i] = 1;

	for (int i = 0, cnt; i < m; i++) {
		for (int j = i + 1; j < m; j++) {
			cnt = (b[i] & b[j]).count();
			if (cnt && cnt != b[i].count() && cnt != b[j].count()) {
				*A = i;
				*B = j;
				return 0;
			}
		}
	}

	return 1;
}