#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
using namespace std;
#define F first
#define S second

vector <pair<char, int>> conv(string a) {
    vector <pair<char, int>> ans;
    for (char c : a) {
        if (ans.empty() || ans.back().F != c)
            ans.push_back({c, 1});
        else
            ans.back().S++;
    }

    return ans;
}

int main() {
    string a, b, c;
    cin >> a >> b >> c;
    auto va = conv(a);
    auto vb = conv(b);
    auto vc = conv(c);

    if (!(va.size() == vb.size() && vb.size() == vc.size())) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    int n = va.size();
    bool one = true;
    string ans;
    for (int i = 0; i < n; i++) {
        if (!(va[i].F == vb[i].F && vb[i].F == vc[i].F)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }

        ans += string(va[i].S + vb[i].S + vc[i].S - min(va[i].S, min(vb[i].S, vc[i].S)) - max(va[i].S, max(vb[i].S, vc[i].S)), va[i].F);
    }

    cout << ans << "\n";
}