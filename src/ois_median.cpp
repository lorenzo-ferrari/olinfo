#include <bits/stdc++.h>
using namespace std;
using LL = long long;

// magic #define contributed by @collodel
template<typename Container,
    typename S = typename enable_if<!is_same<Container, string>::value, typename Container::value_type>::type>
ostream& operator<<(ostream& __out, Container &__ct) {
    __out << "{";
    bool first = true;
    for(auto&& __el : __ct) {
        if(!first) __out << ", ";
        __out << __el;
        first = false;
    }
    return __out << "}";
}
template<typename Tail>
void _dbg(Tail T) {
    cerr << T << endl;
}
template<typename Head, typename... Tail>
void _dbg(Head H, Tail... T) {
    cerr << H << ", ";
    _dbg(T...);
}
 
#ifdef DEBUG
#define dbg(...) do{cerr << "[" << #__VA_ARGS__ << "]: "; _dbg(__VA_ARGS__);}while(0)
#else
#define dbg(...) 42
#endif

mt19937 rng{42};

struct node {
    int x, y, val, sum, lazyx;
    node* l = nullptr;
    node* r = nullptr;
    node(int x = 0) : x(x), y(rng()), val(0), sum(0), lazyx(0) {}
    node(int x, int val) : x(x), y(rng()), val(val), sum(val), lazyx(0) {}

    friend void prop(node* n) {
        if (n && n->lazyx) {
            n->x += n->lazyx;
            if (n->l) n->l->lazyx += n->lazyx;
            if (n->r) n->r->lazyx += n->lazyx;
            n->lazyx = 0;
        }
    }
    friend int getsum(node* n) {
        return n ? n->sum : 0;
    }
    friend void calc(node* n) {
        if (n) {
            n->sum = n->val + getsum(n->l) + getsum(n->r);
        }
    }

    friend void split(node* t, int x, node*& l, node*& r) {
        prop(t);
        if (!t) l = r = nullptr;
        else if (t->x <= x) {
            split(t->r, x, t->r, r), l = t;
        } else {
            split(t->l, x, l, t->l), r = t;
        }
        calc(l);
        calc(r);
    }

    friend void merge(node* l, node* r, node*& t) {
        prop(l), prop(r);
        if (!l || !r) t = l ? l : r;
        else if (l->y > r->y) {
            merge(l->r, r, l->r), t = l;
        } else {
            merge(l, r->l, r->l), t = r;
        }
        calc(t);
    }

    friend bool count(node* t, int x) {
        prop(t);
        if (!t) return false;
        if (t->x == x) return true;
        return t->x > x ? count(t->l, x) : count(t->r, x);
    }
    friend void increase(node* t, int key, int val) {
        assert(t);
        prop(t);
        if (t->x == key) {
            t->val += val;
        } else if (t->x > key) {
            increase(t->l, key, val);
        } else {
            increase(t->r, key, val);
        }
        calc(t);
    }

    friend vector<array<int, 2>> get_all(node* n) {
        prop(n);
        if (!n) return {};
        vector<array<int, 2>> ans(1, {n->x, n->val});
        auto l = get_all(n->l);
        auto r = get_all(n->r);
        if (l.size() > ans.size()) swap(ans, l);
        for (auto x : l) ans.push_back(x);
        if (r.size() > ans.size()) swap(ans, r);
        for (auto x : r) ans.push_back(x);
        return ans;
    }
};

struct Treap {
    node* root = nullptr;
    int size;
    Treap(int key, int val) : root(new node(key, val)), size(1) {}

    void increase_keys(int x) {
        assert(root);
        root->lazyx += x;
    }

    int query(int r) {
        node* a;
        split(root, r, root, a);
        int ans = getsum(root);
        merge(root, a, root);
        return ans;
    }

    void insert(int x, int val) {
        ++size;
        node* t = new node(x, val);
        node* a;
        split(root, x, root, a);// [root][a]
        merge(root, t, root);   // [root][t]
        merge(root, a, root);   // [root][t][a]
    }
    void add(int key, int val) {
        if (count(root, key)) {
            increase(root, key, val);
        } else {
            insert(key, val);
        }
    }

    LL unite(Treap oth) {
        LL ans = 0;
        auto nodes = get_all(oth.root);
        for (auto [x, val] : nodes) {
            ans += (LL)val * query(-x);
        }
        for (auto [x, val] : nodes) {
            add(x, val);
        }
        return ans;
    }
};

LL ans = 0;
Treap dfs(int v, int p, const vector<vector<array<int, 2>>>& adj) {
    Treap ret(0, 1);
    for (auto [u, w] : adj[v]) {
        if (u == p) continue;
        Treap oth = dfs(u, v, adj);
        oth.increase_keys(w);
        if (oth.size > ret.size) {
            swap(oth, ret);
        }
        ans += ret.unite(oth);
    }
    return ret;
}

LL count_paths(vector<vector<array<int, 2>>> adj, int m) {
    // per quanti path la risposta e' almeno m?
    // cambia il peso di ogni arco in -1 (w<=m) o +1 (w>m)
    // per quanti path il peso e' non positivo?
    int n = adj.size();
    for (int i = 0; i < n; ++i) {
        for (auto& [u, w] : adj[i]) {
            if (w <= m) w = -1;
            else w = 1;
        }
    }
    ans = 0;
    dfs(0, -1, adj);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    LL k; cin >> k;
    vector<vector<array<int, 2>>> adj(n);
    for (int i = 0, a, b, c; i < n-1; ++i) {
        cin >> a >> b >> c; --a, --b;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    int l = 0, r = 1e9+1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (count_paths(adj, m) < k) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << r << "\n";
}
