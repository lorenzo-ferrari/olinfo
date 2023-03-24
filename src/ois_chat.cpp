#include "bits/stdc++.h"
using namespace std;

int main() {
    int n; cin >> n;
    vector<string> a(n);
    for (auto& s : a) {
        cin >> s;
    }
    reverse(begin(a), end(a));
    set<string> s;
    for (auto x : a) {
        if (!s.count(x)) {
            cout << x << "\n";
        }
        s.insert(x);
    }
}
