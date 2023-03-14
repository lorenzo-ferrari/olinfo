/*
 * // https://training.olinfo.it/#/task/ioit_neighborly/statement
 *
 * Greedy!
 * -> build a Trie containing all possible substrings of S
 * -> always add the maximum prefix possible char by char
 * The tight memory limit does not allow for a standard Suffix Trie, thus we
 * build a Compressed Trie containing all suffixes of S (that is, a Suffix Tree)
 *
 */

#include <bits/stdc++.h>
using namespace std;

// Compressed Suffix Trie
// O(|S|^2) time
// O(|S|) memory
struct RadixTree {
    struct Node {
        map<char, int> nxt;
        Node() {}
    };
    int new_node() {
        nodes.push_back(Node());
        return nodes.size() - 1;
    }

    struct Edge {
        int l, r, to;
    };
    int new_edge(int l, int r, int node = -1) {
        if (node == -1) {
            node = new_node();
        }
        edges.push_back({l, r, node});
        return edges.size() - 1;
    }

    vector<Node> nodes;
    vector<Edge> edges;

    void insert(int node, int l, int r) {
        if (r < l) return;
        if (nodes[node].nxt[str[l]] == 0) {
            // normal insert
            nodes[node].nxt[str[l]] = new_edge(l, r);
            return;
        } else {
            // find longest common prefix
            Edge e = edges[nodes[node].nxt[str[l]]];
            int same = 0;
            for (; l+same <= r && e.l+same <= e.r; ++same) {
                if (str[l+same] != str[e.l+same]) {
                    break;
                }
            }
            assert(same > 0 && "Error: str[l] should match str[e.l]");
            if (same > r-l) {
                // string [l, r] was already contained in the Trie
                // do nothing
                return;
            } else if (same > e.r-e.l) {
                // the whole edge matches, move to the next node
                insert(e.to, l+same, r);
            } else {
                // split the current edge in a prefix and two branches
                int old_branch = new_edge(e.l+same, e.r, e.to);
                int new_branch = new_edge(l+same, r);
                edges[nodes[node].nxt[str[l]]].r = e.l + same - 1;
                edges[nodes[node].nxt[str[l]]].to = new_node();
                e = edges[nodes[node].nxt[str[l]]];
                nodes[e.to].nxt[str[e.l+same]] = old_branch;
                nodes[e.to].nxt[str[  l+same]] = new_branch;
                return;
            }
        }
    }

    const string str;
    int root;
    RadixTree(string s) : str(s), root(new_node()) {
        // edge of index 0 stands for no edge
        // -> all edges should have index > 0
        new_edge(0, -1);
        for (int i = 0; i < (int)s.size(); ++i) {
            insert(root, i, s.size()-1);
        }
    }

    void debug(ostream& os) {
        os << "Radix Tree:\n";
        for (int i = 0; i < (int)nodes.size(); ++i) {
            print_node(os, i);
        }
    }
    void print_node(ostream& os, int n) {
        if (nodes[n].nxt.empty()) return;
        os << n << ": {";
        bool first = true;
        for (auto [chr, i] : nodes[n].nxt) {
            if (!first) os << ',';
            print_edge(os, edges[i]);
            first = false;
        }
        os << "}\n";
    }
    void print_edge(ostream& os, Edge e) {
        os << "[\"" << str.substr(e.l, e.r-e.l+1) << "\"," << e.to << "]";
    }

    int count_pieces(const string&);
};

int RadixTree::count_pieces(const string& s) {
    int ans = 0;
    int n = s.size();
    for (int i = 0; i < n; ++ans) {
        int node = root;
        bool stop = false;
        while (!stop && i < n && nodes[node].nxt[s[i]]) {
            Edge e = edges[nodes[node].nxt[s[i]]];
            for (int j = e.l; j <= e.r && i < n; ++j, ++i) {
                if (str[j] != s[i]) {
                    stop = true;
                    break;
                }
            }
            if (!stop && i < n) {
                node = e.to;
            }
        }
    }
    return ans;
}

int main() {
    string e, s;
    getline(cin, e);
    getline(cin, s);

    RadixTree tree(s);

    cout << tree.count_pieces(e) << "\n";
}
