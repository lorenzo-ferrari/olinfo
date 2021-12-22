#include <iostream>

int main() {
#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	scanf("%d", &n);

	int l = -1e9, r = 1e9;
	for (int i = 0, m, K = 0; i < n; ++i) {
		scanf("%d", &m);
		if (i & 1) {
			l = std::max(l, K - m);
			K -= m << 1;
		} else {
			r = std::min(r, K + m);
			K += m << 1;
		}
	}

	printf("%d\n", std::max(0, r - l + 1));
}
