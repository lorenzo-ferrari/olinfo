#include "bits/stdc++.h"
using namespace std;
using LL = long long;

variant<bool, vector<int>> find_tour(int n, vector<int> a) {
    if (a[0] != 2 || a[n - 1] != 2) {
        return false;
    }

    vector<int> tour;
    tour.push_back(0);
    queue<int> Q;
    int open = 2;
    for (int i = 1; i < n - 1; ++i) {
        if (a[i] == open + 2) {         // both left
            Q.push(i);
            open += 2;
        } else if (a[i] == open + 1) {  // one and one
            tour.push_back(i);
        } else if (a[i] == open) {      // both right
            tour.push_back(i);
            if (Q.empty()) {
                return false;
            }
            tour.push_back(Q.front());
            Q.pop();
            open -= 2;
        } else {
            return false;
        }
    }

    if (open != 2) {
        return false;
    }

    tour.push_back(n - 1);

    return tour;
}
