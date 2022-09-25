#include <stdio.h>
#include <assert.h>
#include <algorithm>

#define MAXN 50000

int N, V, counter = 0;
int prices[MAXN], vouchers[MAXN];

int main() {

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d %d", &N, &V));
    for(int i=0; i<N; i++)
        assert(1 == scanf("%d", &prices[i]));
    for(int i=0; i<V; i++)
        assert(1 == scanf("%d", &vouchers[i]));

    std:: sort(prices, prices + N);
    std:: sort(vouchers, vouchers + V);

    for(int i = N-1, j = V-1; i >= 0 && j >= 0; i--)
    {
        if(vouchers[j] >= prices[i])
        {
            j--;
            counter++;
        }
    }

    printf("%d\n", counter);
}

