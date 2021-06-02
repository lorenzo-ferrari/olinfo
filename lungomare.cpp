#include <iostream>
#pragma GCC optimize ("O3")

long long percorri (int N, long long L, long long D[], long long P[]) {
	D[N] = L;

	bool subtask2 = true;
	for (int i = 1; i < N - 1; i++) {
		if (D[i] - D[i + 1] != D[i - 1] - D[i] || P[i - 1] != P[i] || P[i] != P[i + 1]) {
		  subtask2 = false;
			break;
		}
	}

	if (subtask2) {
		return std::min(L, 2 * P[0] + D[0]);
	}

	long long l = 0, r = L, mid;
	while (l < r - 1) {
		mid = l + (r - l) / 2;
		bool possible = true;
		long long acc = D[0];
		for (int i = 0; i < N; i++) {
			if (P[i] < acc && acc + P[i] <= mid && P[i] + D[i + 1] - D[i] <= mid) {
				acc = P[i] + D[i + 1] - D[i];
			}
			else if (acc + D[i + 1] - D[i] <= mid) {
				acc += D[i + 1] - D[i];
			}
			else {
				possible = false;
				break;
			}
		}

		if (possible)
			r = mid;
		else
			l = mid;
	}

	return r;
}