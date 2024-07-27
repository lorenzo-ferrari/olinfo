#include <bits/stdc++.h>
using namespace std;
using LL = long long;

vector<string> sol(LL K) {
	assert(K >= 1);
	if (K == 1) {
		return {"."};
	} else {
		auto grid = sol(K / 2);
		assert(!grid.empty());
		int l = grid[0].size();
		if (K % 2 == 0) {
			for (int i = 0; i < (int)grid.size(); ++i) {
				grid[i] = (i ? "#" : ".") + grid[i];
			}
			grid.insert(begin(grid), ".." + string(l - 1, '#'));
		} else {
			for (int i = 0; i < (int)grid.size(); ++i) {
				grid[i] = (i ? ".#" : "..") + grid[i];
			}
			grid.insert(begin(grid), ".." + string(l, '#'));
			grid.push_back("." + string(l, '#') + ".");
			grid.push_back(string(l + 2, '.') + ".");
		}
		return grid;
	}
}

vector<vector<char>> solve(LL K) {
	vector<vector<char>> ans;
	for (const auto& line : sol(K)) {
		ans.push_back(vector<char>(begin(line), end(line)));
	}
	return ans;
};
