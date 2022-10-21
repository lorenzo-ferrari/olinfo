#pragma GCC optimize ("O3")
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

static constexpr size_t N = 1e5;
static constexpr double eps = 1e-9;

static int n;
static int p[N], s[N], r[N];

struct nd {
    int to = -1;
    double tot = 0;
    double best = 0;
};
static nd join(const nd& a, const nd& b, double x) {
    nd ans;
    ans.to = b.to;
    int m = a.to;
    double delta = x*s[m] + ((double)(s[m] - p[m])/s[m] - x)*s[m];
    ans.tot = a.tot + b.tot + delta;
    ans.best = max(a.best, a.tot + b.best + delta);
    return ans;
};

vector<nd> prv(N), cur(N);
static bool works(double x) {
    // if the answer is a cycle, theoretically it isn't handled properly
    // however you can increase the number of iterations of LCA to get close enough
    for (int i = 0; i < n; ++i) {
        cur[i] = {r[i], -x*s[i], -x*s[i]};
    }
    for (int i = 1; i < 28; ++i) {
        swap(prv, cur);
        for (int j = 0; j < n; ++j) {
            cur[j] = join(prv[j], prv[prv[j].to], x);
            if (cur[j].best > 0) {
                return true;
            }
        }
    }
    return false;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s[i] >> p[i] >> r[i];
    }

    double ll = 0, rr = 1.0;
    while (rr - ll > eps) {
        double mid = (ll + rr) / 2;
        if (works(mid)) {
            ll = mid;
        } else {
            rr = mid;
        }
    }
    cout << fixed << setprecision(9) << 100*(ll + rr)/2 << "\n";

    return 0;
}
