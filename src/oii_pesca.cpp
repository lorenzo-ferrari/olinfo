#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    array<LL, 2> o;
    cin >> o[0] >> o[1];
    vector<array<LL, 2>> P(n);
    for (int i = 0; i < n; ++i) {
        cin >> P[i][0] >> P[i][1];
    }
    auto sgn = [&](LL x) { return (x > 0) - (x < 0); };
    auto input_dirs = [&]() -> vector<array<LL, 2>> {
        vector<array<LL, 2>> ans;
        array<LL, 2> cur = o;
        LL dir = 0;
        do {
            LL d; cin >> d;
            if (sgn(d) == sgn(dir)) dir += d;
            else {
                if (!ans.empty() && ans.back()[0] == cur[0]) {
                    ans.pop_back();
                }
                ans.push_back(cur);
                if (sgn(dir) == 1) {
                    cur[1] += dir;
                } else if (sgn(dir) == -1) {
                    cur[0] -= dir;
                }
                dir = d;
            }
        } while (dir);
        if (!ans.empty() && ans.back()[0] == cur[0]) {
            ans.pop_back();
        }
        ans.push_back(cur);
        return ans;
    };
    auto below = [](const vector<array<LL, 2>>& r, array<LL, 2> pt) -> bool {
        if (!(r[0][0] <= pt[0] && pt <= r.back())) return false;
        auto it = lower_bound(begin(r), end(r), pt);
        return (*it)[0] == pt[0] || (*prev(it))[1] >= pt[1];
    };

    auto a = input_dirs();
    auto b = input_dirs();

#ifdef LOCAL
    for (auto [x, y] : a) { cerr << "A: " << x << " " << y << "\n"; }
    for (auto [x, y] : b) { cerr << "B: " << x << " " << y << "\n"; }
#endif

    for (auto p : P) {
        if (!below(a, p) && below(b, p)) {
            swap(a, b);
            break;
        }
    }

    for (auto& [x, y] : b) ++x, --y; --b[0][0];

    int ans = 0;
    for (auto p : P) {
        if (p[0] > a.back()[0]) continue;
        ans += below(a, p) && !below(b, p);
    }

    cout << ans << "\n";
}
