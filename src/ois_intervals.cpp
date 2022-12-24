#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<int, 2>> a(n);
    for (auto& [x, y] : a) {
        cin >> x >> y;
    }
    sort(begin(a), end(a), [&](array<int, 2> i, array<int, 2> j){return i[1] < j[1];});
    multiset<int> s;
    for (auto& [x, y] : a) {
        if (s.find(x) == s.end()) {
            s.insert(y);
        } else {
            s.erase(s.find(x));
            s.insert(y);
        }
    }
    cout << s.size() << "\n";
}
