#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct pt {
    LL x, y;
    pt() {}
    pt(LL _x, LL _y) : x(_x), y(_y) {}
};

LL operator^(const pt& a, const pt& b) { return a.x*b.y - a.y*b.x; }
pt operator+(const pt& a, const pt& b) { return pt(a.x + b.x, a.y + b.y); }
pt operator-(const pt& a, const pt& b) { return pt(a.x - b.x, a.y - b.y); }
bool operator<(const pt& a, const pt& b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
ostream& operator<<(ostream& os, const pt& a) { return os << '(' << a.x << ',' << a.y << ')'; }

bool al (pt a, pt b, pt c) { return ((a-c)^(b-c)) == 0; }
bool cw (pt a, pt b, pt c) { return ((a-c)^(b-c)) < 0; }
bool ccw(pt a, pt b, pt c) { return ((a-c)^(b-c)) > 0; }

vector<pt> upper_hull(int n, vector<pt> P) {
    vector<pt> hull;
    for (int i = 0; i < n; ++i) {
        while ((int)hull.size() > 1 && !cw(hull[hull.size()-2], hull.back(), P[i])) {
            hull.pop_back();
        }
        hull.push_back(P[i]);
    }
    return hull;
}

vector<pt> lower_hull(int n, vector<pt> P) {
    for (pt& p : P) p.y *= -1;
    auto hull = upper_hull(n, P);
    for (pt& p : hull) p.y *= -1;
    return hull;
}

vector<pt> convex_hull(int n, vector<pt> P) {
    sort(begin(P), end(P));
    vector<pt> l, u;
    l.push_back(P[0]);
    u.push_back(P[0]);
    for (int i = 1; i < n-1; ++i) {
        if (ccw(P[0], P.back(), P[i])) {
            u.push_back(P[i]);
        } else {
            l.push_back(P[i]);
        }
    }
    l.push_back(P.back());
    u.push_back(P.back());
    auto lh = lower_hull(l.size(), l);
    auto uh = upper_hull(u.size(), u);
    for (int i = 1; i < (int)uh.size() - 1; ++i) {
        lh.push_back(uh[i]);
    }
    return lh;
}

vector<int> trovacerchi(int n, vector<int> x, vector<int> y) {
    vector<pt> P(n);
    for (int i = 0; i < n; ++i) {
        P[i] = {x[i], y[i]};
    }
    P.push_back({0, 0});
    auto c = convex_hull(n+1, P);
    set<pt> s;
    for (pt p : c) {
        s.insert(p);
    }
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (s.count({x[i], y[i]})) {
            ans.push_back(i);
        }
    }
    return ans;
}
