#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second
#define int long long
using pii=pair<int, int>;

struct nd {
    int min = 0;
    int lazy = 0;
    nd() {}
    nd(int _min, int _lazy) :
        min(_min), lazy(_lazy) {}
};
nd join(nd a, nd b) {
    return nd(min(a.min, b.min), 0);
}

const int H = 1 << 17;

nd t[2 * H];

void prop(int i) {
    if (t[i].lazy == 0) return;
    t[i].min += t[i].lazy;
    if (i < H) {
        t[i << 1    ].lazy += t[i].lazy;
        t[i << 1 | 1].lazy += t[i].lazy;
    }
    t[i].lazy = 0;
}

nd query(int i, int a, int b, int p) {
    prop(i);
    if (i == p + H)
        return t[i];
    if (a <= p && p < (a + b) / 2) return query(i << 1    , a, (a + b) / 2, p);
    if ((a + b) / 2 <= p && p < b) return query(i << 1 | 1, (a + b) / 2, b, p);
    return nd();
}

void update(int i, int a, int b, int l, int r) {
    prop(i);
    if (r <= a || b <= l) return;
    if (l <= a && b <= r) {
        t[i].lazy += 1;
        prop(i);
    } else {
        update(i << 1    , a, (a + b) / 2, l, r);
        update(i << 1 | 1, (a + b) / 2, b, l, r);
        t[i] = join(t[i << 1], t[i << 1 | 1]);
    }
}

int lower_bound(int i, int a, int b, int l, int r, int x) {
    prop(i);
    if (r <= a || b <= l || t[i].min > x) return -1;
    if (i >= H) return i - H;
    int o = lower_bound(i << 1, a, (a + b) / 2, l, r, x);
    return o != -1 ? o : lower_bound(i << 1 | 1, (a + b) / 2, b, l, r, x);
}


int32_t main() {
ios_base::sync_with_stdio(false);
cin.tie(NULL);
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    vector<pii> v(n);
    for (auto& [h, k] : v)
        cin >> h >> k;
    sort(v.begin(), v.end());

    for (auto& [h, k] : v) {
        int a = query(1, 0, H, h - k).min;
        int b = lower_bound(1, 0, H, 0, h, a);
        int c = lower_bound(1, 0, H, 0, h, a - 1);
        if (c == -1) {
            update(1, 0, H, b, b + k);
        } else {
            update(1, 0, H, c, h);
            update(1, 0, H, b, b + k - (h - c));
        }
    }

    for (int i = 0; i < 2 * H; ++i)
        prop(i);

    int ans = 0;
    for (int i = 0; i < H; ++i)
        ans += t[i + H].min * (t[i + H].min - 1) / 2;
    cout << ans << "\n";
}
