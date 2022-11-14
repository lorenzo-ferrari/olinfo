#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define all(x) begin(x), end(x)

bool good(vector<int> v) {
    map<int, multiset<int>> mp;
    for (int i : v) {
        if (!mp[i].empty()) {
            auto it = prev(mp[i].end());
            if (*it != i) {
                mp[i + 2].insert(*it);
            }
            mp[i].erase(it);
        } else if (i < 0) {
            mp[i + 2].insert(-i);
        } else if (i > 0) {
            return false;
        }
    }
    for (auto& [a, b] : mp) {
        if (!b.empty()) {
            return false;
        }
    }
    return true;
}

int main() {
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    if (!good(v)) {
        cout << "0\n";
    } else {
        cout << count(all(v), 0) + count(all(v), 1) << "\n";
    }
}
