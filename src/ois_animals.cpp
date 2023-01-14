#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    stack<int> st;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        while (!st.empty() && st.top() < x) {
            st.pop();
        }
        st.push(x);
    }
    cout << st.size() << "\n";
}
