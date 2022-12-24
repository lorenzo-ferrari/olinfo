#include <bits/stdc++.h>
using namespace std;
using LL = long long;

set<LL> s;

void apri(LL p) {
    s.insert(p);
}

void chiudi(LL p) {
    s.erase(p);
}

LL chiedi(LL p) {
    auto it = s.lower_bound(p);
    LL ans = -1;
    if (it != end(s)) {
        ans = *it;
    }
    if (it != begin(s) && (ans == -1 || ans - p > p - *prev(it))) {
        ans = *prev(it);
    }
    return ans;
}

void inizia() {}

int main() {
    inizia();
    int q; cin >> q;
    while (q--) {
        char c; cin >> c;
        LL p; cin >> p;
        if (c == 'q') {
            cout << chiedi(p) << "\n";
        } else if (c == 'a') {
            apri(p);
        } else {
            chiudi(p);
        }
    }
}

