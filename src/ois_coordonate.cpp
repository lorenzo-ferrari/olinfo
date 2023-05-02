#include "bits/stdc++.h"
using namespace std;
using LL = long long;

set<int> cur;
map<int, int> frq;

void answer() {
    for (int i : cur) {
        cout << i << " ";
    }
    cout << "\n";
    exit(0);
}

static void erase(int x) {
    if (--frq[x] == 0) frq.erase(x);
}

void solve();

void rec(int pos) {
    if (pos < 0) return;

    bool works = true;
    for (int i : cur) {
        if (!works) break;
        if (frq.count(abs(i - pos))) {
            erase(abs(i - pos));
        } else {
            works = false;
            for (int j : cur) {
                if (j == i) break;
                ++frq[abs(j - pos)];
            }
        }
    }
    if (works) {
        cur.insert(pos);
        solve();
        cur.erase(pos);
        for (int i : cur) {
            ++frq[abs(i - pos)];
        }
    }
}

void solve() {
    if (frq.empty()) answer();

    int pos = prev(end(frq))->first;
    rec(pos);
    rec(*prev(end(cur)) - pos);
}

int main() {
    int n; cin >> n;
    for (int i = 0, x; i < n*(n-1)/2; ++i) {
        cin >> x;
        ++frq[x];
    }

    cur.insert(0);
    solve();
}
