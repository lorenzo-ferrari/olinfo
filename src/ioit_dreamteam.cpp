#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

int readint() {
    int n;
    cin >> n;
    return n;
}

void print(int n) {
    cout << n << "\n";
}

int main() {
    int n = readint();
    int k = readint();
    vector<int> f(n), p(n), q(n);
    for (int i = 0; i < n; ++i) {
        cin >> f[i] >> p[i] >> q[i];
    }
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        if (i < f[i]) {
            v.push_back(max(p[i], p[f[i]]));
            v.push_back(q[i] + q[f[i]] - v.back());
        }
    }
    nth_element(v.begin(), v.begin() + k, v.end(), greater<int>());
    long long ans = 0;
    for (int i = 0; i < k; ++i) {
        ans += v[i];
    }
    print(ans);
}
