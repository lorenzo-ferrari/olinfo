#include "bits/stdc++.h"
using namespace std;
using LL = long long;

template<size_t K>
bool conn(vector<array<int, K>> c) {
    if (c.empty()) return true;
    set<array<int, K>> s;
    for (auto p : c) {
        s.insert(p);
    }
    set<array<int, K>> vis;
    auto dfs = [&](auto&& self, array<int, K> p) -> void {
        if (!s.count(p) || vis.count(p)) {
            return;
        }
        vis.insert(p);
        for (int i = 0; i < K; ++i) {
            p[i] += 1;
            self(self, p);
            p[i] -= 2;
            self(self, p);
            p[i] += 1;
        }
    };
    dfs(dfs, *begin(s));
    return vis.size() == s.size();
}

template<size_t K>
bool works(vector<array<int, K>> c) {
    static_assert(K >= 1);
    if (!conn<K>(c)) {
        return false;
    }
    if constexpr (K == 1) {
        return true;
    } else {
        array<map<int, vector<array<int, K-1>>>, K> sections;
        for (auto p : c) {
            for (int i = 0; i < K; ++i) {
                array<int, K-1> pp;
                for (int j = 0; j < K; ++j) {
                    if (j == i) continue;
                    pp[j - (j > i)] = p[j];
                }
                sections[i][p[i]].push_back(pp);
            }
        }
        for (int i = 0; i < K; ++i) {
            for (auto [_, cc] : sections[i]) {
                if (!works<K-1>(cc)) {
                    return false;
                }
            }
        }
        return true;
    }
}

int main() {
    int n; cin >> n;
    vector<array<int, 3>> c(n);
    for (int i = 0; i < n; ++i) cin >> c[i][0];
    for (int i = 0; i < n; ++i) cin >> c[i][1];
    for (int i = 0; i < n; ++i) cin >> c[i][2];
    if (works<3>(c)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
