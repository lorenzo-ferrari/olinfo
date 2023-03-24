#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int x; cin >> x;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    sort(begin(a), end(a));
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (i+1 < n && a[i] + a[i+1] <= x) {
            ++i;
        }
        ++cnt;
    }
    cout << cnt << "\n";
}
