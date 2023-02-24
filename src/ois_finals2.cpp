#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int p; cin >> p;
    vector<int> s(n);
    for (int i = 0, a, b, c; i < n; ++i) {
        cin >> a >> b >> c;
        s[i] = a + b + c;
    }
    int m2 = p*100 + *max_element(begin(s)+1, end(s));
    int ans = m2 - s[0] + 1;
    cout << max(0, ans) << "\n";
}
