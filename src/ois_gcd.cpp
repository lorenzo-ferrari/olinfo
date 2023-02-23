#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int d; cin >> d;
    LL p = 1;
    for (int i = 1; i < n; ++i) {
        p *= 10;
    }
    LL a = ((p + d - 1) / d) * d;
    LL b = a + d;
    if ((int)to_string(a).size() == n && (int)to_string(b).size() == n) {
        cout << a << " " << b << "\n";
    } else {
        cout << "0 0\n";
    }
}
