#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    string s; cin >> s;
    int p = 0;
    for (char c : s) {
        p += (c == 'R') - (c == 'L');
    }
    cout << abs(p) << "\n";
}
