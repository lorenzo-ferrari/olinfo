#include <vector>
#include <stdio.h>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    scanf("%d%d", &n, &k);

    vector <int> u(n);
    vector <vector<int>> pref(n + 1, vector <int> (10));

    for (int i = 0; i < n; i++) {
        scanf("%d", &u[i]);
        pref[i + 1] = pref[i];
        pref[i + 1][u[i]]++;
    }

    // [l, r)
    for (int l = 0, r = k + 1; k != n && l < n; l++) {
        bool good = true;
        for (int i = 0; i < u[l]; i++)
            if (pref[r][i] - pref[l][i] != 0)
                good = false;
        
        if (good) {
            printf("%d ", u[l]);
            // printf("%d ", u[l]);            
            k++;
            r++;
        }
    }
    printf("\n");
}