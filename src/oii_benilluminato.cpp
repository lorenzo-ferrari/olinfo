// https://training.olinfo.it/task/oii_benilluminato
#include <set>
#include <array>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int illumina(int N, int M, vector<int> H, vector<int> A, vector<int> B, vector<int> L) {
	vector<set<array<int, 2>>> adj(N);

	int ans = 0;
	vector<bool> standing(N, true);
	
	queue<int> Q;
	auto delete_edge = [&](int edge) -> void {
		adj[A[edge]].erase({B[edge], edge});
		adj[B[edge]].erase({A[edge], edge});
	};
	auto cut_down = [&](int tree, int edge) -> void {
		delete_edge(edge);
		if (standing[tree]) {
			++ans;
			Q.push(tree);
			standing[tree] = false;
		}
	};
	// se un sentiero può contenere entrambi gli alberi o solo uno dei due, tanto meglio
	for (int i = 0; i < M; ++i) {
		if (H[A[i]] < H[B[i]])
			swap(A[i], B[i]);
		if (L[i] < H[B[i]]) {
			continue;
		} else if (H[B[i]] <= L[i] && L[i] < H[A[i]]) {
			cut_down(B[i], i);
		} else if (H[A[i]] <= L[i] && L[i] < H[A[i]] + H[B[i]]) {
			adj[A[i]].insert({B[i], i});
			adj[B[i]].insert({A[i], i});
		} else {
			cut_down(A[i], i);
			cut_down(B[i], i);
		}
	}

	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		while (!adj[u].empty()) {
			auto [v, i] = *begin(adj[u]);
			cut_down(v, i);
		}
	}

	for (int i = 0; i < N; ++i)
		if (standing[i] && (int)adj[i].size() == 1)
			Q.push(i);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		if (adj[u].empty())
			continue;
		auto [v, i] = *begin(adj[u]);
		cut_down(u, i);
		if ((int)adj[v].size() == 1)
			Q.push(v);
	}

	for (int i = 0; i < N; ++i) {
		if (standing[i] && !adj[i].empty())
			++ans;
	}
	
	return ans;
}
