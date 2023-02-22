#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    for (int i = 0; i < n/2; ++i) {
        cout << "1 0 1\n";
    }
    cout << (n+1)/2 << " 0 1\n";
    for (int i = 0; i < (n+1)/2; ++i) {
        cout << "1 1 0\n";
    }
    cout << (n+1)/2 << " 0 1\n";
}
