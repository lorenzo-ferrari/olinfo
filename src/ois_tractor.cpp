#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

static constexpr int N = 1e5;
static constexpr double TL = 9;

enum dir_t { dx, sx };

clock_t t;

class Solution {
    int n, k, kk, best;
    bitset<N> vis{};
    vector<int> ans, o;

    inline void explore(int cur, dir_t dir, int sum) {
        vis[cur] = true;
        o.push_back(cur);
        search(cur, dir, sum);
        o.pop_back();
        vis[cur] = false;
    }

    inline void explore_small(int cur, dir_t dir, int sum) {
        vis[cur] = true;
        o.push_back(cur);
        search_small(cur, dir, sum);
        o.pop_back();
        vis[cur] = false;
    }

    void search(int cur, dir_t dir, int sum) {
        if (clock() - t > TL * CLOCKS_PER_SEC) return;
        if (sum + (n - (int)o.size())*k >= best) return;
        if ((int)o.size() == n) {
            best = sum;
            ans = o;
            return;
        }

        for (int d = k; d < max(10, 3*k); ++d) {
            for (int j = 0; j < 2; ++j) {
                if (j == dir && cur + d < n && !vis[cur + d]) {
                    explore(cur + d, sx, sum + d);
                }
                if (j != dir && cur - d >= 0 && !vis[cur - d]) {
                    explore(cur - d, dx, sum + d);
                }
            }
            if (kk*k <= cur && cur <= n - kk*k) {
                break;
            }
        }
    }

    void search_small(int cur, dir_t dir, int sum) {
        if (clock() - t > TL * CLOCKS_PER_SEC) return;
        if (sum + (n - (int)o.size())*k >= best) return;
        if ((int)o.size() == n) {
            best = sum;
            ans = o;
            return;
        }

        for (int d = k; d < 2*k; ++d) {
            for (int j = 0; j < 2; ++j) {
                if (j == dir && cur + d < n && !vis[cur + d]) {
                    explore_small(cur + d, sx, sum + d);
                }
                if (j != dir && cur - d >= 0 && !vis[cur - d]) {
                    explore_small(cur - d, dx, sum + d);
                }
            }
            if (4*k <= cur && cur <= n - 4*k) {
                break;
            }
        }
    }

public:
    Solution(int n, int k) : n(n), k(k), kk(k <= 5 ? 4 : 6), best(1e9) {
        if (n <= 30) {
            explore_small(0, dx, 0);
        } else {
            explore(0, dx, 0);
        }
    }
    pair<int, vector<int>> get() const { return {best, ans}; }
};

void print(int cost, vector<int> tour) {
    cout << cost << "\n";
    for (int i : tour) {
        cout << i << " ";
    }
    cout << "\n";
}

int main() {
    t = clock();
    int n; cin >> n;
    int k; cin >> k;
    
    if (n >= 30*k) {
        int cnks = (n - 30*k) / k;
        n -= cnks * k;
        Solution s(n, k);
        auto [cost, tour] = s.get();
        if ((int)tour.size() != n) {
            exit(1);
        }
        vector<int> ans;
        int prv = -1;
        for (int i : tour) {
            if (i < n/2) {
                ans.push_back(i);
            } else if (n/2 <= i && i < n/2+k) {
                for (int j = 0; j <= cnks; ++j) {
                    if (prv < i) ans.push_back(i + j*k);
                    else ans.push_back(i + (cnks - j)*k);
                }
            } else {
                ans.push_back(i + cnks*k);
            }
            prv = i;
        }
        print(cost + cnks*k*k, ans);
    } else {
        Solution s(n, k);
        auto [cost, tour] = s.get();
        if ((int)tour.size() != n) {
            exit(1);
        }
        print(cost, tour);
    }
}
