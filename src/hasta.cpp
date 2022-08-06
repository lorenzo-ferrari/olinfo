/*
 *  define sff[l] as query(l, n-1) - query(l+1, n-1)
 *  define ans[r][l] as sff[l] if v were {v[0], ..., v[r]}
 *      observation: ans[i] ~ ans[i+1], the only change is
 *          * where do I start adding r[v[i+1]]
 *          * where do I start deleting r[v[i+1]]
 *          -> the only change is "where is class v[i] active", at most 4 elements differ
 *  - compute ans[n] = sff
 *  - build a persistent segment tree
 *  - 4 updates to get ans[i] starting from ans[i+1]
 *  - answer range queries(l, n-1) on the "array" ans[r]
 *
 *  -> O(n lg n) time/space complexity
 */

#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

struct nd {
    int val = 0, a, b;
    nd * l = nullptr;
    nd * r = nullptr;
    nd* add(int, int) const;
    int get(int, int) const;
};

const int NODES = 1e7;
nd pool[NODES];
int nd_cnt = 0;

nd* new_nd(int a, int b) {
    nd* t = &pool[nd_cnt++];
    t->a = a, t->b = b;
    return t;
}
nd* new_nd(const nd* n) {
    nd* t = &pool[nd_cnt++];
    t->val = n->val, t->a = n->a, t->b = n->b;
    t->l = n->l, t->r = n->r;
    return t;
}

nd* nd::add(int i, int v) const {
    nd* n = new_nd(this);
    if (i < a || b <= i) return n;
    if (b-a == 1) {
        n->val += v;
    } else {
        int m = (a+b)/2;
        if (i < m) n->l = l->add(i, v);
        else n->r = r->add(i, v);
        n->val = n->l->val + n->r->val;
    }
    return n;
}

int nd::get(int ll, int rr) const {
    if (ll <= a && b <= rr) return val;
    if (rr <= a || b <= ll) return 0;
    return l->get(ll, rr) + r->get(ll, rr);
}

struct Segtree {
    nd* build(int a, int b) {
        nd* ans = new_nd(a, b);
        if (b-a != 1) {
            int m = (a+b)/2;
            ans->l = build(a, m);
            ans->r = build(m, b);
        }
        return ans;
    }

    int n;
    vector<nd*> roots;

    Segtree(int _n) {
        for (n = 1; n < _n; n <<= 1);
        roots.push_back(build(0, n));
    }

    void add(int i, int v) {
        roots.push_back(roots.back()->add(i, v));
    }

    int get(int t, int l, int r) {
        return roots[t]->get(l, r);
    }
};

Segtree* st;

vector<int> id;

void inizia(int n, int k, int v[], int r[]) {
    st = new Segtree(n);
    id.assign(n, -1);

    vector<vector<int>> ss(k);
    for (int i = 0; i < n; ++i) {
        ss[v[i]].push_back(i);
        // remove old values
        if (ss[v[i]].size() >= r[v[i]]+1) st->add(ss[v[i]][ss[v[i]].size() - r[v[i]] - 1], -r[v[i]]);
        if (ss[v[i]].size() >= r[v[i]]+2) st->add(ss[v[i]][ss[v[i]].size() - r[v[i]] - 2], +r[v[i]]);
        // add new values
        if (ss[v[i]].size() >= r[v[i]]  ) st->add(ss[v[i]][ss[v[i]].size() - r[v[i]]    ], +r[v[i]]);
        if (ss[v[i]].size() >= r[v[i]]+1) st->add(ss[v[i]][ss[v[i]].size() - r[v[i]] - 1], -r[v[i]]);
        id[i] = st->roots.size()-1;
    }
}

int istiga(int l, int r) {
    return st->get(id[r], l, st->n);
}

