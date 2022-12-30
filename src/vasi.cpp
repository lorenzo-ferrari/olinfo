#include <bits/stdc++.h>
using namespace std;

// http://xorshift.di.unimi.it/splitmix64.c
static uint64_t x = 0x040404;
static uint64_t next() {
	uint64_t z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return (z ^ (z >> 31)) & 0xffffffff;
}

struct treap {
    treap* l = nullptr;
    treap* r = nullptr;
    uint64_t y;
    int a, b, sz;
    treap(){}
    treap(int n) : y(next()), a(0), b(n), sz(n) {}
};

static constexpr size_t N = 1e7;
int g = 0;
static treap pool[N];
static treap* new_treap() { return pool + (g++); }
static treap* new_treap(int n) { pool[g] = treap(n); return pool + (g++); }
static treap* copy_treap(const treap& t) { pool[g] = t; return pool + (g++); }

static uint64_t rng_from(uint64_t lb) {
    return lb + 1 + next();
}

static uint64_t pr(treap* t) { return t ? t->y : 0; }
static int sz(treap* t) { return t ? t->sz : 0; }
static void calc(treap* t) { if (t) t->sz = t->b - t->a + sz(t->l) + sz(t->r); }

static void merge(treap* l, treap* r, treap*& t) {
    if (!l || !r) { t = l ? l : r; return; }
    if (l->y >= r->y) {
        t = l;
        merge(l->r, r, l->r);
    } else {
        t = r;
        merge(l, r->l, r->l);
    }
    calc(t);
}

static void split(treap* t, int i, treap*& l, treap*& r) {
    if (!t) l = r = nullptr;
    else if (i <= sz(t->l)) {
        r = t;
        split(t->l, i, l, t->l);
    } else if (i - sz(t->l) < t->b - t->a) {
        i -= sz(t->l);
        l = t;
        r = copy_treap(*t);
        r->y = rng_from(pr(r->r));
        l->r = r->l = nullptr;
        l->b = r->a = l->a + i;
    } else {
        i -= sz(t->l) + t->b - t->a;
        l = t;
        split(t->r, i, t->r, r);
    }
    calc(l);
    calc(r);
}

static int get(treap* t, int i) {
    if (!t) return -1;
    if (t->l && i < sz(t->l)) return get(t->l, i);
    i -= sz(t->l);
    if (i < t->b - t->a) return t->a + i;
    i -= t->b - t->a;
    return get(t->r, i);
}

treap* root = nullptr;

static int get(int i) {
    return get(root, i);
    treap *a, *b, *ti;
    split(root, i, a, b);
    split(b, 1, ti, b);
    int ans = ti->a;
    merge(a, ti, root);
    merge(root, b, root);
    return ans;
}

static void move(int i, int j) {
    treap *a, *b, *ti;
    split(root, i, a, b);
    split(b, 1, ti, b);
    merge(a, b, root);
    split(root, j, a, b);
    merge(a, ti, root);
    merge(root, b, root);
}

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    int m; cin >> m;

    root = new_treap(n);

    while (m--) {
        char op; cin >> op;
        if (op == 'c') {
            int i; cin >> i;
            cout << get(i) << " ";
        }
        if (op == 's') {
            int i; cin >> i;
            int j; cin >> j;
            move(i, j);
        }
    }
}

