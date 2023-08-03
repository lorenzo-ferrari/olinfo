#include "bits/stdc++.h"
using namespace std;

struct nd {
    int idx = -1;
    array<int, 26> nxt{};
};

static constexpr int SIZE = 1e6;
int g = 1;
static nd nodes[SIZE];

static int new_nd() { return g++; }

struct Trie {
    int root;
    Trie() : root(new_nd()) {}
    void insert(const vector<int>& s, int idx) {
        int cur = root;
        for (int i = 0; i < (int)s.size(); ++i) {
            if (!nodes[cur].nxt[s[i]]) {
                nodes[cur].nxt[s[i]] = new_nd();
            }
            cur = nodes[cur].nxt[s[i]];
        }
        if (nodes[cur].idx == -1) {
            nodes[cur].idx = idx;
        }
    }
};

static int rev(int trg, int key) {
    return (trg - key + 26) % 26;
}

static vector<int> add(vector<int> v, const vector<int>& key) {
    for (int i = 0; i < (int)v.size(); ++i) {
        v[i] = (v[i] + key[i % key.size()]) % 26;
    }
    return v;
}

static vector<int> tovector(string s) {
    vector<int> ans(s.size());
    for (int i = 0; i < (int)s.size(); ++i) {
        ans[i] = s[i] - 'a';
    }
    return ans;
}

bool operator<(const vector<int>& a, const vector<int>& b) {
    assert(a.size() == b.size());
    for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return false;
}

int main() {
    int n; cin >> n;
    int k; cin >> k;
    vector<vector<int>> t(k);
    map<int, Trie> tries;

    for (int i = 0; i < k; ++i) {
        string key; cin >> key;
        t[i].resize(key.size());
        for (int j = 0; j < (int)key.size(); ++j) {
            t[i][j] = (key[j] - 'a');
        }
        tries[key.size()].insert(t[i], i);
    }

    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        auto v = tovector(s);
        int l = s.size();
        int ans = -1;
        for (int d = 1; d <= l; ++d) {
            if (l % d || !tries.count(d)) continue;
            int cur = tries[d].root;
            for (int dep = 0; dep < d; ++dep) {
                for (int trg = 0; trg < 26; ++trg) {
                    if (nodes[cur].nxt[rev(trg, v[dep])]) {
                        cur = nodes[cur].nxt[rev(trg, v[dep])];
                        break;
                    }
                }
            }
            if (ans == -1 || add(v, t[nodes[cur].idx]) < add(v, t[ans])) {
                ans = nodes[cur].idx;
            }
        }
        cout << (ans == -1 ? -1 : ans+1) << "\n";
    }
}
