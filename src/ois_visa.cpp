#include <bits/stdc++.h>
using namespace std;

struct trimask {
    inline static mt19937_64 rng;
    inline static vector<long long> h1;
    inline static vector<long long> h2;

    static void init() {
        rng = mt19937_64(42);
        h1.resize(1000);
        h2.resize(1000);
        generate(begin(h1), end(h1), rng);
        generate(begin(h2), end(h2), rng);
    }

    bitset<1000> visas_seen = 0;
    bitset<1000> visas_taken = 0;
    vector<int16_t> path;
    int node;
    int dist = 1e9;
    long long hash = 0;

    trimask() {}
    trimask(int n, int v) : node(v), path(1, v) {}

    bool seen(int i) const { return visas_seen[i]; }
    bool have(int i) const { return visas_taken[i]; }
    void see(int i) {
        if (!visas_seen[i]) {
            hash ^= h1[i];
        }
        visas_seen[i] = true;
    }
    void buy(int i) {
        see(i);
        if (!visas_taken[i]) {
            hash ^= h2[i];
        }
        visas_taken[i] = true;
    }
    void set_node(int new_node) {
        hash ^= node;
        node = new_node;
        hash ^= node;
    }
    bool operator<(const trimask& oth) const {
        return dist > oth.dist;
    }
    void print() const {
        cout << path.size() << "\n";
        for (int i : path) {
            cout << i << " ";
        }
        cout << "\n";
    }
};

int main() {
    trimask::init();

    bool schifo4 = true;
    bool schifo5 = true;

    int n; cin >> n;
    vector<int> v(n);
    vector<vector<int>> amb(n);
    vector<vector<array<int, 2>>> adj(n);
    for (int i = 0, k, l; i < n; ++i) {
        cin >> v[i] >> k >> l;
        vector<int> a(k), b(l), c(l);
        for (int j = 0; j < k; ++j) { cin >> a[j]; amb[i].push_back(a[j]); }
        for (int j = 0; j < l; ++j) cin >> b[j];
        for (int j = 0; j < l; ++j) cin >> c[j];
        for (int j = 0; j < l; ++j) {
            adj[i].push_back({b[j], c[j]});
        }
        /**/
        if (a != b) schifo5 = false;
        if (i == 0 && k != n-1) schifo4 = false;
        /**/
    }


    if (schifo4 || schifo5) {
        vector<int> dist(n, 1e9);
        vector<vector<int>> path(n);

        priority_queue<array<int, 2>> Q;
        Q.push({0, 0});
        dist[0] = 0;
        path[0].push_back(0);
        while (!Q.empty()) {
            int a =  Q.top()[1];
            int t = -Q.top()[0];
            Q.pop();
            for (auto [b, w] : adj[a]) {
                if (dist[b] > t + w + v[b]) {
                    dist[b] = t + w + v[b];
                    path[b] = path[a];
                    path[b].push_back(b);
                    Q.push({-(int)dist[b], b});
                }
            }
        }
        cout << path[n-1].size() << "\n";
        for (int i : path[n-1]) {
            cout << i << " ";
        }
        cout << "\n";
        return 0;
    }

    vector<int> dist(n, 1e9);
    {
        priority_queue<array<int, 2>> Q;
        Q.push({0, n-1});
        dist[n-1] = 0;
        while (!Q.empty()) {
            int a =  Q.top()[1];
            int t = -Q.top()[0];
            Q.pop();
            for (auto [b, w] : adj[a]) {
                if (dist[b] > t + w) {
                    dist[b] = t + w;
                    Q.push({-(int)dist[b], b});
                }
            }
        }
    }

    priority_queue<trimask> Q;
    {
        trimask mask(n, 0);
        mask.buy(0);
        mask.dist = dist[0];
        Q.push(mask);
    }
    while (!Q.empty()) {
        auto mask = Q.top();
        Q.pop();
        if (mask.node == n-1) {
            mask.print();
            return 0;
        }
        for (int b : amb[mask.node]) {
            if (!mask.seen(b)) {
                mask.see(b);
            }
        }
        for (auto [b, w] : adj[mask.node]) {
            if (!mask.seen(b)) continue;
            auto new_mask = mask;
            new_mask.set_node(b);
            new_mask.path.push_back(b);
            new_mask.dist = mask.dist + w - dist[mask.node] + dist[b];
            if (!mask.have(b)) {
                new_mask.buy(b);
                new_mask.dist += v[b];
            }
            Q.push(new_mask);
        }
    }
}
