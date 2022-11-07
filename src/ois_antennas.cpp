#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct cool_map {
    LL d = 0;
    map<LL, LL> m;

    void insert(LL p, LL t) {
        p += d;
        {
            auto it = m.lower_bound(p);
            if (it != m.end() && it->second <= t) {
                return;
            }
        }
        m[p] = t;
        auto it = m.find(p);
        while (it != m.begin()) {
            if (prev(it)->second >= t) {
                m.erase(prev(it));
            } else {
                break;
            }
        }
    }
    void decrease(LL td) { d += td; }
    LL get_time(LL l) {
        auto it = m.lower_bound(l + d);
        return it == m.end() ? -1 : it->second;
    }
};

int main() {
    LL n; cin >> n;
    LL d; cin >> d;
    vector<LL> l(n), p(n), s(n), t(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> p[i] >> s[i] >> t[i];
    }
    auto next_time = [&](int i, LL tt) -> LL {
        if (tt < s[i]) return s[i];
        tt -= s[i];
        tt = t[i] * (1 + tt/t[i]);
        tt += s[i];
        return tt;
    };

    cool_map mp;
    mp.insert(p[0], s[0]);
    for (int i = 1; i < n-1; ++i) {
        mp.decrease(d);
        LL tt = mp.get_time(l[i]);
        if (tt == -1) continue;
        else mp.insert(p[i], next_time(i, tt));
    }
    mp.decrease(d);
    LL ans = mp.get_time(l.back());
    cout << (ans == -1 ? -1 : next_time(n-1, ans)) << "\n";
}
