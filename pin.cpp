#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    int64_t n, k, s = 0;
    cin >> n >> k;
    uint64_t p = pow(10, k - 1);
    unordered_map <uint64_t, uint64_t> f;
    for (uint64_t i = 0, c; i < k; i++) {
        cin >> c;
        s = 10 * s + c;
    }
    f[s]++;
    for (uint64_t i = k, c; i < n; i++) {
        cin >> c;
        s = 10 * (s % p) + c;
        f[s]++;
    }

    int mx = 0;
    for (auto x : f) {
        if (x.second > mx) {
            mx = x.second;
            s = x.first;
        }
    }

    while (k--) {
        cout << s / p << " ";
        s %= p;
        p /= 10;
    }
}