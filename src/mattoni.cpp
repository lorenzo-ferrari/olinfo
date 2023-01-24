#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int m; cin >> m;
    vector<int> h(n+1);
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        ++h[a-1];
        --h[b];
    }
    for (int i = 1; i < n; ++i) {
        h[i] += h[i-1];
    }
    h.pop_back();
    nth_element(begin(h), begin(h) + n/2, end(h));
    cout << h[n / 2] << "\n";
}
