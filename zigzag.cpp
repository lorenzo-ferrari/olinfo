#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");

    int n; cin >> n;
    vector<int> a(n), s(n), g(n);
    for (int& i : a) cin >> i;
    stack<pair<int,int>> st1; st1.push({ 2e9, n});
    stack<pair<int,int>> st2; st2.push({-2e9, n});
    for (int i = n - 1; i >= 0; --i) {
        while (st1.top().first <= a[i]) st1.pop();
        while (st2.top().first >= a[i]) st2.pop();
        g[i] = st1.top().second;
        s[i] = st2.top().second;
        st1.push({a[i], i});
        st2.push({a[i], i});
    }
    vector<int> dp1(n+1), dp2(n+1);
    for (int i = n - 1; i >= 0; --i) {
        dp1[i] = max(dp1[g[i]], dp2[g[i]] + 1);
        dp2[i] = max(dp2[s[i]], dp1[s[i]] + 1);
    }

    cout << max(*max_element(dp1.begin(), dp1.end()),
                *max_element(dp2.begin(), dp2.end())) << "\n";
}
