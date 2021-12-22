#include <algorithm>
#pragma GCC optimize ("O3")
using namespace std;

void permute(int subtask, int N, int V[], int R[]) {
    sort(V, V + N);

    for (int i = N - 1, j = 0; i >= (N >> 1); i--, j++)
        R[(j << 1)] = V[i];

    for (int i = 0; i < (N >> 1); i++)
        R[(i << 1) | 1] = V[i];
}
