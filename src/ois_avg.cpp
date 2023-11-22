#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    LL k; cin >> k;
    LL t = n * k;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    LL s = accumulate(begin(p), end(p), 0LL);
    if (s == t) {
        cout << "0\n";
    } else if (s < t) {
        cout << "1\n";
    } else {
        sort(begin(p), end(p));
        int cnt = 0;
        for (int i = n-1; s > t && i >= 0; --i) {
            s -= p[i] - 1;
            ++cnt;
        }
        cout << cnt << "\n";
    }
}
