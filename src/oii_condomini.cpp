// @check-accepted: esempi quartica cubica quadratica NlogN lineare full
/*

Consider the following case:

20
9 4 1 19 11 19 9 10 9 7 7 4 5 14 13 3 6 10 6 13

The correct answer is 7 (subarray [1 19 11 19 9 10 9 7 7 4]).

Previous solutions on the above input case gave 6.

 */
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

static constexpr long long MAXH = 1e9 + 5;

// for i = 0..n-1, find the index of the Next Greater Element
vector<int> nge(int n, vector<int> v) {
    vector<int> ans(n);
    stack<int> st;
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && v[st.top()] <= v[i]) st.pop();
        if (st.empty())
            ans[i] = -1;
        else
            ans[i] = st.top();
        st.push(i);
    }
    return ans;
}
// for i = 0..n-1, find the index of the Previous Greater Element
vector<int> pge(int n, vector<int> v) {
    reverse(begin(v), end(v));
    auto ans = nge(n, v);
    reverse(begin(ans), end(ans));
    for (int& i : ans)
        if (i != -1) i = n - 1 - i;
    return ans;
}

int sbugiarda(int n, vector<int> h) {
    auto nxt = nge(n, h);
    auto prv = pge(n, h);
    // quant'è alto l'albero di i verso sinistra (vl) e destra (vr)
    vector<int> vl(n, 1), vr(n, 1);
    for (int i = 0; i < n; ++i)
        if (nxt[i] != -1) vl[nxt[i]] = max(vl[nxt[i]], vl[i] + 1);
    for (int i = n - 1; i >= 0; --i)
        if (prv[i] != -1) vr[prv[i]] = max(vr[prv[i]], vr[i] + 1);
    auto pmax = vl, smax = vr;
    for (int i = 1; i < n; ++i) pmax[i] = max(pmax[i], pmax[i - 1]);
    for (int i = n - 2; i >= 0; --i) smax[i] = max(smax[i], smax[i + 1]);

    int ans = pmax[n - 1];
    for (int i = 0; i + 1 < n; ++i) ans = max(ans, pmax[i] + smax[i + 1]);
    return ans;
}
