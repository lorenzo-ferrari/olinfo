#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int r; cin >> r;
        int t; cin >> t;
        int sum = 0;
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            sum += x;
        }
        if (sum > (r+t)*n) {
            cout << "Cheater\n";
        } else {
            cout << "Innocent\n";
        }
    }
}
