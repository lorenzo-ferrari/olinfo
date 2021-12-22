#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int64_t N = 1000;
const int64_t P = 5;
const int64_t MOD = 1e9 + 7;

int64_t pw[N];
int64_t v[N];
int64_t match[N];

int64_t hash_eso(int l, int r, int deg, bool tonde) {
	int64_t ans = 0;
	for (int i = l; i < r; i++) {
		if (match[i] == -1)
			ans ^= v[i];
		else {
			ans ^= hash_eso(i+1, match[i], deg + 1, v[i] == -1);
			i = match[i];
		}
	}
	ans = ans * (tonde ? pw[deg] : (pw[deg] << 1)) % MOD;
	return ans;
}

int32_t main() {
	pw[0] = 1;
	for (int i = 1; i < N; i++)
		pw[i] = P * pw[i - 1] % MOD;
#ifdef EVAL
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n, m;
	assert(2 == scanf("%d%d", &n, &m));
	unordered_map<int64_t, int64_t> dict;
	unordered_map<int64_t, vector<int64_t>> ans;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			assert(1 == scanf("%ld", v + j));
			if (v[j] > 0) {
				if (dict.find(v[j]) == dict.end())
					v[j] = dict[v[j]] = rand();
				else
					v[j] = dict[v[j]];
			}
		}
		stack<int> st;
		for (int j = 0; j < m; j++) {
			match[j] = -1;
			if (v[j] == -2 || v[j] == -4) {
				match[st.top()] = j;
				st.pop();
			}
			else if (v[j] == -1 || v[j] == -3)
				st.push(j);
		}
		ans[hash_eso(0, m, 1, 1)].push_back(i);
	}

	printf("%d\n", ans.size());
	for (auto &[id, x] : ans) {
		printf("%d ", x.size());
		for (int i = 0; i < x.size(); i++)
			printf("%d ", x[i] + 1);
		printf("\n");
	}
}
