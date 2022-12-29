#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr int N_NODES = 2e7;

struct Node {
    int l = -1, r = -1;
    LL sum = 0, lz = 0;
    Node() {}
};

static int g = 0;
static Node nodes[N_NODES];

static int new_node() {
    assert(g < N_NODES && "Too few nodes!");
    return g++;
}

static int copy_node(const Node& n) {
    assert(g < N_NODES && "Too few nodes!");
    int i = g++;
    nodes[i].l = n.l;
    nodes[i].r = n.r;
    nodes[i].sum = n.sum;
    nodes[i].lz = n.lz;
    return i;
}

static void apply(Node& n, int a, int b, LL x) {
    n.sum += x * (b - a);
    n.lz += x;
}

static void prop(Node& n, int a, int b) {
    if (n.lz == 0) return;
    if (n.l != -1) { n.l = copy_node(nodes[n.l]); apply(nodes[n.l], a, (a+b)/2, n.lz); }
    if (n.r != -1) { n.r = copy_node(nodes[n.r]); apply(nodes[n.r], (a+b)/2, b, n.lz); }
    n.lz = 0;
}

static int build(int a, int b, const vector<int>& v) {
    int i = new_node();
    if (b - a == 1) {
        nodes[i].sum = v[a];
    } else {
        nodes[i].l = build(a, (a+b)/2, v);
        nodes[i].r = build((a+b)/2, b, v);
        nodes[i].sum = nodes[nodes[i].l].sum + nodes[nodes[i].r].sum;
    }
    return i;
}

static LL query(Node& n, int l, int r, int a, int b) {
    prop(n, a, b);
    if (r <= a || b <= l) return 0;
    if (l <= a && b <= r) return n.sum;
    return query(nodes[n.l], l, r, a, (a+b)/2) +
           query(nodes[n.r], l, r, (a+b)/2, b); 
}

static int add(int prv, int l, int r, int x, int a, int b) {
    prop(nodes[prv], a, b);
    int n = copy_node(nodes[prv]);
    if (r <= a || b <= l) return prv;
    if (l <= a && b <= r) {
        apply(nodes[n], a, b, x);
    } else {
        nodes[n].l = add(nodes[prv].l, l, r, x, a, (a+b)/2);
        nodes[n].r = add(nodes[prv].r, l, r, x, (a+b)/2, b);
        nodes[n].sum = nodes[nodes[n].l].sum + nodes[nodes[n].r].sum;
    }
    return n;
}

static int reset(int from, int to, int l, int r, int a, int b) {
    prop(nodes[from], a, b);
    prop(nodes[to], a, b);
    if (r <= a || b <= l) return copy_node(nodes[from]);
    if (l <= a && b <= r) return copy_node(nodes[to]);
    else {
        int n = new_node();
        nodes[n].l = reset(nodes[from].l, nodes[to].l, l, r, a, (a+b)/2);
        nodes[n].r = reset(nodes[from].r, nodes[to].r, l, r, (a+b)/2, b);
        nodes[n].sum = nodes[nodes[n].l].sum + nodes[nodes[n].r].sum;
        return n;
    }
}

struct Segtree {
    int n;
    vector<int> roots;
    Segtree(int _n, vector<int> a) {
        for (n = 1; n < _n; n<<= 1);
        a.resize(n);
        roots.push_back(build(0, n, a));
    }
    void add(int l, int r, int x) {
        roots.push_back(::add(roots.back(), l, r, x, 0, n));
    }
    void reset(int l, int r, int v) {
        roots.push_back(::reset(roots.back(), roots[v], l, r, 0, n));
    }
    LL get(int l, int r) {
        return query(nodes[roots.back()], l, r, 0, n);
    }
};

Segtree* st;

void incrementa(int l, int r, int x) {
    st->add(l, r, x);
}

void resetta(int l, int r, int v) {
    st->reset(l, r, v);
}

LL somma(int l, int r) {
    return st->get(l, r);
}

void inizia(int n, vector<int> a) {
    st = new Segtree(n, a);
}
